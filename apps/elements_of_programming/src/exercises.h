#ifndef EXERCISES_H_FBE9B1D27DBF4A7CBD27E83431D2624B
#define EXERCISES_H_FBE9B1D27DBF4A7CBD27E83431D2624B

#include "eop-code/intrinsics.h"
#include "eop-code/type_functions.h"

#include "eop-code/eop.h"

namespace eop {
// Chapter 2
// Remember: the precondition everywhere here is that all orbits are finite.
// So we are left with terminating or \rho-shaped or circular.

// 2.2
template <typename F, typename P>
REQUIRES(Transformation(F) && UnaryPredicate(P) && Domain(F) == Domain(P))
bool intersect(Domain(F) x, Domain(F) y, F f, P p) {
    // for any x in Domain(F): p(x) <=> f(x) defined
    const auto x_coll{collision_point(x, f, p)};
    const auto y_coll{collision_point(y, f, p)};

    // Since intersection implies having in common all cyclic elements, the contraposition that there
    // is a cyclic element (and therefore a cycle) for x (or y), but none for y (or x), i.e. y (or x)
    // is terminating, we can return false immediately.
    if (p(x_coll) != p(y_coll))
        return false;

    if (!p(x_coll))
    {
        // Case of two terminating orbits.
        // They intersect, if they have the last element in common. Intersection means having at least
        // one element in common. But that implies having all the following ones - applying the
        // transformation, in common also.
        return p(x_coll) == p(y_coll);
    }
    else
    {
        // Case of two non-terminating orbits (\rho-shaped or cyclic).
        // If they intersect, they have in common all cyclic elements. But the converse is also true for
        // orbits with non-empty common cycles.
        // Intersection happens, when the connection point of one orbit is reachable by the other.
        const auto x_conn{convergent_point(x, f(x_coll), f)};
        const auto y_conn{convergent_point(y, f(y_coll), f)};
        for (auto x_runner{x_conn}; x_runner != x_conn; x_runner = f(x_runner))
        {
            if (x_runner == y_conn)
                return true;
        }
        return false;
    }
}
} // namespace eop

#endif
