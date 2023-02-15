#include "prime-sieve.h"
#include <vector>

template <typename T>
constexpr T value(T index)
{
    UL_EXPECT(index >= 0);
    return 2 * index + 3;
}

int main()
{
    constexpr auto m{1'000'000};
    constexpr auto mi{(m - 3) / 2};

    std::vector<uint8_t> primes;
    primes.resize(mi);
    math::sift2(std::begin(primes), mi);
    for (size_t i{}; i < primes.size(); ++i)
    {
        if (!primes[i])
            continue;

        const auto val{value(i)};
        const auto digitCount{ul::math::getDigitCount(value(i))};
        bool palindromeDec{true};
        for (std::remove_const_t<decltype(digitCount)> d{}; d < digitCount / 2; ++d)
        {
            if (ul::math::getDigit(val, d) != ul::math::getDigit(val, digitCount - d - 1))
            {
                palindromeDec = false;
                break;
            }
        }
        // Seem to have those here:
        // 0..1.000, 10.000..20.000, 30.000..40.000, 70.000..80.000, 90.000..100.000
        // 1Mio..2Mio, 3Mio..4Mio, 7Mio..8Mio, 9Mio..10Mio
        // 100Mio..200Mio, 300Mio..400Mio, 700Mio..800Mio, 900Mio..1000Mio
        // So except for 11 always an odd number of digits.
        // And there are strange gaps lacking numbers between 200 and 300, 400 and 700, 800 and 900,
        // continuing over and over when adding two 0's each.
        if (palindromeDec)
            std::cout << ul::fmt::groupThousands(value(i)) << " ";
    }

    return {};
}
