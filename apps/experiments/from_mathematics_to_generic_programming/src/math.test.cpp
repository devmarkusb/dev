#include "math.h"
#include "gtest/gtest.h"
#include <functional>

using Int = int;
constexpr auto colVec1{math::Matrix<Int, 2, 1>{{{1}, {2}}}};
constexpr auto rowVec1{math::Matrix<Int, 1, 2>{{{1, 2}}}};
constexpr auto scalar1{math::Matrix<Int, 1, 1>{{{5}}}};
constexpr auto matrix2x2_1{math::Matrix<Int, 2, 2>{{{1, 2}, {2, 4}}}};
constexpr auto matrix2x2_2{math::Matrix<Int, 2, 2>{{{5, 10}, {10, 20}}}};
constexpr auto colVec2{math::Matrix<Int, 2, 1>{{{5}, {10}}}};
constexpr auto rowVec2{math::Matrix<Int, 1, 2>{{{5, 10}}}};

TEST(multiply, tests)
{
    using math::operator<<;
    std::cout << colVec1 << "\n";
    std::cout << rowVec1 << "\n";
    std::cout << scalar1 << "\n";
    std::cout << matrix2x2_1 << "\n";
    std::cout << matrix2x2_2 << "\n";
    std::cout << colVec2 << "\n";
    std::cout << rowVec2 << "\n";
    EXPECT_EQ(math::multiply(rowVec1, colVec1, std::multiplies{}, std::plus{}), scalar1);
    EXPECT_EQ(math::multiply(colVec1, rowVec1, std::multiplies{}, std::plus{}), matrix2x2_1);
    EXPECT_EQ(math::multiply(matrix2x2_1, colVec1, std::multiplies{}, std::plus{}), colVec2);
    EXPECT_EQ(math::multiply(rowVec1, matrix2x2_1, std::multiplies{}, std::plus{}), rowVec2);
    EXPECT_EQ(math::multiply(matrix2x2_1, matrix2x2_1, std::multiplies{}, std::plus{}), matrix2x2_2);
}
