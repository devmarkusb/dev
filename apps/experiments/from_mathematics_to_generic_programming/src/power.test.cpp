#include "power.h"
#include "gtest/gtest.h"

TEST(power_accumulate_semigroup, tests)
{
    EXPECT_EQ(math::power_accumulate_semigroup(1, 2, 3), 8);
    EXPECT_EQ(math::power_accumulate_semigroup(2, 2, 3), 16);
}

TEST(power_semigroup, tests)
{
    EXPECT_EQ(math::power_semigroup(2, 4, [](auto l, auto r) { return l + r;}), 8);
}

TEST(power_monoid, tests)
{
}

TEST(power_group, tests)
{
}
