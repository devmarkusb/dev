#include "consumer_api/consumer.h"

#define DUMP 0
#if DUMP
#include <iostream>
#endif


namespace consumer {
void consume(const Product& product) {
#if DUMP
    std::cout << "consumed one" << std::endl;
#endif
    for (auto part : product) {
#if DUMP
        //std::cout << part << std::endl;
#endif
    }
}
} // namespace consumer
