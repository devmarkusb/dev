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

namespace {
/** producer: pushes into product queue
    processor: pulls from queue, processes, pushes into processed products (result) queue
    consumer: pulls from processed products queue

    Alternative:
    set product queue size as tiny as there are processors; this seems to suffice most of
    the time*/
class App : public Application {
public:
    static constexpr auto input_interval{std::chrono::milliseconds(1)};
    static constexpr auto measurement_interval{input_interval};
    static constexpr auto print_interval{std::chrono::seconds(3)};
    static constexpr auto simulated_additional_processing_time{input_interval * 5};
    static const auto processing_thread_count{5};

    ~App() override {
        if (is_running_)
            App::terminate();
        std::cout << "Application destructed" << std::endl;
    }

    void run() override {
        is_running_ = true;

        producer_thread_ = std::thread{[this]() {
            asio::steady_timer timer{io_context_};
            while (is_running_) {
                timer.expires_from_now(input_interval);
                timer.wait();
                if (!products_.push(producer::produce())) {
                    std::cout << "queue of produced elements full\n";
                }
            }
        }};

        for (auto& processing_thread : processing_threads_) {
            processing_thread = std::thread{[this]() {
                while (is_running_) {
                    producer::Product product;
                    if (!products_.wait_and_pop(product))
                        break;

                    consumer::Product processed;
                    processed.reserve(product.size());

                    std::this_thread::sleep_for(simulated_additional_processing_time);
                    std::transform(
                        std::cbegin(product), std::cend(product), std::back_inserter(processed), [](const auto string) {
                            return string.size();
                        });

                    if (!processed_products_.push(processed)) {
                        std::cout << "queue of transformed elements full\n";
                    }
                }
            }};
        }

        consumer_thread_ = std::thread{[this]() {
            while (is_running_) {
                consumer::Product product;
                if (!processed_products_.wait_and_pop(product))
                    break;
                consumer::consume(product);
            }
        }};

        on_measurement_timer({});
        on_print_timer({});
        io_context_.run();
    }

    void terminate() override {
        is_running_ = false;
        products_.stop();
        processed_products_.stop();
        producer_thread_.join();
        std::for_each(std::begin(processing_threads_), std::end(processing_threads_), [](auto& t) {
            t.join();
        });
        consumer_thread_.join();
        measurement_timer_.cancel();
        print_timer_.cancel();
        io_context_.stop();
    }

private:
    bool is_running_{};
    asio::io_context io_context_;
    ul::thread::WaitQueue<producer::Product> products_{/*processingThreadCount*/};
    ul::thread::WaitQueue<consumer::Product> processed_products_{};
    asio::steady_timer measurement_timer_{io_context_};
    asio::steady_timer print_timer_{io_context_};
    std::thread producer_thread_;
    std::array<std::thread, processing_thread_count> processing_threads_;
    std::thread consumer_thread_;
    size_t measurement_count_{};
    size_t measurement_product_queue_size_{};
    size_t measurement_transformed_product_queue_size_{};
    size_t measurement_product_queue_size_max_{};
    size_t measurement_transformed_product_queue_size_max_{};

    void on_measurement_timer(const asio::error_code& ec) {
        if (!is_running_)
            return;

        if (ec) {
            std::cout << "asio error code: " << ec << std::endl;
            return;
        }

        ++measurement_count_;
        measurement_product_queue_size_max_ = std::max(measurement_product_queue_size_max_, products_.size());
        measurement_product_queue_size_ += products_.size();
        measurement_transformed_product_queue_size_max_ =
            std::max(measurement_transformed_product_queue_size_max_, processed_products_.size());
        measurement_transformed_product_queue_size_ += processed_products_.size();

        measurement_timer_.expires_from_now(measurement_interval);

        using namespace std::placeholders;
        measurement_timer_.async_wait(std::bind(&App::on_measurement_timer, this, _1));
    }

    void on_print_timer(const asio::error_code& ec) {
        if (!is_running_)
            return;

        if (ec) {
            std::cout << "asio error code: " << ec << std::endl;
            return;
        }

        std::stringstream out_p;
        out_p << "avg. products queue size: "
              << static_cast<double>(measurement_product_queue_size_) / static_cast<double>(measurement_count_)
              << std::endl;
        std::cout << out_p.str();
        std::stringstream out_tp;
        out_tp << "avg. transformed products queue size: "
               << static_cast<double>(measurement_transformed_product_queue_size_)
                      / static_cast<double>(measurement_count_)
               << std::endl;
        std::cout << out_tp.str();

        std::stringstream out_pm;
        out_pm << "max. products queue size: " << measurement_product_queue_size_max_ << std::endl;
        std::cout << out_pm.str();
        std::stringstream out_tpm;
        out_tpm << "max. transformed products queue size: " << measurement_transformed_product_queue_size_max_
                << std::endl;
        std::cout << out_tpm.str();

        print_timer_.expires_from_now(print_interval);

        using namespace std::placeholders;
        print_timer_.async_wait(std::bind(&App::on_print_timer, this, _1));
    }
};

// volatile std::sig_atomic_t g_signal{};
Application* g_application{};

void signal_handler(int) {
    // g_signal = signal;
    if (g_application)
        g_application->terminate();
}
} // namespace

int main() {
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);

    auto app{std::make_unique<client_server::App>()};
    g_application = app.get();

    app->run();

    std::cout << "finishing..." << std::endl;
    return 0;
}
