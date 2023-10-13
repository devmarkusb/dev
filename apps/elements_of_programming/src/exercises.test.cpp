#include "exercises.h"
#include "gtest/gtest.h"

namespace eop
{
const auto example_nr{5};

struct terminating_orbit
{
    /// Expects x > 1.
    int operator()(int x)
    {
        --x;
        return (x + 1) / x;
    }
};

template <>
struct input_type<terminating_orbit, 0>
{
    using type = int;
};

bool terminating_orbit_pred(int x)
{
    return x > 1;
}

/// Cycle size 5. Handle size 1 or 0 for x >= -1, more for x < -1.
int non_terminating_orbit(int x)
{
    return (x + 1) % example_nr;
}
} // namespace eop

using namespace eop;

TEST(intersectTest, misc)
{
    //EXPECT_TRUE(intersect(example_nr, 2, terminating_orbit{}, terminating_orbit_pred));
}
