#include "power.h"
#include "gtest/gtest.h"
#include <functional>
#include <limits>

TEST(power_accumulate_semigroup, tests)
{
    EXPECT_EQ(math::power_accumulate_semigroup(1, 2, 3), 8);
    EXPECT_EQ(math::power_accumulate_semigroup(2, 2, 3), 16);
}

TEST(power_semigroup, tests)
{
    // abuse as multiply
    EXPECT_EQ(math::power_semigroup(2, 4, std::plus{}), 8);
    EXPECT_EQ(math::power_semigroup(2, 4, std::multiplies{}), 16);
}

// aka social_net_paths
TEST(power_semigroup, transitive_closure)
{
    constexpr auto dim{7};
    using Matrix = math::Matrix<int, dim, dim>;
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

    EXPECT_EQ(
        math::power_semigroup(adjacencyMatrix, 1, math::MatMulGenBool<Matrix>{}),
        adjacencyMatrix);

    using math::operator<<;
    std::cout << math::power_semigroup(adjacencyMatrix, 2, math::MatMulGenBool<Matrix>{})
              << "\n";

    std::cout << math::power_semigroup(adjacencyMatrix, dim - 1, math::MatMulGenBool<Matrix>{})
              << "\n";

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

    EXPECT_EQ(
        math::power_semigroup(
            adjacencyMatrix, dim - 1,
            math::MatMulGenBool<Matrix>{}),
        transitiveClosure);
}

// aka shortest_length
TEST(power_semigroup, transitive_closure2)
{
    constexpr auto dim{7};
    constexpr auto inf{math::Tropical::inf};
    using Matrix = math::Matrix<math::Tropical, dim, dim>;
    using mat_mul_gen_tropical = math::MatMulGenTropical<math::Tropical, dim, dim, dim>;
    // aka unit of min part of semiring (min, +)
    // aka distances
    constexpr auto weightedAdjacencyMatrix{Matrix{{
        {0, 6, inf, 3, inf, inf, inf},
        {inf, 0, inf, inf, 2, 10, inf},
        {7, inf, 0, inf, inf, inf, inf},
        {inf, inf, 5, 0, inf, 4, inf},
        {inf, inf, inf, inf, 0, inf, 3},
        {inf, inf, 6, inf, 7, 0, 8},
        {inf, 9, inf, inf, inf, inf, 0},
    }}};

    EXPECT_EQ(
        math::power_semigroup(
            weightedAdjacencyMatrix, 1,
            mat_mul_gen_tropical{}),
        weightedAdjacencyMatrix);

    using math::operator<<;
    std::cout << math::power_semigroup(
        weightedAdjacencyMatrix, 2,
        mat_mul_gen_tropical{}) << "\n";

    std::cout << math::power_semigroup(
        weightedAdjacencyMatrix, dim - 1,
        mat_mul_gen_tropical{}) << "\n";

    // aka shortest paths to everywhere
    constexpr auto transitiveClosure{Matrix{{
        {0, 6, 8, 3, 8, 7, 11},
        {23, 0, 16, 26, 2, 10, 5},
        {7, 13, 0, 10, 15, 14, 18},
        {12, 18, 5, 0, 11, 4, 12},
        {35, 12, 28, 38, 0, 22, 3},
        {13, 17, 6, 16, 7, 0, 8},
        {32, 9, 25, 35, 11, 19, 0},
    }}};

    EXPECT_EQ(
        math::power_semigroup(
            weightedAdjacencyMatrix, dim - 1,
            mat_mul_gen_tropical{}),
        transitiveClosure);
}

TEST(power_monoid, tests)
{
}

TEST(power_group, tests)
{
}
