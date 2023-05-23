#include "prime-sieve.h"
#include <bitset>
#include <vector>

namespace {
template <typename T>
constexpr T value(T index) {
    UL_EXPECT(index >= 0);
    return 2 * index + 3;
}

void list_palindromes_dec(const std::vector<uint8_t>& primes) {
    for (size_t i{}; i < primes.size(); ++i) {
        if (!primes[i])
            continue;

        const auto val{value(i)};
        const auto digit_count_dec{ul::math::get_digit_count(value(i))};
        bool palindrome_dec{true};
        for (std::remove_const_t<decltype(digit_count_dec)> d{}; d < digit_count_dec / 2; ++d) {
            if (ul::math::get_digit(val, d) != ul::math::get_digit(val, digit_count_dec - d - 1)) {
                palindrome_dec = false;
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
        if (palindrome_dec)
            std::cout << ul::fmt::group_thousands(value(i)) << " ";
    }
}

void list_palindromes_hex(const std::vector<uint8_t>& primes) {
    for (size_t i{}; i < primes.size(); ++i) {
        if (!primes[i])
            continue;

        const auto val{value(i)};
        const auto digit_count_hex{ul::math::get_digit_count(value(i), ul::math::NumBase::hex)};
        bool palindrome_hex{true};
        for (std::remove_const_t<decltype(digit_count_hex)> d{}; d < digit_count_hex / 2; ++d) {
            if (ul::math::get_digit(val, d, ul::math::NumBase::hex)
                != ul::math::get_digit(val, digit_count_hex - d - 1, ul::math::NumBase::hex)) {
                palindrome_hex = false;
                break;
            }
        }
        // Similar to dec we have only odd digit counts, except for 11.
        if (palindrome_hex)
            std::cout << std::hex << value(i) << " ";
    }
}

void list_palindromes_bin(const std::vector<uint8_t>& primes) {
    for (size_t i{}; i < primes.size(); ++i) {
        if (!primes[i])
            continue;

        const auto val{value(i)};
        const auto digit_count_bin{ul::math::get_digit_count(value(i), ul::math::NumBase::bin)};
        bool palindrome_bin{true};
        for (std::remove_const_t<decltype(digit_count_bin)> d{}; d < digit_count_bin / 2; ++d) {
            if (ul::math::get_digit(val, d, ul::math::NumBase::bin)
                != ul::math::get_digit(val, digit_count_bin - d - 1, ul::math::NumBase::bin)) {
                palindrome_bin = false;
                break;
            }
        }
        // Similar to dec and hex we have only odd digit counts, except for 3 (0b11).
        if (palindrome_bin) {
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
    list_palindromes_dec(primes);

    std::cout << "\npalindrome primes in hex:\n";
    list_palindromes_hex(primes);

    std::cout << "\npalindrome primes in bin:\n";
    list_palindromes_bin(primes);

    return {};
}
