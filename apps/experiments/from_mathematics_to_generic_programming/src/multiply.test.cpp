#include "multiply.h"
#include "gtest/gtest.h"

TEST(multiply_accumulate_semigroup, tests)
{
    EXPECT_EQ(math::multiply_accumulate_semigroup(0, 3, 4), 12);
    EXPECT_EQ(math::multiply_accumulate_semigroup(1, 3, 4), 13);
}
