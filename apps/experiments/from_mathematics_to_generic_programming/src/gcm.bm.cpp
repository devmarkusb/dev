#include "gcm.h"
#include "ul/ul.h"

#include "benchmark/benchmark.h"

namespace {
void quotient_remainder0(benchmark::State& state) {
    for (auto _ : state) {
        auto [q, r]{
            math::quotient_remainder0(ul::narrow_cast<int>(state.range(0)), ul::narrow_cast<int>(state.range(1)))};
        benchmark::DoNotOptimize(q);
        benchmark::DoNotOptimize(r);
    }
}

void quotient_remainder1(benchmark::State& state) {
    for (auto _ : state) {
        auto [q, r]{
            math::quotient_remainder1(ul::narrow_cast<int>(state.range(0)), ul::narrow_cast<int>(state.range(1)))};
        benchmark::DoNotOptimize(q);
        benchmark::DoNotOptimize(r);
    }
}

BENCHMARK(quotient_remainder0)
    ->Args({45, 6})
    ->Args({45, 44})
    ->Args({45, 1})
    ->Args({1'000'000, 1})
    ->Args({1'000'000, 2})
    ->Args({1'000'000, 5})
    ->Args({1'000'000, 11})
    ->Args({1'000'000, 999'999})
    ->Args({1'000'000, 1'000'000})
    ->Args({1'000'003, 2});
BENCHMARK(quotient_remainder1)
    ->Args({45, 6})
    ->Args({45, 44})
    ->Args({45, 1})
    ->Args({1'000'000, 1})
    ->Args({1'000'000, 2})
    ->Args({1'000'000, 5})
    ->Args({1'000'000, 11})
    ->Args({1'000'000, 999'999})
    ->Args({1'000'000, 1'000'000})
    ->Args({1'000'003, 2});
} // namespace
