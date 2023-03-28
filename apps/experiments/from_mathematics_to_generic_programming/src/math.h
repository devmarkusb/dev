#ifndef MATH_H_reogh378904h27837h3
#define MATH_H_reogh378904h27837h3

#include "ul/ul.h"
#include <array>
#include <concepts>
#include <ostream>

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

template <typename>
concept SemiRing = true;

template <typename T>
concept Integer = std::integral<T>;

template <typename T>
concept Regular = std::regular<T>;

/// m rows, n cols, [row][col]
template <SemiRing T, size_t m, size_t n>
using Matrix = std::array<std::array<T, n>, m>;

template <typename T>
concept MatrixLike = true;

template <SemiRing T, size_t m, size_t n>
std::ostream& operator<<(std::ostream& os, const Matrix<T, m, n>& matrix)
{
    for (decltype(m) i{}; i < m; ++i)
    {
        os << "[";
        for (decltype(n) j{}; j < n; ++j)
            os << " " << matrix[i][j];
        os << " ]\n";
    }
    return os;
}

template <SemiRing T, size_t m, size_t k, size_t n>
Matrix<T, m, n> multiply(
    Matrix<T, m, k> l, Matrix<T, k, n> r, SemigroupOperation auto&& innerMul, SemigroupOperation auto&& innerAdd)
{
    Matrix<T, m, n> res{};
    for (decltype(m) i{}; i < m; ++i)
        for (decltype(k) h{}; h < k; ++h)
            for (decltype(n) j{}; j < n; ++j)
                res[i][j] = innerAdd(res[i][j], innerMul(l[i][h], r[h][j]));
    return res;
}

template <SemiRing T, size_t m, size_t k, size_t n>
Matrix<T, m, n> operator*(
    Matrix<T, m, k> l, Matrix<T, k, n> r)
{
    return multiply(l, r, std::multiplies{}, std::plus{});
}

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

template <MatrixLike A>
struct mat_mul : public std::binary_function<A, A, A>
{
    A operator()(const A& a1, const A& a2) const
    {
        return a1 * a2;
    }
};

template <MatrixLike A>
struct mat_mul_gen_bool : public std::binary_function<A, A, A>
{
    A operator()(const A& a1, const A& a2) const
    {
        return multiply(a1, a2, std::logical_and{}, std::logical_or{});
    }
};

template <MultiplicativeSemigroup A>
struct min : public std::binary_function<A, A, A>
{
    A operator()(const A& a1, const A& a2) const
    {
        return std::min(a1, a2);
    }
};

template <SemiRing A, size_t m, size_t k, size_t n>
struct mat_mul_gen_tropical : public std::binary_function<Matrix<A, m, n>, Matrix<A, m, k>, Matrix<A, k, n>>
{
    Matrix<A, m, n> operator()(const Matrix<A, m, k>& a1, const Matrix<A, k, n>& a2) const
    {
        return multiply(a1, a2, std::plus{}, min<A>{});
    }
};
} // namespace math

#endif
