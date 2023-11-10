#ifndef EXERCISES_H_FBE9B1D27DBF4A7CBD27E83431D2624B
#define EXERCISES_H_FBE9B1D27DBF4A7CBD27E83431D2624B

#include "eop-code/intrinsics.h"
#include "eop-code/type_functions.h"
#include "eop-code/eop.h"
#include <cstdlib>
#include <optional>
#include <random>
#include <string_view>
#include <thread>

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

inline int rand_gen_legacy(int seed) {
    std::srand(static_cast<unsigned int>(seed));
    return std::rand();
}

template <ul::Transformation F>
inline void print_orbit_structure_random_nr_generator(std::mutex& stdout_mutex, ul::Domain<F> x, F f, std::string_view f_as_str) {
    auto [m0, m1, m2]{
        ul::orbit_structure_nonterminating_orbit(x, f)};
    const std::lock_guard lk{stdout_mutex};
    std::cout << f_as_str << ", starting point=" << x << '\n';
    if (!m0)
        std::cout << "    circular: c-1=" << m1 << '\n';
    else
        std::cout << "    \\rho-shaped: h=" << m0 << ", c-1=" << m1 << ", connection point=" << m2 << '\n';
    std::cout << '\n';
}

inline void print_orbit_structure_random_nr_generators() {
    const auto x{0};
    std::mutex stdout_mutex;
    std::vector<std::jthread> t;
    t.emplace_back([&stdout_mutex]() {
        print_orbit_structure_random_nr_generator(
            stdout_mutex, x, rand_gen<std::default_random_engine>, "std::default_random_engine");
    });
    t.emplace_back([&stdout_mutex]() {
        print_orbit_structure_random_nr_generator(stdout_mutex, x, rand_gen<std::mt19937>, "std::mt19937");
    });
    // taking too long, but that was one output:
    //     std::mt19937_64, starting point=0
    //         \rho-shaped: h=349528656, c-1=4664684600, connection point=6974110543638746052
    // t.emplace_back([&stdout_mutex]() {
    //     print_orbit_structure_random_nr_generator(stdout_mutex, x, rand_gen<std::mt19937_64>, "std::mt19937_64");
    // });
    t.emplace_back([&stdout_mutex]() {
        print_orbit_structure_random_nr_generator(stdout_mutex, x, rand_gen<std::minstd_rand>, "std::minstd_rand");
    });
    t.emplace_back([&stdout_mutex]() {
        print_orbit_structure_random_nr_generator(stdout_mutex, x, rand_gen<std::ranlux24_base>, "std::ranlux24_base");
    });
    t.emplace_back([&stdout_mutex]() {
        print_orbit_structure_random_nr_generator(stdout_mutex, x, rand_gen<std::ranlux48_base>, "std::ranlux48_base");
    });
    t.emplace_back([&stdout_mutex]() {
        print_orbit_structure_random_nr_generator(stdout_mutex, x, rand_gen<std::knuth_b>, "std::knuth_b");
    });
    t.emplace_back([&stdout_mutex]() {
        print_orbit_structure_random_nr_generator(stdout_mutex, x, rand_gen_legacy, "(s)rand");
    });
}
} // namespace eop

#endif
