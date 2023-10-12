#ifndef EXERCISES_H_FBE9B1D27DBF4A7CBD27E83431D2624B
#define EXERCISES_H_FBE9B1D27DBF4A7CBD27E83431D2624B

#include "eop-code/intrinsics.h"
#include "eop-code/type_functions.h"

namespace eop {
// Chapter 2

// 2.2
template <typename F, typename P>
REQUIRES(Transformation(F) && UnaryPredicate(P) && Domain(F) == Domain(P))
bool intersect(Domain(F) x, Domain(F) y, F f, P p) {
    // for any x in Domain(F): p(x) <=> f(x) defined
    //todo
}
}

#endif
