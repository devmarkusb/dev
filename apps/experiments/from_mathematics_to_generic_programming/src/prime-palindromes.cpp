#include "prime-sieve.h"
#include <bitset>
#include <vector>

namespace {
template <typename T>
constexpr T value(T index) {
    UL_EXPECT(index >= 0);
    return 2 * index + 3;
}

void listPalindromesDec(const std::vector<uint8_t>& primes) {
    for (size_t i{}; i < primes.size(); ++i) {
        if (!primes[i])
            continue;

        const auto val{value(i)};
        const auto digitCountDec{ul::math::getDigitCount(value(i))};
        bool palindromeDec{true};
        for (std::remove_const_t<decltype(digitCountDec)> d{}; d < digitCountDec / 2; ++d) {
            if (ul::math::getDigit(val, d) != ul::math::getDigit(val, digitCountDec - d - 1)) {
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
}

void listPalindromesHex(const std::vector<uint8_t>& primes) {
    for (size_t i{}; i < primes.size(); ++i) {
        if (!primes[i])
            continue;

        const auto val{value(i)};
        const auto digitCountHex{ul::math::getDigitCount(value(i), ul::math::NumBase::HEX)};
        bool palindromeHex{true};
        for (std::remove_const_t<decltype(digitCountHex)> d{}; d < digitCountHex / 2; ++d) {
            if (ul::math::getDigit(val, d, ul::math::NumBase::HEX)
                != ul::math::getDigit(val, digitCountHex - d - 1, ul::math::NumBase::HEX)) {
                palindromeHex = false;
                break;
            }
        }
        // Similar to dec we have only odd digit counts, except for 11.
        if (palindromeHex)
            std::cout << std::hex << value(i) << " ";
    }
}

void listPalindromesBin(const std::vector<uint8_t>& primes) {
    for (size_t i{}; i < primes.size(); ++i) {
        if (!primes[i])
            continue;

        const auto val{value(i)};
        const auto digitCountBin{ul::math::getDigitCount(value(i), ul::math::NumBase::BIN)};
        bool palindromeBin{true};
        for (std::remove_const_t<decltype(digitCountBin)> d{}; d < digitCountBin / 2; ++d) {
            if (ul::math::getDigit(val, d, ul::math::NumBase::BIN)
                != ul::math::getDigit(val, digitCountBin - d - 1, ul::math::NumBase::BIN)) {
                palindromeBin = false;
                break;
            }
        }
        // Similar to dec and hex we have only odd digit counts, except for 3 (0b11).
        if (palindromeBin) {
            std::bitset<32> b{value(i)};
            std::cout << b << " ";
        }
    }
}
} // namespace

int main() {
    constexpr auto m{100'000'000};
    constexpr auto mi{(m - 3) / 2};

    std::vector<uint8_t> primes;
    primes.resize(mi);
    math::sift2(std::begin(primes), mi);

    std::cout << "palindrome primes in dec:\n";
    listPalindromesDec(primes);

    std::cout << "\npalindrome primes in hex:\n";
    listPalindromesHex(primes);

    std::cout << "\npalindrome primes in bin:\n";
    listPalindromesBin(primes);

    return {};
}
