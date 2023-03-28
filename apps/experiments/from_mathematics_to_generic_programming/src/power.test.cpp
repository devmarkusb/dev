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
        math::power_semigroup(adjacencyMatrix, 1, math::mat_mul_gen_bool<Matrix>{}),
        adjacencyMatrix);

    using math::operator<<;
    std::cout << math::power_semigroup(adjacencyMatrix, 2, math::mat_mul_gen_bool<Matrix>{})
              << "\n";

    std::cout << math::power_semigroup(adjacencyMatrix, dim - 1, math::mat_mul_gen_bool<Matrix>{})
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
            math::mat_mul_gen_bool<Matrix>{}),
        transitiveClosure);
}

// aka shortest_length
TEST(power_semigroup, transitive_closure2)
{
    constexpr auto dim{7};
    using Matrix = math::Matrix<int, dim, dim>;
    using mat_mul_gen_tropical = math::mat_mul_gen_tropical<int, dim, dim, dim>;
    // aka unit of min part of semiring (min, +)
    constexpr auto inf{std::numeric_limits<int>::max()};
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
