#include "alternative.h"
#include "application.h"
#include "consumer_api/consumer.h"
#include "producer_api/producer.h"
#include "util/allthethings.h"
#include "asio.hpp"
#include <algorithm>
#include <csignal>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

namespace
{
/** producer: pushes into product queue
    processor: pulls from queue, processes, pushes into processed products (result) queue
    consumer: pulls from processed products queue

    Alternative:
    set product queue size as tiny as there are processors; this seems to suffice most of
    the time*/
class App : public Application
{
public:
    static constexpr auto inputInterval{std::chrono::milliseconds(1)};
    static constexpr auto measurementInterval{inputInterval};
    static constexpr auto printInterval{std::chrono::seconds(3)};
    static constexpr auto simulatedAdditionalProcessingTime{inputInterval * 5};
    static const auto processingThreadCount{5};

    ~App() override
    {
        if (isRunning_)
            terminate();
        std::cout << "Application destructed" << std::endl;
    }

    void run() override
    {
        isRunning_ = true;

        producerThread_ = std::thread{[this]()
                                      {
                                          asio::steady_timer timer{ioContext_};
                                          while (isRunning_)
                                          {
                                              timer.expires_from_now(inputInterval);
                                              timer.wait();
                                              if (!products_.push(producer::produce()))
                                              {
                                                  std::cout << "queue of produced elements full\n";
                                              }
                                          }
                                      }};

        for (auto& processingThread : processingThreads_)
        {
            processingThread = std::thread{
                [this]()
                {
                    while (isRunning_)
                    {
                        producer::Product product;
                        if (!products_.waitAndPop(product))
                            break;

                        consumer::Product processed;
                        processed.reserve(product.size());

                        std::this_thread::sleep_for(simulatedAdditionalProcessingTime);
                        std::transform(
                            std::cbegin(product), std::cend(product), std::back_inserter(processed),
                            [](const auto string)
                            {
                                return string.size();
                            });

                        if (!processedProducts_.push(processed))
                        {
                            std::cout << "queue of transformed elements full\n";
                        }
                    }
                }};
        }

        consumerThread_ = std::thread{[this]()
                                      {
                                          while (isRunning_)
                                          {
                                              consumer::Product product;
                                              if (!processedProducts_.waitAndPop(product))
                                                  break;
                                              consumer::consume(product);
                                          }
                                      }};

        onMeasurementTimer({});
        onPrintTimer({});
        ioContext_.run();
    }

    void terminate() override
    {
        isRunning_ = false;
        products_.stop();
        processedProducts_.stop();
        producerThread_.join();
        std::for_each(
            std::begin(processingThreads_), std::end(processingThreads_),
            [](auto& t)
            {
                t.join();
            });
        consumerThread_.join();
        measurementTimer_.cancel();
        printTimer_.cancel();
        ioContext_.stop();
    }

private:
    bool isRunning_{};
    asio::io_context ioContext_;
    ul::thread::WaitQueue<producer::Product> products_{/*processingThreadCount*/};
    ul::thread::WaitQueue<consumer::Product> processedProducts_{};
    asio::steady_timer measurementTimer_{ioContext_};
    asio::steady_timer printTimer_{ioContext_};
    std::thread producerThread_;
    std::array<std::thread, processingThreadCount> processingThreads_;
    std::thread consumerThread_;
    size_t measurementCount_{};
    size_t measurementProductQueueSize_{};
    size_t measurementTransformedProductQueueSize_{};
    size_t measurementProductQueueSizeMax_{};
    size_t measurementTransformedProductQueueSizeMax_{};

    void onMeasurementTimer(const asio::error_code& ec)
    {
        if (!isRunning_)
            return;

        if (ec)
        {
            std::cout << "asio error code: " << ec << std::endl;
            return;
        }

        ++measurementCount_;
        measurementProductQueueSizeMax_ = std::max(measurementProductQueueSizeMax_, products_.size());
        measurementProductQueueSize_ += products_.size();
        measurementTransformedProductQueueSizeMax_ =
            std::max(measurementTransformedProductQueueSizeMax_, processedProducts_.size());
        measurementTransformedProductQueueSize_ += processedProducts_.size();

        measurementTimer_.expires_from_now(measurementInterval);

        using namespace std::placeholders;
        measurementTimer_.async_wait(std::bind(&App::onMeasurementTimer, this, _1));
    }

    void onPrintTimer(const asio::error_code& ec)
    {
        if (!isRunning_)
            return;

        if (ec)
        {
            std::cout << "asio error code: " << ec << std::endl;
            return;
        }

        std::stringstream outP;
        outP << "avg. products queue size: "
             << static_cast<double>(measurementProductQueueSize_) / static_cast<double>(measurementCount_) << std::endl;
        std::cout << outP.str();
        std::stringstream outTP;
        outTP << "avg. transformed products queue size: "
              << static_cast<double>(measurementTransformedProductQueueSize_) / static_cast<double>(measurementCount_)
              << std::endl;
        std::cout << outTP.str();

        std::stringstream outPM;
        outPM << "max. products queue size: " << measurementProductQueueSizeMax_ << std::endl;
        std::cout << outPM.str();
        std::stringstream outTPM;
        outTPM << "max. transformed products queue size: " << measurementTransformedProductQueueSizeMax_ << std::endl;
        std::cout << outTPM.str();

        printTimer_.expires_from_now(printInterval);

        using namespace std::placeholders;
        printTimer_.async_wait(std::bind(&App::onPrintTimer, this, _1));
    }
};

// volatile std::sig_atomic_t g_signal{};
Application* g_application{};

void signal_handler(int)
{
    // g_signal = signal;
    if (g_application)
        g_application->terminate();
}
} // namespace

int main()
{
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);

    auto app{std::make_unique<client_server::App>()};
    g_application = app.get();

    app->run();

    std::cout << "finishing..." << std::endl;
    return 0;
}
