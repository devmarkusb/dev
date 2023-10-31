#ifndef MATH_H_REOGH378904H27837H3
#define MATH_H_REOGH378904H27837H3

#include "ul/ul.h"
#include "util/decl.h"
#include <array>
#include <cmath>
#include <compare>
#include <concepts>
#include <ostream>

namespace math {
template <typename T>
concept Regular = ul::Regular<T>;

/**
    Synonym of Regular suiting a mathematically oriented naming scheme.
    Roughly, you can think of the concept as the category of sets, e.g. int being a type fulfilling/implementing that,
    i.e. being a set. Any variable then being an element or object of that set.
    More precisely, Set is a concept (programming) is a theory (math, like also Group can be considered as a theory and
    not only an algebraic structure) is a genus (Aristotle),
    and e.g. int is a value/object type (programming) is a model (math) is a species (Aristotle),
    and e.g. 42 is a value/object/instance (programming) is an element (math) is an individual (Aristotle).
 */
template <typename S>
concept Set = Regular<S>;

namespace v1 {
template <typename Op, typename SetT>
concept SemigroupOperation =
    Set<SetT> && std::regular_invocable<Op, SetT, SetT> && std::is_same_v<SetT, std::invoke_result_t<Op, SetT, SetT>>
    && requires(Op op, SetT a, SetT b, SetT c) {
           { op(a, b) } -> std::convertible_to<SetT>;
           UL_SEMANTICS {
               op(op(a, b), c) == op(a, op(b, c));
           };
       };
}

inline namespace v2 {
template <typename Op>
concept SemigroupOperation =
    ul::BinaryOperation<Op> && Set<ul::Domain<Op>>
    && requires(Op op, ul::Domain<Op> a, ul::Domain<Op> b, ul::Domain<Op> c) {
           UL_SEMANTICS {
               op(op(a, b), c) == op(a, op(b, c));
           };
       };
}

template <typename Op>
concept Semigroup = Set<ul::Domain<Op>> && SemigroupOperation<Op>;

template <typename SetT>
concept NoncommutativeAdditiveSemigroup = Semigroup<std::plus<SetT>>;

template <typename SetT>
concept MultiplicativeSemigroup = Semigroup<std::multiplies<SetT>>;

template <typename Op, typename SetT>
concept MonoidOperation = Set<SetT> && SemigroupOperation<Op> && requires(Op op, SetT a, SetT identity) {
                                                                           UL_SEMANTICS {
                                                                               op(identity, a) == identity;
                                                                               op(a, identity) == identity;
                                                                           };
                                                                       };

template <typename Op, typename SetT>
concept CommutativeMonoidOperation =
    Set<SetT> && MonoidOperation<Op, SetT> && requires(Op op, SetT a, SetT b) {
                                                  UL_SEMANTICS {
                                                      op(a, b) == op(b, a);
                                                  };
                                              };

template <typename SetT, typename Op>
concept Monoid = Set<SetT> && MonoidOperation<Op, SetT>;

template <typename SetT, typename Op>
concept CommutativeMonoid = Monoid<SetT, Op> && CommutativeMonoidOperation<Op, SetT>;

template <typename SetT>
concept NoncommutativeAdditiveMonoid = Monoid<SetT, std::plus<SetT>>;

template <typename SetT>
concept MultiplicativeMonoid = Monoid<SetT, std::multiplies<SetT>>;

template <typename Op, typename SetT>
concept GroupOperation = Set<SetT> && MonoidOperation<Op, SetT>;

template <typename Op, typename SetT>
concept GroupInverseOperation =
    Set<SetT> && std::regular_invocable<Op, SetT> && std::is_same_v<SetT, std::invoke_result_t<Op, SetT>>
    && requires(Op op, SetT a) {
           { op(a) } -> std::convertible_to<SetT>;
           UL_SEMANTICS {
               op(op(a)) == a;
           };
       };

template <typename SetT, typename Op, typename InverseOp>
concept Group = Set<SetT> && GroupOperation<Op, SetT> && GroupInverseOperation<InverseOp, SetT>
                && requires(Op op, InverseOp inverse_op, SetT a, SetT identity) {
                       UL_SEMANTICS {
                           op(a, inverse_op(a)) == identity;
                           op(inverse_op(a), a) == identity;
                       };
                   };

template <typename SetT>
concept NoncommutativeAdditiveGroup = Group<SetT, std::plus<SetT>, std::negate<SetT>>;

template <typename SetT>
concept AdditiveGroup = NoncommutativeAdditiveGroup<SetT> && requires(SetT a, SetT b) {
                                                                 UL_SEMANTICS {
                                                                     a + b == b + a;
                                                                 };
                                                             };

/** Borderline, works for arithmetic types but enforces general Regular to provide a constructor accepting integer 1
    to produce the multiplicative identity element.*/
template <Regular T>
T identity_element(std::multiplies<T>) {
    return T{1};
}

template <Regular T>
T identity_element(std::plus<T>) {
    return T{};
}

/** Borderline, works for arithmetic types but enforces general Regular to provide a constructor accepting integer 1
    to produce the multiplicative identity element.*/
template <Regular T>
T multiplicative_inverse(T a) {
    return identity_element(std::multiplies<T>{}) / a;
}

template <Regular T>
struct Reciprocal {
    T operator()(const T& a) const {
        return multiplicative_inverse(a);
    }
};

template <typename SetT>
concept MultiplicativeGroup = Group<SetT, std::multiplies<SetT>, Reciprocal<SetT>>;

template <typename SetT, typename OpCommutativeMonoid /*add*/, typename OpMonoid /*multiply*/>
concept SemiRing =
    Set<SetT> && CommutativeMonoid<SetT, OpCommutativeMonoid> && Monoid<SetT, OpMonoid>
    && requires(
        OpCommutativeMonoid op_commutative_monoid, OpMonoid op_monoid, SetT a, SetT b, SetT c,
        SetT commutative_monoid_identity, SetT monoid_identity) {
           UL_SEMANTICS {
               commutative_monoid_identity != monoid_identity;
               op_monoid(commutative_monoid_identity, a) == commutative_monoid_identity;
               op_monoid(a, op_commutative_monoid(b, c)) == op_commutative_monoid(op_monoid(a, b), op_monoid(a, c));
           };
       };

template <typename SetT>
concept SemiRingAddMult = SemiRing<SetT, std::plus<SetT>, std::multiplies<SetT>>;

template <
    typename SetT, typename OpCommutativeGroup /*add*/, typename OpInvCommutativeGroup /*add*/,
    typename OpMonoid /*multiply*/>
concept Ring =
    Set<SetT> && SemiRing<SetT, OpCommutativeGroup, OpMonoid> && Group<SetT, OpCommutativeGroup, OpInvCommutativeGroup>;

template <
    typename SetT, typename OpCommutativeGroup /*add*/, typename OpInvCommutativeGroup /*add*/,
    typename OpCommutativeMonoid /*multiply*/>
concept CommutativeRing = Set<SetT> && Ring<SetT, OpCommutativeGroup, OpInvCommutativeGroup, OpCommutativeMonoid>
                          && CommutativeMonoid<SetT, OpCommutativeMonoid>;

template <
    typename SetT, typename OpCommutativeGroup /*add*/, typename OpInvCommutativeGroup /*add*/,
    typename OpCommutativeMonoid /*multiply*/>
concept IntegralDomain =
    Set<SetT> && CommutativeRing<SetT, OpCommutativeGroup, OpInvCommutativeGroup, OpCommutativeMonoid>
    && requires(OpCommutativeMonoid op_commutative_monoid, SetT a, SetT b, SetT commutative_group_identity) {
           UL_SEMANTICS {
               // a * b = 0  => a = 0 || b = 0 (no other zero divisor besides 0)
               // 0: commutativeGroupIdentity, *: opCommutativeMonoid
               op_commutative_monoid(a, b) != commutative_group_identity
                   || (a == commutative_group_identity || b == commutative_group_identity);
           };
       };

template <typename T>
concept Integral = std::integral<T>;

/// Fast mul/div by 2 and even/odd testing.
template <typename T>
concept BinaryInteger = Integral<T>;

/// Broader than Integral, which is restricted to built-in integer types.
/** Would be interesting to construct. Won't like to built it upon algebraic structure like ring, but perhaps more
    likely upon Peano axioms.*/
template <typename>
concept Integer = true;

template <typename>
concept UnsignedInteger = true;

template <typename T>
concept NaturalNumber = UnsignedInteger<T>;

template <
    typename SetT, typename OpCommutativeGroup /*add*/, typename OpInvCommutativeGroup /*add*/,
    typename OpCommutativeMonoid /*multiply*/, typename OpQuotient, typename OpRemainder, typename OpNorm>
concept EuclideanDomain =
    IntegralDomain<SetT, OpCommutativeGroup, OpInvCommutativeGroup, OpCommutativeMonoid>
    && std::regular_invocable<OpQuotient, SetT, SetT>
    && std::is_same_v<SetT, std::invoke_result_t<OpQuotient, SetT, SetT>>
    && std::regular_invocable<OpRemainder, SetT, SetT>
    && std::is_same_v<SetT, std::invoke_result_t<OpRemainder, SetT, SetT>> && std::regular_invocable<OpNorm, SetT>
    && NaturalNumber<std::invoke_result_t<OpNorm, SetT>>
    && requires(
        SetT a, SetT b, SetT commutative_group_identity, OpQuotient op_quotient, OpRemainder op_remainder,
        OpCommutativeMonoid op_commutative_monoid, OpCommutativeGroup op_commutative_group, OpNorm op_norm) {
           { op_quotient(a, b) } -> std::convertible_to<SetT>;
           { op_remainder(a, b) } -> std::convertible_to<SetT>;
           { op_norm(a) } -> NaturalNumber;
           UL_SEMANTICS {
               b != commutative_group_identity;
               a == op_commutative_group(op_commutative_monoid(op_quotient(a, b), b), op_remainder(a, b));
               (op_norm(a) == commutative_group_identity) == (a == commutative_group_identity);
               op_norm(op_commutative_monoid(a, b)) >= op_norm(a);
               op_norm(op_remainder(a, b)) <= op_norm(b);
           };
       };

template <Set S>
struct Abs {
    auto operator()(const S& elem) const {
        if constexpr (!std::is_unsigned_v<S>) {
            return std::abs(elem);
        } else {
            return elem;
        }
    }
};

template <typename SetT>
concept EuclideanDomainAddMult = EuclideanDomain<
    SetT, std::plus<SetT>, std::negate<SetT>, std::multiplies<SetT>, std::divides<SetT>, std::modulus<SetT>, Abs<SetT>>;

template <
    typename SetT, typename OpCommutativeGroup /*add*/, typename OpInvCommutativeGroup /*add*/,
    typename OpCommutativeGroupMul /*multiply*/, typename OpInvCommutativeGroupMul /*multiply*/>
concept Field = Set<SetT> && IntegralDomain<SetT, OpCommutativeGroup, OpInvCommutativeGroup, OpCommutativeGroupMul>
                && Group<SetT, OpCommutativeGroupMul, OpInvCommutativeGroupMul>;

template <Integral N>
bool odd(N n) {
    return static_cast<bool>(n & 0x1);
}

template <Integral N>
bool even(N n) {
    return !odd(n);
}

template <Integral N>
N half(N n) {
    return n >> 1;
}

template <AdditiveGroup T>
std::negate<T> inverse_operation(std::plus<T>) {
    return std::negate<T>{};
}

template <MultiplicativeGroup T>
Reciprocal<T> inverse_operation(std::multiplies<T>) {
    return Reciprocal<T>{};
}

template <Regular ElemT, size_t m, size_t n>
using Matrix = std::array<std::array<ElemT, n>, m>;

template <typename MatrixT, typename ElemT>
concept MatrixLike = requires(MatrixT m, size_t r, size_t c) {
                         m[r];
                         m[r][c];
                         requires std::is_same_v<std::remove_cvref_t<decltype(m[r][c])>, ElemT>;
                     };

// Not yet useful. Even problematic in the difficulty of inferring template parameters.
//template <typename MatrixT, typename ElemT, size_t m, size_t n>
//concept MatrixMNLike = MatrixLike<MatrixT, ElemT> && requires(MatrixT mat, size_t r, size_t c) {
//    mat[0];
//    mat[m - 1];
//    mat[0][0];
//    mat[0][n - 1];
//    mat[m - 1][0];
//    mat[m - 1][n - 1];
//};

template <Regular ElemT, size_t m, size_t n>
std::ostream& operator<<(std::ostream& os, const Matrix<ElemT, m, n>& matrix) {
    for (decltype(m) i{}; i < m; ++i) {
        os << "[";
        for (decltype(n) j{}; j < n; ++j)
            os << " " << matrix[i][j];
        os << " ]\n";
    }
    return os;
}

template <
    Set ElemT, size_t m, size_t k, size_t n, CommutativeMonoidOperation<ElemT> OpElemCommutativeMonoid /*add*/,
    MonoidOperation<ElemT> OpElemMonoid /*multiply*/>
    requires SemiRing<ElemT, OpElemCommutativeMonoid, OpElemMonoid>
auto multiply(
    Matrix<ElemT, m, k> l, Matrix<ElemT, k, n> r, OpElemCommutativeMonoid&& inner_add, OpElemMonoid&& inner_mul) {
    Matrix<ElemT, m, n> res{};
    for (decltype(m) i{}; i < m; ++i)
        for (decltype(k) h{}; h < k; ++h)
            for (decltype(n) j{}; j < n; ++j)
                res[i][j] = inner_add(res[i][j], inner_mul(l[i][h], r[h][j]));
    return res;
}

template <SemiRingAddMult ElemT, size_t m, size_t k, size_t n>
auto multiply(Matrix<ElemT, m, k> l, Matrix<ElemT, k, n> r) {
    return multiply(l, r, std::plus<ElemT>{}, std::multiplies<ElemT>{});
}

template <SemiRingAddMult ElemT, size_t m, size_t k, size_t n>
auto operator*(Matrix<ElemT, m, k> l, Matrix<ElemT, k, n> r) {
    return multiply(l, r);
}

template <SemiRingAddMult ElemT, MatrixLike<ElemT> M>
struct MatMul {
    M operator()(const M& a1, const M& a2) const {
        return a1 * a2;
    }
};

template <SemiRingAddMult ElemT, MatrixLike<ElemT> M>
struct MatMulGenBool {
    M operator()(const M& a1, const M& a2) const {
        return multiply(a1, a2, std::logical_or<ElemT>{}, std::logical_and<ElemT>{});
    }
};

template <NoncommutativeAdditiveMonoid A>
struct Min {
    A operator()(const A& a1, const A& a2) const {
        return std::min(a1, a2);
    }
};

template <SemiRingAddMult ElemT, size_t m, size_t k, size_t n>
struct MatMulGenTropical {
    Matrix<ElemT, m, n> operator()(const Matrix<ElemT, m, k>& a1, const Matrix<ElemT, k, n>& a2) const {
        return multiply(a1, a2, Min<ElemT>{}, std::plus<ElemT>{});
    }
};

struct Tropical {
    static constexpr auto inf{std::numeric_limits<double>::infinity()};

    constexpr Tropical() noexcept = default;

    constexpr /*implicit*/ Tropical(double d) noexcept
        : d_{d} {
    }

    constexpr /*implicit*/ operator double() const noexcept {
        return d_;
    }

    auto operator<=>(const Tropical&) const noexcept = default;

private:
    double d_{inf};
};

template <MultiplicativeSemigroup A, Integral N>
A power_accumulate_semigroup(A r, A a, N n) {
    UL_EXPECT(n >= 0);
    if (n == 0)
        return r;
    while (true) {
        if (odd(n)) {
            r *= a;
            if (n == 1)
                return r;
        }
        n = half(n);
        a *= a;
    }
}

template <MultiplicativeSemigroup A, Integral N>
A power_semigroup(A a, N n) {
    UL_EXPECT(n > 0);
    while (!odd(n)) {
        a *= a;
        n = half(n);
    }
    if (n == 1)
        return a;
    return power_accumulate_semigroup(a, a * a, half(n - 1));
}

template <MultiplicativeMonoid A, Integral N>
A power_monoid(A a, N n) {
    UL_EXPECT(n >= 0);
    if (n == 0)
        return A{1};
    return power_semigroup(a, n);
}

template <Regular A, Integral N, SemigroupOperation Op>
A power_accumulate_semigroup(A r, A a, N n, Op op) {
    UL_EXPECT(n >= 0);
    if (n == 0)
        return r;
    while (true) {
        if (odd(n)) {
            r = op(r, a);
            if (n == 1)
                return r;
        }
        n = half(n);
        a = op(a, a);
    }
}

/// For a multiply operation as op you achieve the canonical 'power'.
template <Regular A, Integral N, SemigroupOperation Op>
A power_semigroup(A a, N n, Op op) {
    UL_EXPECT(n > 0);
    while (!odd(n)) {
        a = op(a, a);
        n = half(n);
    }
    if (n == 1)
        return a;
    return power_accumulate_semigroup(a, op(a, a), half(n - 1), op);
}

template <Regular A, Integral N, MonoidOperation<A> Op>
A power_monoid(A a, N n, Op op, A identity) {
    UL_EXPECT(n >= 0);
    if (n == 0)
        return identity;
    return power_semigroup(a, n, op);
}

template <Regular A, Integral N, GroupOperation<A> Op, GroupInverseOperation<A> InvOp>
A power_group(A a, N n, Op op, InvOp invop, A identity) {
    if (n < 0) {
        n = -n;
        a = invop(a);
    }
    return power_monoid(a, n, op, identity);
}

template <Integer I>
bool divides(I i, I n) {
    UL_EXPECT(i != I{0});
    return n % i == I{0};
}

/// Other than the trivial 1.
template <Integer I>
I smallest_divisor(I n) {
    UL_EXPECT(n > I{0});
    if (even(n))
        return I{2};
    for (I i{3}; i * i <= n; i += I{2}) {
        if (divides(i, n))
            return i;
    }
    return n;
}

/// Beware: slow, just to be used sparingly.
template <Integer I>
I is_prime(I n) {
    return n > I{1} && smallest_divisor(n) == n;
}

template <Integer I>
struct ModuloMultiply {
    I modulus{};

    explicit ModuloMultiply(I i)
        : modulus(i) {
    }

    I operator()(I n, I m) const {
        return (n * m) % modulus;
    }
};

template <Integer I>
I identity_element(ModuloMultiply<I>) {
    return I{1};
}

template <Integer I>
I multiplicative_inverse_fermat(I a, I p) {
    UL_EXPECT(is_prime(p) && a > I{0});
    return power_monoid(a, p - 2, ModuloMultiply<I>(p));
}

/// Reads: n no prime if false, probably prime if true, more probable for more witnesses.
template <Integer I>
bool fermat_test(I n, I witness) {
    UL_EXPECT(I{0} < witness);
    UL_EXPECT(witness < n);
    I remainder{power_semigroup(witness, n - I{1}, ModuloMultiply<I>(n))};
    return remainder == I{1};
}

template <Integer I>
bool miller_rabin_test(I n, I q, I k, I w) {
    UL_EXPECT(n > 1);
    UL_EXPECT(n - 1 == 2 * k * q);
    UL_EXPECT(odd(q));
    ModuloMultiply<I> mmult{n};
    I x = power_semigroup(w, q, mmult);
    if (x == I{1} || x == n - I{1})
        return true;
    for (I i{1}; i < k; ++i) {
        // invariant x = w^(2^(i−1)q)
        x = mmult(x, x);
        if (x == n - I{1})
            return true;
        if (x == I{1})
            return false;
    }
    return false;
}
} // namespace math

#endif
