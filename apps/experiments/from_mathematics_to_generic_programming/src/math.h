#ifndef MATH_H_reogh378904h27837h3
#define MATH_H_reogh378904h27837h3

#include "ul/ul.h"
#include <concepts>

namespace math
{
/// requires (Domain<Op, AxA>)
template <typename T>
concept SemigroupOperation = true;

template <typename>
concept NoncommutativeAdditiveSemigroup = true;

template <typename>
concept MultiplicativeSemigroup = true;

/// requires (Domain<Op, AxA>)
template <typename T>
concept MonoidOperation = true;

template <typename>
concept NoncommutativeAdditiveMonoid = true;

template <typename>
concept MultiplicativeMonoid = true;

/// requires (Domain<Op, AxA>)
template <typename T>
concept GroupOperation = true;

template <typename>
concept NoncommutativeAdditiveGroup = true;

template <typename>
concept AdditiveGroup = true;

template <typename>
concept MultiplicativeGroup = true;

template <typename T>
concept Integer = std::integral<T>;

template <typename T>
concept Regular = std::regular<T>;

template <Integer N>
bool odd(N n)
{
    return static_cast<bool>(n & 0x1);
}

template <Integer N>
N half(N n)
{
    return n >> 1;
}

template <MultiplicativeGroup A>
A multiplicative_inverse(A a)
{
    return A{1} / a;
}

template <NoncommutativeAdditiveMonoid T>
T identity_element(std::plus<T>)
{
    return T{0};
}

template <MultiplicativeMonoid T>
T identity_element(std::multiplies<T>)
{
    return T{1};
}

template <MultiplicativeGroup A>
struct reciprocal : public std::unary_function<A, A>
{
    A operator()(const A& a) const
    {
        return multiplicative_inverse(a);
    }
};

template <AdditiveGroup T>
std::negate<T> inverse_operation(std::plus<T>)
{
    return std::negate<T>();
}

template <MultiplicativeGroup T>
reciprocal<T> inverse_operation(std::multiplies<T>)
{
    return reciprocal<T>();
}
} // namespace math

#endif
