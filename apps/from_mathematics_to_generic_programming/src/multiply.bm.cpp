#include "multiply.h"
#include "benchmark/benchmark.h"

namespace {
constexpr auto lhs_factors{1'000};
constexpr auto rhs_factors{1'000};

void multiply0(benchmark::State& state) {
    for (auto _ : state) {
        for (int lhs{1}; lhs <= lhs_factors; ++lhs)
            for (int rhs{1}; rhs <= rhs_factors; ++rhs)
                math::multiply0(lhs, lhs + rhs);
    }
}

void multiply1(benchmark::State& state) {
    for (auto _ : state) {
        for (int lhs{1}; lhs <= lhs_factors; ++lhs)
            for (int rhs{1}; rhs <= rhs_factors; ++rhs)
                math::multiply1(lhs, lhs + rhs);
    }
}

void multiply2(benchmark::State& state) {
    for (auto _ : state) {
        for (int lhs{1}; lhs <= lhs_factors; ++lhs)
            for (int rhs{1}; rhs <= rhs_factors; ++rhs)
                math::multiply2(lhs, lhs + rhs);
    }
}

void multiply3(benchmark::State& state) {
    for (auto _ : state) {
        for (int lhs{1}; lhs <= lhs_factors; ++lhs)
            for (int rhs{1}; rhs <= rhs_factors; ++rhs)
                math::multiply3(lhs, lhs + rhs);
    }
}

void multiply4(benchmark::State& state) {
    for (auto _ : state) {
        for (int lhs{1}; lhs <= lhs_factors; ++lhs)
            for (int rhs{1}; rhs <= rhs_factors; ++rhs)
                math::multiply4(lhs, lhs + rhs);
    }
}

void multiply5(benchmark::State& state) {
    for (auto _ : state) {
        for (int lhs{1}; lhs <= lhs_factors; ++lhs)
            for (int rhs{1}; rhs <= rhs_factors; ++rhs)
                math::multiply5(lhs, lhs + rhs);
    }
}

void multiply5_by_15(benchmark::State& state) {
    for (auto _ : state) {
        for (int rhs{1}; rhs <= rhs_factors; ++rhs)
            math::multiply5(15, 15 + rhs);
    }
}

void multiply6_by_15(benchmark::State& state) {
    for (auto _ : state) {
        for (int rhs{1}; rhs <= rhs_factors; ++rhs)
            math::multiply6_by_15(15 + rhs);
    }
}

BENCHMARK(multiply0);
BENCHMARK(multiply1);
BENCHMARK(multiply2);
BENCHMARK(multiply3);
BENCHMARK(multiply4);
BENCHMARK(multiply5);
BENCHMARK(multiply5_by_15);
BENCHMARK(multiply6_by_15);
} // namespace
