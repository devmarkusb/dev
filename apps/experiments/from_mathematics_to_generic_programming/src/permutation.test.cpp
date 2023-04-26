#include "permutation.h"

#include "gtest/gtest.h"

TEST(gries_mills_rotate, tests)
{
    auto arr{std::array{0, 1, 2, 3, 4}};
    math::gries_mills_rotate(std::begin(arr), std::begin(arr) + 2, std::end(arr));
    EXPECT_EQ(arr, std::array{2, 3, 4, 0, 1});
}
