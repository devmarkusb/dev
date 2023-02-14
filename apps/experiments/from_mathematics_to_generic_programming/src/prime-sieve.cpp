#include "prime-sieve.h"
#include "ul/ul.h"

#include "matplotlibcpp.h"

namespace
{
constexpr int index(int value)
{
    return (value - 3) / 2;
}

int pi(int n, const std::vector<uint8_t>& primes)
{
    UL_EXPECT(index(n) <= ul::narrow_cast<int>(primes.size()));
    int count{};
    for (int i{}; i < index(n); ++i)
    {
        UL_ASSERT(i >= 0);
        if (primes[static_cast<size_t>(i)])
        {
            ++count;
        }
    }
    return count;
}
} // namespace

int main()
{
    constexpr auto m{100'000};
    constexpr auto mi{index(m)};
    std::vector<uint8_t> primes;
    primes.resize(mi);
    math::sift2(std::begin(primes), mi);

    std::vector<double> x(m);
    std::vector<double> y(m);
    for (int i{}; i < m; ++i)
    {
        x[static_cast<size_t>(i)] = i;
        y[static_cast<size_t>(i)] = pi(i, primes);
    }

    matplotlibcpp::named_plot("pi(x)", x, y);

    return ul::prog_exit_success;
}