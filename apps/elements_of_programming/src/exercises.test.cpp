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

template <>
struct input_type<TransformationFctByValue<int>, 0> {
    using type = int;
};

template <typename F, typename N, typename P>
REQUIRES(Transformation(F) && Integer(N) && UnaryPredicate(P) && Domain(F) == Domain(P))
std::optional<Domain(F)> power_unary_guarded(Domain(F) x, N n, F f, P p) {
    // Precondition:
    // $n \geq 0 \wedge (\forall i \in N)\,0 < i \leq n \Rightarrow f^i(x)$ is defined
    while (n != N(0)) {
        n = n - N(1);
        if (!p(x)) {
            return {};
        }
        x = f(x);
    }
    return x;
}

/// Expects x < orbit_terminator.
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

/// Cycle size 5. Handle size 0 for 0 <= x <= 4, 1 for -1 and >= 5, up to 5 for <= -2
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

template <typename F, typename P>
REQUIRES(Transformation(F) && UnaryPredicate(P) && Domain(F) == Domain(P))
void orbit_dump(F f, P p, std::string_view loglabel) {
    const auto example_count{50};
    std::cout << loglabel << " orbit_dump\n";
    for (auto i{0}; i <= example_count; ++i) {
        const auto x{power_unary_guarded(-4, i, f, p)};
        if (x)
            std::cout << *x << ',';
        else {
            std::cout << "terminated";
            break;
        }
    }
    std::cout << '\n';
    for (auto i{0}; i <= example_count; ++i) {
        const auto x{power_unary_guarded(neg_example_nr - 1, i, f, p)};
        if (x)
            std::cout << *x << ',';
        else {
            std::cout << "terminated";
            break;
        }
    }
    std::cout << '\n';
    for (auto i{0}; i <= example_count; ++i) {
        const auto x{power_unary_guarded(neg_example_nr, i, f, p)};
        if (x)
            std::cout << *x << ',';
        else {
            std::cout << "terminated";
            break;
        }
    }
    std::cout << '\n';
    for (auto i{0}; i <= example_count; ++i) {
        const auto x{power_unary_guarded(neg_example_nr + 1, i, f, p)};
        if (x)
            std::cout << *x << ',';
        else {
            std::cout << "terminated";
            break;
        }
    }
    std::cout << '\n';
    for (auto i{0}; i <= example_count; ++i) {
        const auto x{power_unary_guarded(-1, i, f, p)};
        if (x)
            std::cout << *x << ',';
        else {
            std::cout << "terminated";
            break;
        }
    }
    std::cout << '\n';
    for (auto i{0}; i <= example_count; ++i) {
        const auto x{power_unary_guarded(0, i, f, p)};
        if (x)
            std::cout << *x << ',';
        else {
            std::cout << "terminated";
            break;
        }
    }
    std::cout << '\n';
    for (auto i{0}; i <= example_count; ++i) {
        const auto x{power_unary_guarded(1, i, f, p)};
        if (x)
            std::cout << *x << ',';
        else {
            std::cout << "terminated";
            break;
        }
    }
    std::cout << '\n';
    for (auto i{0}; i <= example_count; ++i) {
        {
            const auto x{power_unary_guarded(pos_example_nr, i, f, p)};
            if (x)
                std::cout << *x << ',';
            else {
                std::cout << "terminated";
                break;
            }
        }
    }
    std::cout << '\n';
    for (auto i{0}; i <= example_count; ++i) {
        {
            const auto x{power_unary_guarded(pos_example_nr * 2, i, f, p)};
            if (x)
                std::cout << *x << ',';
            else {
                std::cout << "terminated";
                break;
            }
        }
    }
    std::cout << '\n';
}
} // namespace eop

using namespace eop;

TEST(intersectTest, dumps) {
    orbit_dump(terminating_orbit, terminating_orbit_pred, "terminating_orbit");
    orbit_dump(non_terminating_orbit, [](int) {
        return true;
    }, "non_terminating_orbit");
    orbit_dump(orbit, orbit_pred, "orbit");
    const auto o{gen_orbit<int, DistanceType(int)>{-20, 20, 5}};
    orbit_dump(o, o.p, "gen_orbit");
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
