#ifndef CH13CRYPT_H_749F486AA7854E588662AD7BF619C103
#define CH13CRYPT_H_749F486AA7854E588662AD7BF619C103

#include "gcm.h"
#include "math.h"
#include "ul/ul.h"

namespace math {
// E13.1
/** Numbers n that aren't prime (are 'composite') but most likely fool the Fermat test because all witnesses > 1 and
    < n that are coprime to n (which are many) render n being probably prime.
    The function expects n > 1 and non-prime. */
template <Integer N>
bool is_carmichael(N n) {
    UL_EXPECT(n > N{1});
    UL_EXPECT(!is_prime(n));
    if (n == N{2})
        return false;
    for (N b{2}; b < n; ++b) {
        if (gcd(b, n) != N{1})
            continue;
        if (!fermat_test(n, b)) {
            return false;
        }
    }
    return true;
}

// E13.2
template <size_t n, Integer N>
std::array<N, n> gen_first_carmichaels() {
    std::array<N, n> res{};
    N found{};
    for (N candidate{3}; candidate <= std::numeric_limits<N>::max(); candidate += N{2}) {
        if (is_prime(candidate)) {
            continue;
        }
        if (is_carmichael(candidate)) {
            res[found] = candidate;
            if (++found == res.size()) {
                return res;
            }
        }
    }
    return res;
}

namespace rsa {
// 13.4
namespace kgen {}

// 13.5
// encode
// decode
} // namespace rsa
} // namespace math

#endif
