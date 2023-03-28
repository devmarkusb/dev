#ifndef POWER_H_oerth2zh29hz5833hbdf
#define POWER_H_oerth2zh29hz5833hbdf

#include "math.h"
#include "ul/ul.h"

namespace math
{
template <MultiplicativeSemigroup A, Integer N>
A power_accumulate_semigroup(A r, A a, N n)
{
    UL_EXPECT(n >= 0);
    if (n == 0)
        return r;
    while (true)
    {
        if (odd(n))
        {
            r *= a;
            if (n == 1)
                return r;
        }
        n = half(n);
        a *= a;
    }
}

template <MultiplicativeSemigroup A, Integer N>
A power_semigroup(A a, N n)
{
    UL_EXPECT(n > 0);
    while (!odd(n))
    {
        a *= a;
        n = half(n);
    }
    if (n == 1)
        return a;
    return power_accumulate_semigroup(a, a * a, half(n - 1));
}

template <MultiplicativeMonoid A, Integer N>
A power_monoid(A a, N n)
{
    UL_EXPECT(n >= 0);
    if (n == 0)
        return A{1};
    return power_semigroup(a, n);
}

template <Regular A, Integer N, SemigroupOperation Op>
A power_accumulate_semigroup(A r, A a, N n, Op op)
{
    UL_EXPECT(n >= 0);
    if (n == 0)
        return r;
    while (true)
    {
        if (odd(n))
        {
            r = op(r, a);
            if (n == 1)
                return r;
        }
        n = half(n);
        a = op(a, a);
    }
}

/// For a multiply operation as op you achieve the canonical 'power'.
template <Regular A, Integer N, SemigroupOperation Op>
A power_semigroup(A a, N n, Op op)
{
    UL_EXPECT(n > 0);
    while (!odd(n))
    {
        a = op(a, a);
        n = half(n);
    }
    if (n == 1)
        return a;
    return power_accumulate_semigroup(a, op(a, a), half(n - 1), op);
}

template <Regular A, Integer N, MonoidOperation Op>
A power_monoid(A a, N n, Op op)
{
    UL_EXPECT(n >= 0);
    if (n == 0)
        return identity_element(op);
    return power_semigroup(a, n, op);
}

template <Regular A, Integer N, GroupOperation Op>
A power_group(A a, N n, Op op)
{
    if (n < 0)
    {
        n = -n;
        a = inverse_operation(op)(a);
    }
    return power_monoid(a, n, op);
}
} // namespace math

#endif
