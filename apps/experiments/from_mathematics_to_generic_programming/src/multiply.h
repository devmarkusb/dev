#ifndef MULTIPLY_H_OEHGY49G294YGB34
#define MULTIPLY_H_OEHGY49G294YGB34

#include "math.h"
#include "ul/ul.h"

namespace math {
int multiply0(int n, int a);
int multiply1(int n, int a);
int multiply2(int n, int a);
int multiply3(int n, int a);
int multiply4(int n, int a);
//! Ordinary multiplication.
int multiply5(int n, int a);
int multiply6_by_15(int a);

template <NoncommutativeAdditiveSemigroup A, std::integral N>
A multiply_accumulate_semigroup(A r, N n, A a) {
    UL_EXPECT(n >= 0);
    if (n == 0)
        return r;
    while (true) {
        if (odd(n)) {
            r += a;
            if (n == 1)
                return r;
        }
        n = half(n);
        a += a;
    }
}

template <NoncommutativeAdditiveSemigroup A, Integer N>
A multiply_semigroup(N n, A a) {
    UL_EXPECT(n > 0);
    while (!odd(n)) {
        a += a;
        n = half(n);
    }
    if (n == 1)
        return a;
    return multiply_accumulate_semigroup(a, half(n - 1), a + a);
}

template <NoncommutativeAdditiveMonoid A, Integral N>
A multiply_monoid(N n, A a) {
    UL_EXPECT(n >= 0);
    if (n == 0)
        return A{};
    return multiply_semigroup(n, a);
}

template <NoncommutativeAdditiveGroup A, Integral N>
A multiply_group(N n, A a) {
    if (n < 0) {
        n = -n;
        a = -a;
    }
    return multiply_monoid(n, a);
}
} // namespace math

#endif
