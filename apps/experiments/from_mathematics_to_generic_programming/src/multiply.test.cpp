#include "multiply.h"
#include "gtest/gtest.h"

TEST(multiply_accumulate_semigroup, tests_with_int)
{
    EXPECT_EQ(math::multiply_accumulate_semigroup(0, 3, 4), 12);
    EXPECT_EQ(math::multiply_accumulate_semigroup(1, 3, 4), 13);
}

struct NoncommutativeAdditiveSemigroupEx
{
    explicit NoncommutativeAdditiveSemigroupEx(std::string nonEmptyStr)
        : nonEmptyStr_{std::move(nonEmptyStr)}
    {
        UL_EXPECT(!nonEmptyStr_.empty());
    }

    NoncommutativeAdditiveSemigroupEx operator+=(const NoncommutativeAdditiveSemigroupEx& other)
    {
        nonEmptyStr_ += other.nonEmptyStr_;
        return *this;
    }

    friend bool operator==(const NoncommutativeAdditiveSemigroupEx& lhs, const NoncommutativeAdditiveSemigroupEx& rhs);
    friend NoncommutativeAdditiveSemigroupEx operator+(const NoncommutativeAdditiveSemigroupEx& a, const NoncommutativeAdditiveSemigroupEx& b);

private:
    std::string nonEmptyStr_{"a"};
};

bool operator==(const NoncommutativeAdditiveSemigroupEx& lhs, const NoncommutativeAdditiveSemigroupEx& rhs)
{
    return lhs.nonEmptyStr_ == rhs.nonEmptyStr_;
}

NoncommutativeAdditiveSemigroupEx operator+(const NoncommutativeAdditiveSemigroupEx& a, const NoncommutativeAdditiveSemigroupEx& b)
{
    NoncommutativeAdditiveSemigroupEx res{a};
    res += b;
    return res;
}

TEST(multiply_accumulate_semigroup, tests_with_just_semigroup)
{
    NoncommutativeAdditiveSemigroupEx a{"a"};
    NoncommutativeAdditiveSemigroupEx aa{"aa"};
    EXPECT_EQ(math::multiply_accumulate_semigroup(a, 3, NoncommutativeAdditiveSemigroupEx{"b"}), NoncommutativeAdditiveSemigroupEx{"abbb"});
    EXPECT_EQ(math::multiply_accumulate_semigroup(aa, 3, NoncommutativeAdditiveSemigroupEx{"b"}), NoncommutativeAdditiveSemigroupEx{"aabbb"});

    EXPECT_EQ(math::multiply_semigroup(2, NoncommutativeAdditiveSemigroupEx{"b"}), NoncommutativeAdditiveSemigroupEx{"bb"});
    EXPECT_EQ(math::multiply_semigroup(1, NoncommutativeAdditiveSemigroupEx{"b"}), NoncommutativeAdditiveSemigroupEx{"b"});
    EXPECT_DEBUG_DEATH(math::multiply_semigroup(0, NoncommutativeAdditiveSemigroupEx{"b"}), ".*");
}

using NoncommutativeAdditiveMonoidEx = std::string;

TEST(multiply_monoid, tests_with_just_monoid)
{
    // Unfortunately this might work, although we don't have a monoid because of no identity element. Example of
    // concepts not being able to enforce full semantics.
    // In this case it doesn't compile because of the absence of a default constructor (but there could be one, just
    // not necessarily yielding the identity element).
    //EXPECT_EQ(math::multiply_monoid(3, NoncommutativeAdditiveSemigroupEx{"b"}), NoncommutativeAdditiveSemigroupEx{"bbb"});

    EXPECT_EQ(math::multiply_monoid(3, NoncommutativeAdditiveMonoidEx{"b"}), NoncommutativeAdditiveMonoidEx{"bbb"});
    EXPECT_EQ(math::multiply_monoid(1, NoncommutativeAdditiveMonoidEx{"b"}), NoncommutativeAdditiveMonoidEx{"b"});
    EXPECT_EQ(math::multiply_monoid(0, NoncommutativeAdditiveMonoidEx{"b"}), NoncommutativeAdditiveMonoidEx{});
}

using NoncommutativeAdditiveGroupEx = int;

TEST(multiply_group, tests_with_just_group)
{
    // Correctly, not compiling, no inverse.
    //EXPECT_EQ(math::multiply_group(3, NoncommutativeAdditiveMonoidEx{"b"}), NoncommutativeAdditiveMonoidEx{"bbb"});

    EXPECT_EQ(math::multiply_group(3, NoncommutativeAdditiveGroupEx{2}), NoncommutativeAdditiveGroupEx{6});
    EXPECT_EQ(math::multiply_group(1, NoncommutativeAdditiveGroupEx{2}), NoncommutativeAdditiveGroupEx{2});
    EXPECT_EQ(math::multiply_group(0, NoncommutativeAdditiveGroupEx{2}), NoncommutativeAdditiveGroupEx{});
    EXPECT_EQ(math::multiply_group(-1, NoncommutativeAdditiveGroupEx{2}), NoncommutativeAdditiveGroupEx{-2});
}
