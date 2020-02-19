#include "consumer_api/consumer.h"
#include <iostream>


namespace consumer
{
void consume(const std::vector<int>& numbers)
{
    for (auto n : numbers)
    {
        std::cout << n << std::endl;
    }
}
} // consumer
