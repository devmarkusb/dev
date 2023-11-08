#ifndef EXERCISES_H_FBE9B1D27DBF4A7CBD27E83431D2624B
#define EXERCISES_H_FBE9B1D27DBF4A7CBD27E83431D2624B

#include "eop-code/intrinsics.h"
#include "eop-code/type_functions.h"
#include "eop-code/eop.h"
#include <optional>
#include <random>

#include "ul/ul.h"

namespace eop {
// Chapter 2
// Remember: the precondition everywhere here is that all orbits are finite.
// So we are left with terminating or \rho-shaped or circular.

// 2.2
/** Returns an (not necessarily the earliest - use convergent_point_guarded instead) intersection point if there is
    one.*/
template <typename F, typename P>
REQUIRES(Transformation(F) && UnaryPredicate(P) && Domain(F) == Domain(P))
std::optional<Domain(F)> intersect(Domain(F) x0, Domain(F) x1, F f, P p) {
    // expect for any x in Domain(F): p(x) <=> f(x) defined
    const auto x_coll{collision_point(x0, f, p)};
    const auto y_coll{collision_point(x1, f, p)};

    // Since intersection implies having in common all cyclic elements, the contraposition that there
    // is a cyclic element (and therefore a cycle) for x (or y), but none for y (or x), i.e. y (or x)
    // is terminating, we can return false immediately.
    if (p(x_coll) != p(y_coll))
        return {};

    if (!p(x_coll)) {
        // Case of two terminating orbits.
        // They intersect, if they have the last element in common. Intersection means having at least
        // one element in common. But that implies having all the following ones - applying the
        // transformation, in common also.
        return x_coll == y_coll ? std::optional{x_coll} : std::nullopt;
    }

    // Case of two non-terminating orbits (\rho-shaped or cyclic).
    // If they intersect, they have in common all cyclic elements. But the converse is also true for
    // orbits with non-empty common cycles.
    // Intersection happens, when the connection point of one orbit is reachable by the other.
    const auto x_conn{convergent_point(x0, f(x_coll), f)};
    const auto y_conn{convergent_point(x1, f(y_coll), f)};
    if (x_conn == y_conn || f(x_conn) == y_conn)
        return y_conn;
    for (auto x_runner{f(x_conn)}; x_runner != x_conn; x_runner = f(x_runner)) {
        if (x_runner == y_conn)
            return y_conn;
    }
    return {};
}

// 2.3
// Additionally you have to know that the convergent doesn't necessarily have to appear after an equal amount of
// transformation steps applied to x0 and x1. But it is defined as the earliest/first intersection point.
template <typename F, typename P>
REQUIRES(Transformation(F) && UnaryPredicate(P) && Domain(F) == Domain(P))
Domain(F) convergent_point_guarded(Domain(F) x0, Domain(F) x1, F f, P p) {
    // expect intersect(x0, x1, f, p) true
    auto xs{intersect(x0, x1, f, p)};
    UL_EXPECT(xs);
    auto d0{distance(x0, *xs, f)};
    auto d1{distance(x1, *xs, f)};
    if (d0 < d1)
        x1 = power_unary(x1, d1 - d0, f);
    else if (d1 < d0)
        x0 = power_unary(x0, d0 - d1, f);
    return convergent_point(x0, x1, f);
}

// 2.5
/** RandGen examples: default_random_engine, mt19937, mt19937_64, minstd_rand, ranlux24_base, ranlux48_base,
    knuth_b.*/
template <typename RandGen>
typename RandGen::result_type rand_gen(typename RandGen::result_type seed) {
    RandGen gen{seed};
    return gen();
}

template <typename T>
using TransformationFctByValue = T (*)(T);

template <typename RandGen>
ul::Domain<TransformationFctByValue<typename RandGen::result_type>> trans(
    ul::Domain<TransformationFctByValue<typename RandGen::result_type>> x) {
    return x;
}

template <>
struct input_type<TransformationFctByValue<std::default_random_engine::result_type>, 0> {
    using type = std::default_random_engine::result_type;
};
} // namespace eop

namespace mb::ul {
template <>
struct DistanceTypeDecl<eop::TransformationFctByValue<unsigned long>> {
    using Type = uint64_t;
};
} // namespace mb::ul

namespace eop {
inline void print_orbit_structure_random_nr_generators() {
    ul::orbit_structure_nonterminating_orbit(42, rand_gen<std::default_random_engine>);
}
} // namespace eop

#endif
