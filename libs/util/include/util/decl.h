/** A broad collection of very general concepts, types/traits, etc. that could be std material. */

#ifndef DECL_H_43EBEDD3AEE24DB097CA8864DFB68497
#define DECL_H_43EBEDD3AEE24DB097CA8864DFB68497

#include "ul/ul.h"
#include <concepts>

namespace mb::ul {
inline namespace more_generic {
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
} // namespace more_generic

namespace generic {
/**
    Opposed to Regular from most_generic_regular implies default initializable also. This allows for the equivalence
    of 'T a; a = b;' and ' T a{b};'.
 */
template <typename R>
concept Regular = std::regular<R>;

template <typename R>
concept SemiRegular = std::semiregular<R>;
} // namespace generic

template <typename P>
concept Procedure = std::invocable<P>;

namespace most_generic {
template <typename>
concept FunctionalProcedure = true;
}

//todo refine (or not? without restricting too much at least)
template <typename F, typename... Args>
concept FunctionalProcedure = std::regular_invocable<F, Args...> && !std::is_same_v<void, std::invoke_result_t<F, Args...>>;

template <int, most_generic::FunctionalProcedure>
struct InputTypeDecl;

template <int i, most_generic::FunctionalProcedure F>
using InputType = InputTypeDecl<i, F>::Type;

template <most_generic::FunctionalProcedure F>
using Domain = InputType<0, F>;

template <most_generic::FunctionalProcedure>
struct CodomainDecl;

template <most_generic::FunctionalProcedure F>
using Codomain = CodomainDecl<F>::Type;

//todo refine?
template <typename F, typename... Args>
concept HomogeneousFunction = FunctionalProcedure<F, Args...> && std::is_same_v<Args...>;

template <typename Op, typename... Args>
concept Operation =
    HomogeneousFunction<Op, Args...> && std::is_convertible_v<Domain<Op>, Codomain<Op>>
    && requires(Op op, ul::Domain<Op> a, ul::Domain<Op> b, ul::Domain<Op> c) {
           { op(a, b) } -> std::convertible_to<ul::Domain<Op>>;
       };

template <typename Op>
concept BinaryOperation = Operation<Op, Domain<Op>, Domain<Op>> && std::invocable<Op, Domain<Op>, Domain<Op>>;

template<typename ArgTypes>
struct FirstArg
{
    using Type = std::tuple_element_t<0, ArgTypes>;
};

template<>
struct FirstArg<std::tuple<>>
{
    using Type = void;
};

template<typename T>
struct Method
{
    using Type = void;
};

template<typename Ret, typename Type, typename... Args>
struct Method<Ret (Type::*)(Args...) const>
{
    using ReturnType = Ret;
    using ArgsTuple = std::tuple<Args...>;
    using FirstArgType = typename FirstArg<ArgsTuple>::Type;
};

template<typename F>
using CallOperator = Method<decltype(&F::operator())>;

template <typename F>
struct InputTypeDecl<0, F> {
    using Type = std::remove_cvref_t<typename CallOperator<F>::FirstArgType>;
private:
    using TypeForCheck = CallOperator<F>::FirstArgType;
    static_assert((std::is_reference_v<TypeForCheck> && std::is_const_v<std::remove_reference_t<TypeForCheck>>)
                  || (std::is_pointer_v<TypeForCheck> &&  std::is_const_v<std::remove_pointer_t<TypeForCheck>>)
                  || (!std::is_pointer_v<TypeForCheck> && !std::is_reference_v<TypeForCheck>),
                  "arguments have to by regular types, but we want to allow `const a*` and `const a&` as well");
};

template <most_generic::FunctionalProcedure F>
struct CodomainDecl {
    using Type = CallOperator<F>::ReturnType;
};
} // namespace mb::ul

UL_HEADER_END

#endif
