#include "ch13-crypt.h"
#include "gtest/gtest.h"

namespace {
// source: Wolfram
const std::array carmichael{561, 1105, 1729, 2465, 2821, 6601, 8911, 10585, 15841, 29341};

TEST(is_carmichael, up_to_some) {
    const auto max_test_number{carmichael.back()};
    auto current_carmichael_idx{0U};
    for (auto n{2}; n <= max_test_number; ++n) {
        if (math::is_prime(n)) {
            continue;
        }
        if (n == carmichael.at(current_carmichael_idx)) {
            ++current_carmichael_idx;
            EXPECT_TRUE(math::is_carmichael(n)) << n;
        } else {
            EXPECT_FALSE(math::is_carmichael(n)) << n;
        }
    }
}

TEST(is_carmichael, gen_first) {
    const auto number{7};
    auto gen_c{math::gen_first_carmichaels<number, int>()};
    size_t idx{};
    for (auto c : carmichael) {
        EXPECT_EQ(c, gen_c.at(idx));
        ++idx;
        if (idx == gen_c.size()) {
            return;
        }
    }
}
} // namespace
