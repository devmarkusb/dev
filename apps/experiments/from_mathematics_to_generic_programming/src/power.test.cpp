#include "power.h"
#include "gtest/gtest.h"
#include <functional>

TEST(power_accumulate_semigroup, tests) {
    EXPECT_EQ(math::power_accumulate_semigroup(1, 2, 3), 8);
    EXPECT_EQ(math::power_accumulate_semigroup(2, 2, 3), 16);
}

TEST(power_semigroup, tests) {
    // abuse as multiply
    EXPECT_EQ(math::power_semigroup(2, 4, std::plus<int>{}), 8);
    EXPECT_EQ(math::power_semigroup(2, 4, std::multiplies<int>{}), 16);
}

// aka social_net_paths
TEST(power_semigroup, transitive_closure) {
    constexpr auto dim{7};
    using ElemT = bool;
    using Matrix = math::Matrix<ElemT, dim, dim>;
    // NOLINTBEGIN
    // aka directFriends
    constexpr auto adjacencyMatrix{Matrix{{
        {1, 1, 0, 1, 0, 0, 0},
        {1, 1, 0, 0, 0, 1, 0},
        {0, 0, 1, 1, 0, 0, 0},
        {1, 0, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 1},
        {0, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 1},
    }}};
    // NOLINTEND

    EXPECT_EQ(math::power_semigroup(adjacencyMatrix, 1, math::MatMulGenBool<ElemT, Matrix>{}), adjacencyMatrix);

    using math::operator<<;
    std::cout << math::power_semigroup(adjacencyMatrix, 2, math::MatMulGenBool<ElemT, Matrix>{}) << "\n";

    std::cout << math::power_semigroup(adjacencyMatrix, dim - 1, math::MatMulGenBool<ElemT, Matrix>{}) << "\n";

    // NOLINTBEGIN
    // aka friends over max. paths
    constexpr auto transitiveClosure{Matrix{{
        {1, 1, 1, 1, 0, 1, 0},
        {1, 1, 1, 1, 0, 1, 0},
        {1, 1, 1, 1, 0, 1, 0},
        {1, 1, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 1},
        {1, 1, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 1},
    }}};
    // NOLINTEND

    EXPECT_EQ(math::power_semigroup(adjacencyMatrix, dim - 1, math::MatMulGenBool<ElemT, Matrix>{}), transitiveClosure);
}

// aka shortest_length
TEST(power_semigroup, transitive_closure2) {
    constexpr auto dim{7};
    constexpr auto inf{math::Tropical::inf};
    using Matrix = math::Matrix<math::Tropical, dim, dim>;
    using MatMulGenTropical = math::MatMulGenTropical<math::Tropical, dim, dim, dim>;
    // aka distances (directed)
    constexpr auto weighted_adjacency_matrix{Matrix{{
        {0, 6, inf, 3, inf, inf, inf},
        {inf, 0, inf, inf, 2, 10, inf},
        {7, inf, 0, inf, inf, inf, inf},
        {inf, inf, 5, 0, inf, 4, inf},
        {inf, inf, inf, inf, 0, inf, 3},
        {inf, inf, 6, inf, 7, 0, 8},
        {inf, 9, inf, inf, inf, inf, 0},
    }}};

    EXPECT_EQ(math::power_semigroup(weighted_adjacency_matrix, 1, MatMulGenTropical{}), weighted_adjacency_matrix);

    using math::operator<<;
    std::cout << math::power_semigroup(weighted_adjacency_matrix, 2, MatMulGenTropical{}) << "\n";

    std::cout << math::power_semigroup(weighted_adjacency_matrix, dim - 1, MatMulGenTropical{}) << "\n";

    // aka the shortest paths to everywhere
    constexpr auto transitive_closure{Matrix{{
        {0, 6, 8, 3, 8, 7, 11},
        {23, 0, 16, 26, 2, 10, 5},
        {7, 13, 0, 10, 15, 14, 18},
        {12, 18, 5, 0, 11, 4, 12},
        {35, 12, 28, 38, 0, 22, 3},
        {13, 17, 6, 16, 7, 0, 8},
        {32, 9, 25, 35, 11, 19, 0},
    }}};

    EXPECT_EQ(math::power_semigroup(weighted_adjacency_matrix, dim - 1, MatMulGenTropical{}), transitive_closure);
}

using MultiplicativeMonoidEx = unsigned int;
using MonoidEx = std::string;

TEST(power_monoid, tests) {
    EXPECT_EQ(math::power_monoid(MultiplicativeMonoidEx{1}, 3), MultiplicativeMonoidEx{1});
    EXPECT_EQ(math::power_monoid(MultiplicativeMonoidEx{2}, 3), MultiplicativeMonoidEx{8});
    EXPECT_EQ(math::power_monoid(MultiplicativeMonoidEx{3}, 1), MultiplicativeMonoidEx{3});
    EXPECT_EQ(math::power_monoid(MultiplicativeMonoidEx{3}, 2), MultiplicativeMonoidEx{9});

    EXPECT_EQ(math::power_monoid(MonoidEx{"a"}, 3, std::plus<MonoidEx>{}, MonoidEx{""}), MonoidEx{"aaa"});
    EXPECT_EQ(
        math::power_monoid(
            MonoidEx{"a"}, 3,
            [](const MonoidEx& a, const MonoidEx& b) {
                return a + b;
            },
            MonoidEx{""}),
        MonoidEx{"aaa"});
}

using CommutativeAdditiveGroupEx = int;

TEST(power_group, tests) {
    EXPECT_EQ(
        math::power_group(
            CommutativeAdditiveGroupEx{1}, 3, std::plus<CommutativeAdditiveGroupEx>{},
            std::negate<CommutativeAdditiveGroupEx>{}, CommutativeAdditiveGroupEx{}),
        CommutativeAdditiveGroupEx{3});
    EXPECT_EQ(
        math::power_group(
            CommutativeAdditiveGroupEx{2}, 3, std::plus<CommutativeAdditiveGroupEx>{},
            std::negate<CommutativeAdditiveGroupEx>{}, CommutativeAdditiveGroupEx{}),
        CommutativeAdditiveGroupEx{6});
    EXPECT_EQ(
        math::power_group(
            CommutativeAdditiveGroupEx{3}, 1, std::plus<CommutativeAdditiveGroupEx>{},
            std::negate<CommutativeAdditiveGroupEx>{}, CommutativeAdditiveGroupEx{}),
        CommutativeAdditiveGroupEx{3});
    EXPECT_EQ(
        math::power_group(
            CommutativeAdditiveGroupEx{3}, 2, std::plus<CommutativeAdditiveGroupEx>{},
            std::negate<CommutativeAdditiveGroupEx>{}, CommutativeAdditiveGroupEx{}),
        CommutativeAdditiveGroupEx{6});
}
