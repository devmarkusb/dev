#include "multiply.h"
#include "benchmark/benchmark.h"
#include <string>

namespace
{
constexpr auto lhsFactors{1'000};
constexpr auto rhsFactors{1'000};

void multiply0(benchmark::State& state)
{
    for (auto _ : state)
    {
        for (int lhs{1}; lhs < lhsFactors; ++lhs)
            for (int rhs{1}; rhs < rhsFactors; ++rhs)
                math::multiply0(lhs, lhs + rhs);
    }
}

void multiply1(benchmark::State& state)
{
    for (auto _ : state)
    {
        for (int lhs{1}; lhs < lhsFactors; ++lhs)
            for (int rhs{1}; rhs < rhsFactors; ++rhs)
                math::multiply1(lhs, lhs + rhs);
    }
}

void multiply2(benchmark::State& state)
{
    for (auto _ : state)
    {
        for (int lhs{1}; lhs < lhsFactors; ++lhs)
            for (int rhs{1}; rhs < rhsFactors; ++rhs)
                math::multiply2(lhs, lhs + rhs);
    }
}

void multiply3(benchmark::State& state)
{
    for (auto _ : state)
    {
        for (int lhs{1}; lhs < lhsFactors; ++lhs)
            for (int rhs{1}; rhs < rhsFactors; ++rhs)
                math::multiply3(lhs, lhs + rhs);
    }
}

void multiply4(benchmark::State& state)
{
    for (auto _ : state)
    {
        for (int lhs{1}; lhs < lhsFactors; ++lhs)
            for (int rhs{1}; rhs < rhsFactors; ++rhs)
                math::multiply4(lhs, lhs + rhs);
    }
}

void multiply5(benchmark::State& state)
{
    for (auto _ : state)
    {
        for (int lhs{1}; lhs < lhsFactors; ++lhs)
            for (int rhs{1}; rhs < rhsFactors; ++rhs)
                math::multiply5(lhs, lhs + rhs);
    }
}

BENCHMARK(multiply0);
BENCHMARK(multiply1);
BENCHMARK(multiply2);
BENCHMARK(multiply3);
BENCHMARK(multiply4);
BENCHMARK(multiply5);
} // namespace

BENCHMARK_MAIN();
