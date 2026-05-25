#include "gcm.h"
#include "mb/ul/ul.hpp"

#include "benchmark/benchmark.h"

namespace {
void quotient_remainder0(benchmark::State& state) {
    for (auto _ : state) {
        auto [q, r]{math::quotient_remainder0(
            ul::narrow_cast<int>(state.range(0)), ul::narrow_cast<int>(state.range(1)))};
        benchmark::DoNotOptimize(q);
        benchmark::DoNotOptimize(r);
    }
}

void quotient_remainder1(benchmark::State& state) {
    for (auto _ : state) {
        auto [q, r]{math::quotient_remainder1(
            ul::narrow_cast<int>(state.range(0)), ul::narrow_cast<int>(state.range(1)))};
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

constexpr auto rand_range_min{0};
// not exactly 2^16, but...
constexpr auto rand_range_max16{std::numeric_limits<uint16_t>::max()};
constexpr auto rand_range_max32{std::numeric_limits<uint32_t>::max()};
constexpr auto rand_range_max64{std::numeric_limits<uint64_t>::max()};
constexpr auto rand_reps{100};

struct Rand {
    static inline std::random_device dev;
    static inline std::mt19937 gen{dev()};
    static inline std::uniform_int_distribution<uint16_t> distrib16{rand_range_min, rand_range_max16};
    static inline std::uniform_int_distribution<uint32_t> distrib32{rand_range_min, rand_range_max32};
    static inline std::uniform_int_distribution<uint64_t> distrib64{rand_range_min, rand_range_max64};
};

template <class... Args>
void gcd(benchmark::State& state, Args&&... args) {
    auto args_tuple = std::make_tuple(std::move(args)...);
    for (auto _ : state) {
        for (auto i{0}; i < rand_reps; ++i) {
            state.PauseTiming();
            const auto randnr1{std::get<1>(args_tuple)(Rand::gen)};
            const auto randnr2{std::get<1>(args_tuple)(Rand::gen)};
            state.ResumeTiming();
            auto r{std::get<0>(args_tuple)(randnr1, randnr2)};
            benchmark::DoNotOptimize(r);
        }
    }
}

BENCHMARK_CAPTURE(gcd, gcd16, math::gcd<uint16_t>, Rand::distrib16);
BENCHMARK_CAPTURE(gcd, gcd_stein16, math::gcd_stein<uint16_t>, Rand::distrib16);
BENCHMARK_CAPTURE(gcd, gcd32, math::gcd<uint32_t>, Rand::distrib32);
BENCHMARK_CAPTURE(gcd, gcd_stein32, math::gcd_stein<uint32_t>, Rand::distrib32);
BENCHMARK_CAPTURE(gcd, gcd64, math::gcd<uint64_t>, Rand::distrib64);
BENCHMARK_CAPTURE(gcd, gcd_stein64, math::gcd_stein<uint64_t>, Rand::distrib64);
} // namespace
