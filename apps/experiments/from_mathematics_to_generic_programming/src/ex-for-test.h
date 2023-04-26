#include "ul/ul.h"
#include <functional>
#include <string>

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

inline bool operator==(const NoncommutativeAdditiveSemigroupEx& lhs, const NoncommutativeAdditiveSemigroupEx& rhs)
{
    return lhs.nonEmptyStr_ == rhs.nonEmptyStr_;
}

inline NoncommutativeAdditiveSemigroupEx operator+(const NoncommutativeAdditiveSemigroupEx& a, const NoncommutativeAdditiveSemigroupEx& b)
{
    NoncommutativeAdditiveSemigroupEx res{a};
    res += b;
    return res;
}

using NoncommutativeAdditiveMonoidEx = std::string;

using NoncommutativeAdditiveGroupEx = int;

using SemiRingEx = unsigned int;
using SemiRingOpCommMonoidEx = std::plus<SemiRingEx>;
using SemiRingOpMonoidEx = std::multiplies<SemiRingEx>;

using RingEx = int;
