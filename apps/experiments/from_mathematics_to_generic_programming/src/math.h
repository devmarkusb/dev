#ifndef MATH_H_REOGH378904H27837H3
#define MATH_H_REOGH378904H27837H3

#include "ul/ul.h"
#include <array>
#include <cmath>
#include <compare>
#include <concepts>
#include <ostream>

namespace math {
inline namespace most_generic_regular {
/**
    Opposed to std::regular this doesn't contain std::default_initializable.
    The intention of the latter might be to be able to write something like 'R x;' with possibly uninitialized x,
    perhaps modelling a mathematical 'let x be an arbitrary element of R'. But to be honest that's not needed in
    programming. You are more likely to have a function implementation of 'f(R x)' (or 'f(Regular auto x)') getting in
    an arbitrary x. Also it is the preferable principle of generalization to impose less constraints. You can still
    have it for your specific type R if you want to.

    Semantics:
        * T a{b} => (b=c => a=c)
        * a:=b => (b=c => a=c)
        * f RegularFunction and a=b => f(a)=f(b)
    Time/space complexity:
        * each operation on Regular is no worse than linear in the memory of the object
 */
template <typename R>
concept Regular = std::copyable<R> && std::equality_comparable<R>;

template <typename R>
concept SemiRegular = std::copyable<R>;
} // namespace most_generic_regular

namespace generic_regular {
/**
    Opposed to Regular from most_generic_regular implies default initializable also. This allows for the equivalence
    of 'T a; a = b;' and ' T a{b};'.
 */
template <typename R>
concept Regular = std::regular<R>;

template <typename R>
concept SemiRegular = std::semiregular<R>;
} // namespace generic_regular

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

template <typename Op, typename SetT>
concept SemigroupOperation =
    Set<SetT> && std::regular_invocable<Op, SetT, SetT> && std::is_same_v<SetT, std::invoke_result_t<Op, SetT, SetT>>
    && requires(Op op, SetT a, SetT b, SetT c) {
           { op(a, b) } -> std::convertible_to<SetT>;
           UL_SEMANTICS {
               op(op(a, b), c) == op(a, op(b, c));
           };
       };

template <typename SetT, typename Op>
concept Semigroup = Set<SetT> && SemigroupOperation<Op, SetT>;

template <typename SetT>
concept NoncommutativeAdditiveSemigroup = Semigroup<SetT, std::plus<SetT>>;

template <typename SetT>
concept MultiplicativeSemigroup = Semigroup<SetT, std::multiplies<SetT>>;

template <typename Op, typename SetT>
concept MonoidOperation = Set<SetT> && SemigroupOperation<Op, SetT> && requires(Op op, SetT a, SetT identity) {
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
} // namespace math

#endif
