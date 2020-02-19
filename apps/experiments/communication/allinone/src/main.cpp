#include "consumer_api/consumer.h"
#include "producer_api/producer.h"
#include <algorithm>
#include <vector>


int main()
{
    const auto product{producer::produce()};

    std::vector<int> transformed;
    transformed.reserve(product.size());
    std::transform(std::cbegin(product), std::cend(product), std::back_inserter(transformed),
        [](const auto productElem)
        {
            return productElem.size();
        });

    consumer::consume(transformed);

    return 0;
}
