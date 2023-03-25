#ifndef MULTIPLY_H_oehgy49g294ygb34
#define MULTIPLY_H_oehgy49g294ygb34

#include "math.h"
#include "ul/ul.h"

namespace math
{
int multiply0(int n, int a);
int multiply1(int n, int a);
int multiply2(int n, int a);
int multiply3(int n, int a);
int multiply4(int n, int a);
//! Ordinary multiplication.
int multiply5(int n, int a);
int multiply6_by_15(int a);

template <NoncommutativeAdditiveSemigroup A, std::integral N>
A multiply_accumulate_semigroup(A r, N n, A a)
{
    UL_EXPECT(n >= 0);
    if (n == 0)
        return r;
    while (true)
    {
        if (odd(n))
        {
            r += a;
            if (n == 1)
                return r;
        }
        n = half(n);
        a += a;
    }
}

template <NoncommutativeAdditiveMonoid A, Integer N>
A multiply_monoid(N n, A a)
{
    UL_EXPECT(n >= 0);
    if (n == 0)
        return A{0};
    return multiply_semigroup(n, a);
}

template <NoncommutativeAdditiveGroup A, Integer N>
A multiply_group(N n, A a)
{
    if (n < 0)
    {
        n = -n;
        a = -a;
    }
    return multiply_monoid(n, a);
}
} // namespace math

#endif
