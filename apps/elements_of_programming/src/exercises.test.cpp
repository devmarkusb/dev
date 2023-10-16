#include "exercises.h"
#include "gtest/gtest.h"

namespace eop {
const auto cycle_size{5};
const auto orbit_terminator{100};
const auto orbit_separator{50};

template <typename T>
using TransformationFctByValue = T(*)(T);

template <>
struct input_type<TransformationFctByValue<int>, 0> {
    using type = int;
};

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

void non_terminating_orbit_dump() {
    const auto example_count{20};
    for (auto i{0}; i <= example_count; ++i)
        std::cout << power_unary(-4, i, non_terminating_orbit) << ",";
    std::cout << std::endl;
    for (auto i{0}; i <= example_count; ++i)
        std::cout << power_unary(-16, i, non_terminating_orbit) << ",";
    std::cout << std::endl;
    for (auto i{0}; i <= example_count; ++i)
        std::cout << power_unary(-15, i, non_terminating_orbit) << ",";
    std::cout << std::endl;
    for (auto i{0}; i <= example_count; ++i)
        std::cout << power_unary(-14, i, non_terminating_orbit) << ",";
    std::cout << std::endl;
    for (auto i{0}; i <= example_count; ++i)
        std::cout << power_unary(-1, i, non_terminating_orbit) << ",";
    std::cout << std::endl;
    for (auto i{0}; i <= example_count; ++i)
        std::cout << power_unary(0, i, non_terminating_orbit) << ",";
    std::cout << std::endl;
    for (auto i{0}; i <= example_count; ++i)
        std::cout << power_unary(1, i, non_terminating_orbit) << ",";
    std::cout << std::endl;
    for (auto i{0}; i <= example_count; ++i)
        std::cout << power_unary(42, i, non_terminating_orbit) << ",";
    std::cout << std::endl;
}

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
} // namespace eop

using namespace eop;

TEST(intersectTest, both_terminating) {
    EXPECT_TRUE(intersect(orbit_terminator / 2, 1, terminating_orbit, terminating_orbit_pred));
}

TEST(intersectTest, terminating_and_circular) {
    non_terminating_orbit_dump();
   EXPECT_FALSE(intersect(orbit_separator - 1, orbit_separator + 1, orbit, orbit_pred));
}
