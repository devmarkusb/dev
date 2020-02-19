#include "consumer_api/consumer.h"
#include "producer_api/producer.h"
#include <algorithm>
#include <csignal>
#include <iostream>
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

volatile std::sig_atomic_t g_signalStatus{};
DestrTest g_globalDestrTest;
} // namespace

void signal_handler(int signal)
{
    g_signalStatus = signal;
}

int main()
{
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);

    DestrTest destrTest;
    while (!g_signalStatus)
    {
        const auto product{producer::produce()};

        std::vector<int> transformed;
        transformed.reserve(product.size());
        std::transform(std::cbegin(product), std::cend(product), std::back_inserter(transformed),
            [](const auto productElem) { return productElem.size(); });

        consumer::consume(transformed);
    }

    std::cout << "finishing..." << std::endl;
    return 0;
}
