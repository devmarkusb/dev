#include "prime-sieve.h"
#include "gtest/gtest.h"

constexpr auto m{100};
constexpr auto mi{(m - 3) / 2};

TEST(sift2, test)
{
    std::vector<bool> primes;
    primes.resize(mi);
    math::sift2(std::begin(primes), mi);
    for (size_t i{}; i < primes.size(); ++i)
    {
        if (primes[i])
            std::cout << 2 * i + 3 << " ";
    }
}
