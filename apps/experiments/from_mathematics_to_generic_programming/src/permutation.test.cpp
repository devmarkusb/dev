#include "permutation.h"

#include "gtest/gtest.h"

TEST(gries_mills_rotate, tests)
{
    constexpr auto arr_orig{std::array{0, 1, 2, 3, 4}};
    auto arr{arr_orig};
    math::gries_mills_rotate(std::begin(arr), std::begin(arr), std::end(arr));
    EXPECT_EQ(arr, arr_orig);
    math::gries_mills_rotate(std::begin(arr), std::end(arr), std::end(arr));
    EXPECT_EQ(arr, arr_orig);
    math::gries_mills_rotate(std::begin(arr), std::begin(arr) + 2, std::end(arr));
    auto arr_expected{std::array{2, 3, 4, 0, 1}};
    EXPECT_EQ(arr, arr_expected);
    arr = arr_orig;
    math::gries_mills_rotate(std::begin(arr), std::begin(arr) + 4, std::end(arr));
    arr_expected = std::array{4, 0, 1, 2, 3};
    EXPECT_EQ(arr, arr_expected);
}

TEST(gries_mills_rotate_n, tests)
{
    constexpr auto arr_orig{std::array{0, 1, 2, 3, 4}};
    auto arr{arr_orig};
    math::gries_mills_rotate_n(std::begin(arr), std::begin(arr), std::end(arr));
    EXPECT_EQ(arr, arr_orig);
    math::gries_mills_rotate_n(std::begin(arr), std::end(arr), std::end(arr));
    EXPECT_EQ(arr, arr_orig);
    math::gries_mills_rotate_n(std::begin(arr), std::begin(arr) + 2, std::end(arr));
    auto arr_expected{std::array{2, 3, 4, 0, 1}};
    EXPECT_EQ(arr, arr_expected);
    arr = arr_orig;
    math::gries_mills_rotate_n(std::begin(arr), std::begin(arr) + 4, std::end(arr));
    arr_expected = std::array{4, 0, 1, 2, 3};
    EXPECT_EQ(arr, arr_expected);
}
