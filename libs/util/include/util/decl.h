/** A broad collection of very general concepts, types/traits, etc. that could be std material. */

#ifndef DECL_H_43EBEDD3AEE24DB097CA8864DFB68497
#define DECL_H_43EBEDD3AEE24DB097CA8864DFB68497

#include "ul/ul.h"
#include <concepts>

namespace mb::ul {
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

template <typename P>
concept Procedure = std::invocable<P>;

//todo refine (or not? without restricting too much at least)
template <typename F, typename... Args>
concept FunctionalProcedure = std::regular_invocable<F, Args...> && !std::is_same_v<void, std::invoke_result_t<F, Args...>>;

template <FunctionalProcedure, int>
struct InputTypeDecl;

template <FunctionalProcedure F, int i>
using InputType = InputTypeDecl<F, i>::Type;

template <FunctionalProcedure F>
using Domain = InputType<F, 0>;

template <FunctionalProcedure>
struct CodomainDecl;

template <FunctionalProcedure F>
using Codomain = CodomainDecl<F>::Type;

//todo refine?
template <typename F, typename... Args>
concept HomogeneousFunction = FunctionalProcedure<F, Args...> && std::is_same_v<Args...>;

template <typename Op, typename... Args>
concept Operation =
    HomogeneousFunction<Op, Args...> && std::is_same_v<Domain<Op>, Codomain<Op>>
    && requires(Op op, ul::Domain<Op> a, ul::Domain<Op> b, ul::Domain<Op> c) {
           { op(a, b) } -> std::convertible_to<ul::Domain<Op>>;
       };

template <typename Op>
concept BinaryOperation = Operation<Op, Domain<Op>, Domain<Op>> && std::invocable<Op, Domain<Op>, Domain<Op>>;

template <typename T>
struct InputTypeDecl<std::plus<T>, 0> {
    using Type = T;
};

template <typename T>
struct CodomainDecl<std::plus<T>> {
    using Type = T;
};
} // namespace mb::ul

UL_HEADER_END

#endif
