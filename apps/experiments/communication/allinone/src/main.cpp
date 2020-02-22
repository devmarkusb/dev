#include "consumer_api/consumer.h"
#include "producer_api/producer.h"
#include "toolib/thread/waitqueue.h"
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
struct DestrTest
{
    ~DestrTest()
    {
        std::cout << "DestrTest destructed" << std::endl;
    }
};

class Application
{
public:
    static inline constexpr auto inputInterval{std::chrono::microseconds(1)};
    static inline constexpr auto measurementInterval{inputInterval};
    static inline constexpr auto printInterval{std::chrono::seconds(3)};

    ~Application()
    {
        if (isRunning_)
            terminate();
        std::cout << "Application destructed" << std::endl;
    }

    void run()
    {
        isRunning_ = true;

        producerThread_ = std::thread{[this]() {
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

        transformerThread_ = std::thread{[this]() {
            while (isRunning_)
            {
                producer::Product product;
                if (!products_.waitAndPop(product))
                    break;

                consumer::Product transformed;
                transformed.reserve(product.size());
                std::transform(std::cbegin(product), std::cend(product), std::back_inserter(transformed),
                    [](const auto string) { return string.size(); });
                if (!transformedProducts_.push(transformed))
                {
                    std::cout << "queue of transformed elements full\n";
                }
            }
        }};

        consumerThread_ = std::thread{[this]() {
            while (isRunning_)
            {
                consumer::Product product;
                if (!transformedProducts_.waitAndPop(product))
                    break;
                consumer::consume(product);
            }
        }};

        onMeasurementTimer({});
        onPrintTimer({});
        ioContext_.run();
    }

    void terminate()
    {
        isRunning_ = false;
        products_.stop();
        transformedProducts_.stop();
        producerThread_.join();
        transformerThread_.join();
        consumerThread_.join();
        measurementTimer_.cancel();
        printTimer_.cancel();
        ioContext_.stop();
    }

private:
    bool isRunning_{};
    asio::io_context ioContext_;
    too::thread::WaitQueue<producer::Product> products_{};
    too::thread::WaitQueue<consumer::Product> transformedProducts_{};
    asio::steady_timer measurementTimer_{ioContext_};
    asio::steady_timer printTimer_{ioContext_};
    std::thread producerThread_;
    std::thread transformerThread_;
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
        measurementProductQueueSizeMax_ =
            std::max(measurementProductQueueSizeMax_, products_.size());
        measurementProductQueueSize_ += products_.size();
        measurementTransformedProductQueueSizeMax_ =
            std::max(measurementTransformedProductQueueSizeMax_, transformedProducts_.size());
        measurementTransformedProductQueueSize_ += transformedProducts_.size();

        measurementTimer_.expires_from_now(measurementInterval);

        using namespace std::placeholders;
        measurementTimer_.async_wait(std::bind(&Application::onMeasurementTimer, this, _1));
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
        outP << "avg. products queue size: " << static_cast<double>(measurementProductQueueSize_) / measurementCount_
             << std::endl;
        std::cout << outP.str();
        std::stringstream outTP;
        outTP << "avg. transformed products queue size: "
              << static_cast<double>(measurementTransformedProductQueueSize_) / measurementCount_ << std::endl;
        std::cout << outTP.str();

        std::stringstream outPM;
        outPM << "max. products queue size: " << measurementProductQueueSizeMax_ << std::endl;
        std::cout << outPM.str();
        std::stringstream outTPM;
        outTPM << "max. transformed products queue size: " << measurementTransformedProductQueueSizeMax_ << std::endl;
        std::cout << outTPM.str();

        printTimer_.expires_from_now(printInterval);

        using namespace std::placeholders;
        printTimer_.async_wait(std::bind(&Application::onPrintTimer, this, _1));
    }
};

//volatile std::sig_atomic_t g_signal{};
DestrTest g_globalDestrTest;
Application* g_application{};

void signal_handler(int)
{
    //g_signal = signal;
    if (g_application)
        g_application->terminate();
}
} // namespace

int main()
{
    DestrTest destrTest;

    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);

    auto app{std::make_unique<Application>()};
    g_application = app.get();

    app->run();

    std::cout << "finishing..." << std::endl;
    return 0;
}
