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
    ~Application()
    {
        if (isRunning_)
            terminate();
    }

    void run()
    {
        isRunning_ = true;

        producerThread_ = std::thread{[this]() {
            asio::steady_timer timer{ioContext_};
            while (isRunning_)
            {
                timer.expires_from_now(std::chrono::milliseconds(10));
                timer.wait();
                if (!products_.push(producer::produce()))
                {
                    std::cout << "queue of produced elements full\n";
                }
            }
            products_.stop();
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
            transformedProducts_.stop();
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

        onTimer({});
        ioContext_.run();
    }

    void terminate()
    {
        isRunning_ = false;
        producerThread_.join();
        transformerThread_.join();
        consumerThread_.join();
        timer_.cancel();
        ioContext_.stop();
    }

private:
    bool isRunning_{};
    asio::io_context ioContext_;
    too::thread::WaitQueue<producer::Product> products_{100};
    too::thread::WaitQueue<consumer::Product> transformedProducts_{100};
    asio::steady_timer timer_{ioContext_};
    std::thread producerThread_;
    std::thread transformerThread_;
    std::thread consumerThread_;

    void onTimer(const asio::error_code& ec)
    {
        if (ec)
        {
            std::cout << "asio error code: " << ec << std::endl;
            return;
        }

        std::stringstream outP;
        outP << "products queue size: " << products_.size() << std::endl;
        std::cout << outP.str();
        std::stringstream outTP;
        outTP << "transformed products queue size: " << transformedProducts_.size() << std::endl;
        std::cout << outTP.str();

        timer_.expires_from_now(std::chrono::seconds(3));

        using namespace std::placeholders;
        timer_.async_wait(std::bind(&Application::onTimer, this, _1));
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
