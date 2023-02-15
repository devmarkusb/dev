#include "prime-sieve.h"
#include "ul/ul.h"

#include "matplotlibcpp.h"

namespace
{
constexpr int index(int value)
{
    UL_EXPECT(value >= 3);
    return (value - 3) / 2;
}
} // namespace

int main()
{
    constexpr auto m{10'000'000};
    constexpr auto mi{index(m)};
    std::vector<uint8_t> primes;
    primes.resize(mi);
    math::sift2(std::begin(primes), mi);

    std::vector<int> x(m);
    std::vector<int> y(m);
    std::vector<int> yfit(m);
    x[0] = 0;
    x[1] = 1;
    x[2] = 2;
    y[0] = 0;
    y[1] = 0;
    y[2] = 1;
    int pi{1};
    for (int i{3}; i < m; ++i)
    {
        if ((i & 0x1) && primes[static_cast<size_t>(index(i))])
        {
            ++pi;
        }
        x[static_cast<size_t>(i)] = i;
        y[static_cast<size_t>(i)] = pi;
        yfit[static_cast<size_t>(i)] = 1./16. * i + 40000;
    }

    matplotlibcpp::title("Number of primes < x");
    matplotlibcpp::named_plot("pi(x)", x, y);
    matplotlibcpp::named_plot("fit(x)", x, yfit);
    matplotlibcpp::legend();
    matplotlibcpp::show();

    return ul::prog_exit_success;
}