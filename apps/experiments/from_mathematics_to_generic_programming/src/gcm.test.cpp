#include "gcm.h"

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
constexpr auto arbitraryEven{42};
constexpr auto arbitraryOdd{43};
constexpr auto randRangeMin{1};
constexpr auto randRangeMax{1'000'000};
constexpr auto randReps{100};

struct Rand {
    static inline std::random_device dev_;
    static inline std::mt19937 gen_{dev_()};
    static inline std::uniform_int_distribution<> distrib_{randRangeMin, randRangeMax};
};

std::string printRandoms(int r1, int r2) {
    return "randoms: " + std::to_string(r1) + ", " + std::to_string(r2);
}

class GcmTest : public testing::TestWithParam<std::function<int(int, int)>> {};

INSTANTIATE_TEST_SUITE_P(
    GcmVariousImpl, GcmTest,
    testing::Values(math::gcm0, math::gcm1, math::gcm2, math::gcm3, math::gcm4, math::gcm5, math::gcm6));

// NOLINTBEGIN
TEST_P(GcmTest, one) {
    EXPECT_EQ(GetParam()(1, 1), 1);
    EXPECT_EQ(GetParam()(1, 2), 1);
    EXPECT_EQ(GetParam()(2, 1), 1);
    EXPECT_EQ(GetParam()(1, 3), 1);
    EXPECT_EQ(GetParam()(3, 1), 1);
    EXPECT_EQ(GetParam()(1, arbitraryEven), 1);
    EXPECT_EQ(GetParam()(arbitraryEven, 1), 1);
}

TEST_P(GcmTest, two) {
    EXPECT_EQ(GetParam()(2, 2), 2);
    EXPECT_EQ(GetParam()(2, 3), 1);
    EXPECT_EQ(GetParam()(3, 2), 1);
    EXPECT_EQ(GetParam()(2, 4), 2);
    EXPECT_EQ(GetParam()(4, 2), 2);
    EXPECT_EQ(GetParam()(2, arbitraryEven), 2);
    EXPECT_EQ(GetParam()(arbitraryEven, 2), 2);
    EXPECT_EQ(GetParam()(2, arbitraryOdd), 1);
    EXPECT_EQ(GetParam()(arbitraryOdd, 2), 1);
}

TEST_P(GcmTest, three) {
    EXPECT_EQ(GetParam()(3, 3), 3);
    EXPECT_EQ(GetParam()(3, 4), 1);
    EXPECT_EQ(GetParam()(4, 3), 1);
    EXPECT_EQ(GetParam()(3, 5), 1);
    EXPECT_EQ(GetParam()(5, 3), 1);
    EXPECT_EQ(GetParam()(3, 6), 3);
    EXPECT_EQ(GetParam()(6, 3), 3);
    EXPECT_EQ(GetParam()(3, arbitraryEven), arbitraryEven % 3 ? 1 : 3);
    EXPECT_EQ(GetParam()(arbitraryEven, 3), arbitraryEven % 3 ? 1 : 3);
    EXPECT_EQ(GetParam()(3, arbitraryOdd), arbitraryOdd % 3 ? 1 : 3);
    EXPECT_EQ(GetParam()(arbitraryOdd, 3), arbitraryOdd % 3 ? 1 : 3);
}

TEST_P(GcmTest, various) {
    EXPECT_EQ(GetParam()(arbitraryEven, arbitraryEven), arbitraryEven);
    EXPECT_EQ(GetParam()(arbitraryOdd, arbitraryOdd), arbitraryOdd);
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
    for (auto i{1}; i <= randReps; ++i) {
        const auto randnr{Rand::distrib_(Rand::gen_)};
        EXPECT_EQ(GetParam()(randnr, randnr), randnr);
    }
}

TEST_P(GcmTest, symmetric) {
    for (auto i{1}; i <= randReps; ++i) {
        const auto randnr1{Rand::distrib_(Rand::gen_)};
        const auto randnr2{Rand::distrib_(Rand::gen_)};
        EXPECT_EQ(GetParam()(randnr1, randnr2), GetParam()(randnr2, randnr1));
    }
}

TEST_P(GcmTest, sumprop) {
    for (auto i{1}; i <= randReps; ++i) {
        const auto randnr1{Rand::distrib_(Rand::gen_)};
        const auto randnr2{Rand::distrib_(Rand::gen_)};
        EXPECT_EQ(GetParam()(randnr1, randnr2), GetParam()(randnr1, randnr1 + randnr2));
    }
}

TEST_P(GcmTest, diffprop) {
    for (auto i{1}; i <= randReps; ++i) {
        const auto randnr1{Rand::distrib_(Rand::gen_)};
        const auto randnr2{Rand::distrib_(Rand::gen_)};
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
    EXPECT_EQ(GetParam()(0, arbitraryEven), 0);
    EXPECT_EQ(GetParam()(0, arbitraryOdd), 0);
}

TEST_P(RemainderTest, general) {
    for (auto i{1}; i <= randReps; ++i) {
        const auto randnr1{Rand::distrib_(Rand::gen_)};
        const auto randnr2{Rand::distrib_(Rand::gen_)};
        EXPECT_EQ(GetParam()(randnr1, randnr2), randnr1 % randnr2);
    }
}

class QuotientTest : public testing::TestWithParam<std::function<int(int, int)>> {};

INSTANTIATE_TEST_SUITE_P(QuotientVariousImpl, QuotientTest, testing::Values(math::quotient0));

TEST_P(QuotientTest, zero) {
    EXPECT_DEBUG_DEATH(GetParam()(1, 0), ".*");
    EXPECT_EQ(GetParam()(0, 1), 0);
    EXPECT_EQ(GetParam()(0, arbitraryEven), 0);
    EXPECT_EQ(GetParam()(0, arbitraryOdd), 0);
}

TEST_P(QuotientTest, general) {
    for (auto i{1}; i <= randReps; ++i) {
        const auto randnr1{Rand::distrib_(Rand::gen_)};
        const auto randnr2{Rand::distrib_(Rand::gen_)};
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
    EXPECT_EQ(GetParam()(0, arbitraryEven), std::make_pair(0, 0));
    EXPECT_EQ(GetParam()(0, arbitraryOdd), std::make_pair(0, 0));
}

TEST_P(QuotientRemainderTest, general) {
    for (auto i{1}; i <= randReps; ++i) {
        const auto randnr1{Rand::distrib_(Rand::gen_)};
        const auto randnr2{Rand::distrib_(Rand::gen_)};
        EXPECT_EQ(GetParam()(randnr1, randnr2), std::make_pair(randnr1 / randnr2, randnr1 % randnr2))
            << printRandoms(randnr1, randnr2);
    }
}
} // namespace
