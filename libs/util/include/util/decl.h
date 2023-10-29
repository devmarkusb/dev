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

template <typename F>
concept FunctionalProcedure = std::regular_invocable<F>;

template <FunctionalProcedure F, int i>
struct InputTypeDecl;

template <FunctionalProcedure F, int i>
using InputType = InputTypeDecl<F, i>::Type;
}

UL_HEADER_END

#endif
