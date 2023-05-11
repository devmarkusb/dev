#include "math.h"
#include "ex-for-test.h"

#include "gtest/gtest.h"
#include <functional>

using Int = int;
using UInt = unsigned int;
constexpr Int someInt{42};
const std::string str42{"42"};
const std::string str43{"43"};
constexpr UInt uint42{42};
constexpr UInt uint43{43};
const std::string strComma{","};
constexpr auto colVec1{math::Matrix<Int, 2, 1>{{{1}, {2}}}};
constexpr auto rowVec1{math::Matrix<Int, 1, 2>{{{1, 2}}}};
constexpr auto scalar1{math::Matrix<Int, 1, 1>{{{5}}}};
constexpr auto matrix2x2_1{math::Matrix<Int, 2, 2>{{{1, 2}, {2, 4}}}};
constexpr auto matrix2x2_2{math::Matrix<Int, 2, 2>{{{5, 10}, {10, 20}}}};
constexpr auto colVec2{math::Matrix<Int, 2, 1>{{{5}, {10}}}};
constexpr auto rowVec2{math::Matrix<Int, 1, 2>{{{5, 10}}}};

struct RegularEx {};

bool operator==(RegularEx, RegularEx) {
    return true;
}

TEST(regular, tests) {
    const auto copy{[](math::Regular auto r) {
        return r;
    }};
    EXPECT_EQ(copy(someInt), someInt);
    EXPECT_EQ(copy(RegularEx{}), RegularEx{});
}

TEST(semigroup, tests) {
    const auto op{[](math::NoncommutativeAdditiveSemigroup auto a, math::NoncommutativeAdditiveSemigroup auto b) {
        return a + b;
    }};
    EXPECT_EQ(op(str42, str43), "4243");
    EXPECT_EQ(op(str43, str42), "4342");
    EXPECT_NE(op(str42, str43), op(str43, str42));
    EXPECT_EQ(op(op(str42, strComma), str43), op(str42, op(strComma, str43)));

    const NoncommutativeAdditiveSemigroupEx a{"1"};
    const NoncommutativeAdditiveSemigroupEx b{"2"};
    const NoncommutativeAdditiveSemigroupEx c{"3"};
    EXPECT_EQ(op(op(a, b), c), op(a, op(b, c)));
}

TEST(monoid, tests) {
    const auto op{[](math::NoncommutativeAdditiveMonoid auto a, math::NoncommutativeAdditiveMonoid auto b) {
        return a + b;
    }};
    EXPECT_EQ(op(str42, str43), "4243");
    EXPECT_EQ(op(str43, str42), "4342");
    EXPECT_NE(op(str42, str43), op(str43, str42));
    EXPECT_EQ(op(op(str42, strComma), str43), op(str42, op(strComma, str43)));

    const NoncommutativeAdditiveMonoidEx a{"1"};
    const NoncommutativeAdditiveMonoidEx b{"2"};
    const NoncommutativeAdditiveMonoidEx c{"3"};
    const NoncommutativeAdditiveMonoidEx id{};
    EXPECT_EQ(op(op(a, b), c), op(a, op(b, c)));
    EXPECT_EQ(op(id, c), c);
}

TEST(group, tests) {
    const auto op{[](math::NoncommutativeAdditiveGroup auto a, math::NoncommutativeAdditiveGroup auto b) {
        return a + b;
    }};
    EXPECT_EQ(op(str42, str43), "4243");
    EXPECT_EQ(op(str43, str42), "4342");
    EXPECT_NE(op(str42, str43), op(str43, str42));
    EXPECT_EQ(op(op(str42, strComma), str43), op(str42, op(strComma, str43)));

    const NoncommutativeAdditiveGroupEx a{1};
    const NoncommutativeAdditiveGroupEx b{2};
    const NoncommutativeAdditiveGroupEx c{3};
    const NoncommutativeAdditiveGroupEx id{};
    const NoncommutativeAdditiveGroupEx inv_b{-2};
    EXPECT_EQ(op(op(a, b), c), op(a, op(b, c)));
    EXPECT_EQ(op(id, c), c);
    EXPECT_EQ(op(b, inv_b), id);
    EXPECT_EQ(op(inv_b, b), id);
}

TEST(semiring, tests) {
    const auto exampleOp{[](math::SemiRingAddMult auto a, math::SemiRingAddMult auto b, math::SemiRingAddMult auto c) {
        return (a + b) * c;
    }};

    SemiRingOpCommMonoidEx semiRingOpCommMonoidEx{};
    SemiRingOpMonoidEx semiRingOpMonoidEx{};

    EXPECT_EQ(semiRingOpCommMonoidEx(uint42, uint43), 85);
    EXPECT_EQ(semiRingOpCommMonoidEx(uint43, uint42), 85);
    EXPECT_EQ(semiRingOpCommMonoidEx(uint42, uint43), semiRingOpCommMonoidEx(uint43, uint42));
    EXPECT_EQ(
        semiRingOpCommMonoidEx(semiRingOpCommMonoidEx(uint42, 1), uint43),
        semiRingOpCommMonoidEx(uint42, semiRingOpCommMonoidEx(1, uint43)));

    EXPECT_EQ(semiRingOpMonoidEx(2, 3), 6);
    EXPECT_EQ(
        semiRingOpMonoidEx(semiRingOpMonoidEx(uint42, 2), uint43),
        semiRingOpMonoidEx(uint42, semiRingOpMonoidEx(2, uint43)));

    const SemiRingEx idCommMonoid{};
    const SemiRingEx idMonoid{1};
    EXPECT_EQ(exampleOp(idCommMonoid, 2, idMonoid), 2);
    EXPECT_EQ(exampleOp(2, idCommMonoid, idMonoid), 2);
    EXPECT_EQ(exampleOp(2, 3, idMonoid), 5);
    EXPECT_EQ(exampleOp(2, 3, 2), 10);
}

TEST(multiply, tests) {
    using math::operator<<;
    using math::operator*;
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
    EXPECT_EQ(math::multiply(matrix2x2_1, matrix2x2_1), matrix2x2_2);
    EXPECT_EQ(matrix2x2_1 * matrix2x2_1, matrix2x2_2);
}
