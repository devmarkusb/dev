#include "gcm.h"

#include "ul/ul.h"
#include "gtest/gtest.h"
#include <random>

namespace std {
static ostream& operator<<(ostream& os, const function<int(int, int)>&) {
    os << "std::function<std::pair<int, int>(int, int)>";
    return os;
}

static ostream& operator<<(ostream& os, const function<std::pair<int, int>(int, int)>&) {
    os << "std::function<std::pair<int, int>(int, int)>";
    return os;
}
} // namespace std

namespace {
constexpr auto arbitrary_even{42};
constexpr auto arbitrary_odd{43};
constexpr auto rand_range_min{1};
constexpr auto rand_range_max{10'000};
constexpr auto rand_reps{1000};

struct Rand {
    static inline std::random_device dev;
    static inline std::mt19937 gen{dev()};
    static inline std::uniform_int_distribution<> distrib{rand_range_min, rand_range_max};
};

std::string print_randoms(int r1, int r2) {
    return "randoms: " + std::to_string(r1) + ", " + std::to_string(r2);
}

class GcmTest : public testing::TestWithParam<std::function<int(int, int)>> {};

INSTANTIATE_TEST_SUITE_P(
    GcmVariousImpl, GcmTest,
    testing::Values(
        math::gcm0, math::gcm1, math::gcm2, math::gcm3, math::gcm4, math::gcm5, math::gcm6,
        math::gcd<math::LineSegment>, math::gcd_stein<math::LineSegment>));

// NOLINTBEGIN
TEST_P(GcmTest, one) {
    EXPECT_EQ(GetParam()(1, 1), 1);
    EXPECT_EQ(GetParam()(1, 2), 1);
    EXPECT_EQ(GetParam()(2, 1), 1);
    EXPECT_EQ(GetParam()(1, 3), 1);
    EXPECT_EQ(GetParam()(3, 1), 1);
    EXPECT_EQ(GetParam()(1, arbitrary_even), 1);
    EXPECT_EQ(GetParam()(arbitrary_even, 1), 1);
}

TEST_P(GcmTest, two) {
    EXPECT_EQ(GetParam()(2, 2), 2);
    EXPECT_EQ(GetParam()(2, 3), 1);
    EXPECT_EQ(GetParam()(3, 2), 1);
    EXPECT_EQ(GetParam()(2, 4), 2);
    EXPECT_EQ(GetParam()(4, 2), 2);
    EXPECT_EQ(GetParam()(2, arbitrary_even), 2);
    EXPECT_EQ(GetParam()(arbitrary_even, 2), 2);
    EXPECT_EQ(GetParam()(2, arbitrary_odd), 1);
    EXPECT_EQ(GetParam()(arbitrary_odd, 2), 1);
}

TEST_P(GcmTest, three) {
    EXPECT_EQ(GetParam()(3, 3), 3);
    EXPECT_EQ(GetParam()(3, 4), 1);
    EXPECT_EQ(GetParam()(4, 3), 1);
    EXPECT_EQ(GetParam()(3, 5), 1);
    EXPECT_EQ(GetParam()(5, 3), 1);
    EXPECT_EQ(GetParam()(3, 6), 3);
    EXPECT_EQ(GetParam()(6, 3), 3);
    EXPECT_EQ(GetParam()(3, arbitrary_even), arbitrary_even % 3 ? 1 : 3);
    EXPECT_EQ(GetParam()(arbitrary_even, 3), arbitrary_even % 3 ? 1 : 3);
    EXPECT_EQ(GetParam()(3, arbitrary_odd), arbitrary_odd % 3 ? 1 : 3);
    EXPECT_EQ(GetParam()(arbitrary_odd, 3), arbitrary_odd % 3 ? 1 : 3);
}

TEST_P(GcmTest, various) {
    EXPECT_EQ(GetParam()(arbitrary_even, arbitrary_even), arbitrary_even);
    EXPECT_EQ(GetParam()(arbitrary_odd, arbitrary_odd), arbitrary_odd);
    EXPECT_EQ(GetParam()(12, 6), 6);
    EXPECT_EQ(GetParam()(6, 12), 6);
    EXPECT_EQ(GetParam()(12, 9), 3);
    EXPECT_EQ(GetParam()(9, 12), 3);
    EXPECT_EQ(GetParam()(12, 2), 2);
    EXPECT_EQ(GetParam()(2, 12), 2);
    EXPECT_EQ(GetParam()(12, 10), 2);
    EXPECT_EQ(GetParam()(10, 12), 2);
    EXPECT_EQ(GetParam()(12, 11), 1);
    EXPECT_EQ(GetParam()(11, 12), 1);
    EXPECT_EQ(GetParam()(12, 8), 4);
    EXPECT_EQ(GetParam()(8, 12), 4);
    EXPECT_EQ(GetParam()(12, 7), 1);
    EXPECT_EQ(GetParam()(7, 12), 1);
    EXPECT_EQ(GetParam()(12, 3), 3);
    EXPECT_EQ(GetParam()(3, 12), 3);
}

// NOLINTEND

TEST_P(GcmTest, equal) {
    for (auto i{1}; i <= rand_reps; ++i) {
        const auto randnr{Rand::distrib(Rand::gen)};
        EXPECT_EQ(GetParam()(randnr, randnr), randnr);
    }
}

TEST_P(GcmTest, symmetric) {
    for (auto i{1}; i <= rand_reps; ++i) {
        const auto randnr1{Rand::distrib(Rand::gen)};
        const auto randnr2{Rand::distrib(Rand::gen)};
        EXPECT_EQ(GetParam()(randnr1, randnr2), GetParam()(randnr2, randnr1));
    }
}

TEST_P(GcmTest, sumprop) {
    for (auto i{1}; i <= rand_reps; ++i) {
        const auto randnr1{Rand::distrib(Rand::gen)};
        const auto randnr2{Rand::distrib(Rand::gen)};
        EXPECT_EQ(GetParam()(randnr1, randnr2), GetParam()(randnr1, randnr1 + randnr2));
    }
}

TEST_P(GcmTest, diffprop) {
    for (auto i{1}; i <= rand_reps; ++i) {
        const auto randnr1{Rand::distrib(Rand::gen)};
        const auto randnr2{Rand::distrib(Rand::gen)};
        if (randnr1 < randnr2)
            EXPECT_EQ(GetParam()(randnr1, randnr2), GetParam()(randnr1, randnr2 - randnr1));
        else if (randnr1 > randnr2)
            EXPECT_EQ(GetParam()(randnr1, randnr2), GetParam()(randnr1 - randnr2, randnr2));
        else
            EXPECT_EQ(GetParam()(randnr1, randnr2), randnr1);
    }
}

class RemainderTest : public testing::TestWithParam<std::function<int(int, int)>> {};

INSTANTIATE_TEST_SUITE_P(
    RemainderVariousImpl, RemainderTest, testing::Values(math::remainder0, math::remainder1, math::remainder2));

TEST_P(RemainderTest, zero) {
    EXPECT_DEBUG_DEATH(GetParam()(1, 0), ".*");
    EXPECT_EQ(GetParam()(0, 1), 0);
    EXPECT_EQ(GetParam()(0, arbitrary_even), 0);
    EXPECT_EQ(GetParam()(0, arbitrary_odd), 0);
}

TEST_P(RemainderTest, general) {
    for (auto i{1}; i <= rand_reps; ++i) {
        const auto randnr1{Rand::distrib(Rand::gen)};
        const auto randnr2{Rand::distrib(Rand::gen)};
        EXPECT_EQ(GetParam()(randnr1, randnr2), randnr1 % randnr2);
    }
}

class QuotientTest : public testing::TestWithParam<std::function<int(int, int)>> {};

INSTANTIATE_TEST_SUITE_P(QuotientVariousImpl, QuotientTest, testing::Values(math::quotient0));

TEST_P(QuotientTest, zero) {
    EXPECT_DEBUG_DEATH(GetParam()(1, 0), ".*");
    EXPECT_EQ(GetParam()(0, 1), 0);
    EXPECT_EQ(GetParam()(0, arbitrary_even), 0);
    EXPECT_EQ(GetParam()(0, arbitrary_odd), 0);
}

TEST_P(QuotientTest, general) {
    for (auto i{1}; i <= rand_reps; ++i) {
        const auto randnr1{Rand::distrib(Rand::gen)};
        const auto randnr2{Rand::distrib(Rand::gen)};
        EXPECT_EQ(GetParam()(randnr1, randnr2), randnr1 / randnr2);
    }
}

class QuotientRemainderTest : public testing::TestWithParam<std::function<std::pair<int, int>(int, int)>> {};

INSTANTIATE_TEST_SUITE_P(
    QuotientRemainderVariousImpl, QuotientRemainderTest,
    testing::Values(math::quotient_remainder0, math::quotient_remainder1 /*, math::quotient_remainder2*/));

TEST_P(QuotientRemainderTest, zero) {
    EXPECT_DEBUG_DEATH(GetParam()(1, 0), ".*");
    EXPECT_EQ(GetParam()(0, 1), std::make_pair(0, 0));
    EXPECT_EQ(GetParam()(0, arbitrary_even), std::make_pair(0, 0));
    EXPECT_EQ(GetParam()(0, arbitrary_odd), std::make_pair(0, 0));
}

TEST_P(QuotientRemainderTest, general) {
    for (auto i{1}; i <= rand_reps; ++i) {
        const auto randnr1{Rand::distrib(Rand::gen)};
        const auto randnr2{Rand::distrib(Rand::gen)};
        EXPECT_EQ(GetParam()(randnr1, randnr2), std::make_pair(randnr1 / randnr2, randnr1 % randnr2))
            << print_randoms(randnr1, randnr2);
    }
}

// NOLINTBEGIN
TEST(extended_gcd_test, misc)
{
    auto a{12};
    auto b{6};
    auto [x, g]{math::extended_gcd(a, b)};
    EXPECT_EQ(g, 6);
    EXPECT_EQ(x, 0);

    a = 12;
    b = 7;
    std::tie(x, g) = math::extended_gcd(a, b);
    EXPECT_EQ(g, 1);
    EXPECT_EQ(x, 3);
    EXPECT_EQ(math::bezout_y(x, a, b), -5);

    a = 12;
    b = 9;
    std::tie(x, g) = math::extended_gcd(a, b);
    EXPECT_EQ(g, 3);
    EXPECT_EQ(x, 1);
    EXPECT_EQ(math::bezout_y(x, a, b), -1);
}
// NOLINTEND

TEST(extended_gcd_test, bezout_identity_random)
{
    for (auto i{1}; i <= rand_reps; ++i) {
        const auto a{Rand::distrib(Rand::gen)};
        const auto b{Rand::distrib(Rand::gen)};
        auto [x, g]{math::extended_gcd(a, b)};
        ASSERT_FALSE(ul::math::mul_overflow(x, a)); // choose smaller rand_range_max
        EXPECT_EQ(x * a + math::bezout_y(x, a, b) * b, g) << "a: " << a << " b: " << b;
    }
}
} // namespace
