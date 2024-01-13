#include "exercises.h"
#include "eop-code/intrinsics.h"
#include "eop-code/tests.h"
#include "gtest/gtest.h"
#include <optional>

namespace eop {
const auto cycle_size{5};
const auto orbit_terminator{100};
const auto orbit_separator{50};
const auto pos_example_nr{42};
const auto neg_example_nr{-15};

template <typename T>
using TransformationFctByValue = T (*)(T);

template <typename T>
struct input_type<TransformationFctByValue<T>, 0> {
    using type = T;
};

template <typename F, typename N, typename P>
REQUIRES(Transformation(F) && Integer(N) && UnaryPredicate(P) && Domain(F) == Domain(P))
std::optional<Domain(F)> power_unary_guarded(Domain(F) x, N n, F f, P p) {
    UL_EXPECT(n >= 0);
    while (n != N{0}) {
        n = n - N{1};
        if (!p(x)) {
            return {};
        }
        x = f(x);
    }
    return x;
}

//! Expects x < orbit_terminator.
int terminating_orbit(int x) {
    UL_EXPECT(x < orbit_terminator);
    if (x >= orbit_terminator)
        throw std::overflow_error{"terminating_orbit"};
    return ++x;
}

static_assert(std::is_same_v<TransformationFctByValue<int>, decltype(&terminating_orbit)>);

bool terminating_orbit_pred(int x) {
    return x < orbit_terminator;
}

//! Cycle size 5. Handle size 0 for 0 <= x <= 4, 1 for -1 and >= 5, up to 5 for <= -2
int non_terminating_orbit(int x) {
    return (x + 1) % cycle_size;
}

static_assert(std::is_same_v<TransformationFctByValue<int>, decltype(&non_terminating_orbit)>);

int orbit(int x) {
    if (x >= orbit_separator)
        return terminating_orbit(x);
    else
        return non_terminating_orbit(x);
}

static_assert(std::is_same_v<TransformationFctByValue<int>, decltype(&orbit)>);

bool orbit_pred(int x) {
    return x < orbit_terminator;
}

bool hf_pred(int) {
    return true;
}

template <typename F, typename P>
REQUIRES(Transformation(F) && UnaryPredicate(P) && Domain(F) == Domain(P))
std::ostream& orbit_dump(std::ostream& os, F f, P p, Domain(F) starting_point, int example_count) {
    for (auto i{0}; i <= example_count; ++i) {
        const auto x{power_unary_guarded(starting_point, i, f, p)};
        if (x)
            os << *x << ',';
        else {
            os << "terminated";
            break;
        }
    }
    os << '\n';
    return os;
}

template <typename F, typename P>
REQUIRES(Transformation(F) && UnaryPredicate(P) && Domain(F) == Domain(P))
std::ostream& orbit_dump(std::ostream& os, F f, P p, std::string_view loglabel) {
    const auto example_count{50};
    os << loglabel << " orbit_dump\n";
    orbit_dump(os, f, p, -4, example_count);
    orbit_dump(os, f, p, neg_example_nr - 1, example_count);
    orbit_dump(os, f, p, neg_example_nr, example_count);
    orbit_dump(os, f, p, neg_example_nr + 1, example_count);
    orbit_dump(os, f, p, -1, example_count);
    orbit_dump(os, f, p, 0, example_count);
    orbit_dump(os, f, p, 1, example_count);
    orbit_dump(os, f, p, pos_example_nr, example_count);
    orbit_dump(os, f, p, pos_example_nr * 2, example_count);
    return os;
}
} // namespace eop

using namespace eop;

TEST(intersectTest, dumps) {
    orbit_dump(std::cout, terminating_orbit, terminating_orbit_pred, "terminating_orbit");
    std::stringstream ss;
    orbit_dump(ss, terminating_orbit, terminating_orbit_pred, "terminating_orbit");
    EXPECT_EQ(ss.str(), R"(terminating_orbit orbit_dump
-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,
-16,-15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,
-15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,
-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,
-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,
1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,
42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,
84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,terminated
)");
    orbit_dump(
        std::cout, non_terminating_orbit,
        [](int) {
            return true;
        },
        "non_terminating_orbit");
    orbit_dump(std::cout, orbit, orbit_pred, "orbit");
    const auto o{gen_orbit<int, DistanceType(int)>{-20, 20, 5}};
    orbit_dump(std::cout, o, o.p, "gen_orbit");
}

TEST(intersectTest, both_terminating) {
    EXPECT_TRUE(intersect(orbit_terminator / 2, 1, terminating_orbit, terminating_orbit_pred));
}

TEST(intersectTest, non_terminating_and_terminating) {
    EXPECT_FALSE(intersect(orbit_separator - 2, orbit_separator + 2, orbit, orbit_pred));
    EXPECT_FALSE(intersect(orbit_separator + 2, orbit_separator - 2, orbit, orbit_pred));
}

TEST(intersectTest, both_non_terminating) {
    // both circular
    EXPECT_TRUE(intersect(0, pos_example_nr, orbit, orbit_pred));
    EXPECT_TRUE(intersect(pos_example_nr, 0, orbit, orbit_pred));
    EXPECT_TRUE(intersect(0, 2, orbit, orbit_pred));
    EXPECT_TRUE(intersect(2, 0, orbit, orbit_pred));
    // circular and \rho-shaped
    EXPECT_TRUE(intersect(pos_example_nr, 2, orbit, orbit_pred));
    EXPECT_TRUE(intersect(2, pos_example_nr, orbit, orbit_pred));
    EXPECT_TRUE(intersect(-1, 2, orbit, orbit_pred));
    EXPECT_TRUE(intersect(2, -1, orbit, orbit_pred));
    // both \rho-shaped
    EXPECT_TRUE(intersect(pos_example_nr, -2, orbit, orbit_pred));
    EXPECT_TRUE(intersect(-2, pos_example_nr, orbit, orbit_pred));
    EXPECT_TRUE(intersect(-2, -1, orbit, orbit_pred));
}

TEST(convergent_point_guardedTest, misc) {
    EXPECT_TRUE(convergent_point_guarded(1024, 64, hf<int>{}, hf_pred) == 64);
    EXPECT_TRUE(convergent_point_guarded(1025, 65, hf<int>{}, hf_pred) == 32);
    EXPECT_TRUE(convergent_point_guarded(64, 1024, hf<int>{}, hf_pred) == 64);
    EXPECT_TRUE(convergent_point_guarded(65, 1025, hf<int>{}, hf_pred) == 32);
    EXPECT_TRUE(convergent_point_guarded(1024, 2047, hf<int>{}, hf_pred) == 1);
}
