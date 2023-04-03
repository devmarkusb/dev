#include "math.h"
#include "gtest/gtest.h"
#include <functional>

using Int = int;
using UInt = unsigned int;
constexpr Int someInt{42};
const std::string str42{"42"};
const std::string str43{"43"};
const std::string strComma{","};
constexpr auto colVec1{math::Matrix<Int, 2, 1>{{{1}, {2}}}};
constexpr auto rowVec1{math::Matrix<Int, 1, 2>{{{1, 2}}}};
constexpr auto scalar1{math::Matrix<Int, 1, 1>{{{5}}}};
constexpr auto matrix2x2_1{math::Matrix<Int, 2, 2>{{{1, 2}, {2, 4}}}};
constexpr auto matrix2x2_2{math::Matrix<Int, 2, 2>{{{5, 10}, {10, 20}}}};
constexpr auto colVec2{math::Matrix<Int, 2, 1>{{{5}, {10}}}};
constexpr auto rowVec2{math::Matrix<Int, 1, 2>{{{5, 10}}}};

struct RegularEx
{
};

bool operator==(RegularEx, RegularEx)
{
    return true;
}

TEST(regular, tests)
{
    const auto copy{[](math::Regular auto r)
                    {
                        return r;
                    }};
    EXPECT_EQ(copy(someInt), someInt);
    EXPECT_EQ(copy(RegularEx{}), RegularEx{});
}

struct SemiGroupEx
{
    UInt ui{};
};

bool operator==(SemiGroupEx, SemiGroupEx)
{
    return true;
}

SemiGroupEx operator+(SemiGroupEx, SemiGroupEx)
{
    return {};
}

TEST(semigroup, tests)
{
    const auto op{[](math::NoncommutativeAdditiveSemigroup auto a, math::NoncommutativeAdditiveSemigroup auto b)
                  {
                      return a + b;
                  }};
    EXPECT_EQ(op(str42, str43), "4243");
    EXPECT_EQ(op(str43, str42), "4342");
    EXPECT_NE(op(str42, str43), op(str43, str42));
    EXPECT_EQ(op(op(str42, strComma), str43), op(str42, op(strComma, str43)));

    SemiGroupEx a{1};
    SemiGroupEx b{2};
    SemiGroupEx c{3};
    EXPECT_EQ(op(op(a, b), c), op(a, op(b, c)));
}

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
    EXPECT_EQ(math::multiply(rowVec1, colVec1, std::plus<Int>{}, std::multiplies<Int>{}), scalar1);
    EXPECT_EQ(math::multiply(colVec1, rowVec1, std::plus<Int>{}, std::multiplies<Int>{}), matrix2x2_1);
    EXPECT_EQ(math::multiply(matrix2x2_1, colVec1, std::plus<Int>{}, std::multiplies<Int>{}), colVec2);
    EXPECT_EQ(math::multiply(rowVec1, matrix2x2_1, std::plus<Int>{}, std::multiplies<Int>{}), rowVec2);
    EXPECT_EQ(math::multiply(matrix2x2_1, matrix2x2_1, std::plus<Int>{}, std::multiplies<Int>{}), matrix2x2_2);
}
