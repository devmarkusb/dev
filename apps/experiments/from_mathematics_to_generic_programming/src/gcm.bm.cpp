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

constexpr auto randRangeMin{0};
// not exactly 2^16, but...
constexpr auto randRangeMax16{std::numeric_limits<uint16_t>::max()};
constexpr auto randRangeMax32{std::numeric_limits<uint32_t>::max()};
constexpr auto randRangeMax64{std::numeric_limits<uint64_t>::max()};
constexpr auto randReps{100};

struct Rand {
    static inline std::random_device dev_;
    static inline std::mt19937 gen_{dev_()};
    static inline std::uniform_int_distribution<uint16_t> distrib16_{randRangeMin, randRangeMax16};
    static inline std::uniform_int_distribution<uint32_t> distrib32_{randRangeMin, randRangeMax32};
    static inline std::uniform_int_distribution<uint64_t> distrib64_{randRangeMin, randRangeMax64};
};

template <class ...Args>
void gcd(benchmark::State& state, Args&&... args) {
    auto args_tuple = std::make_tuple(std::move(args)...);
    for (auto _ : state) {
        for (auto i{0}; i < randReps; ++i) {
            state.PauseTiming();
            const auto randnr1{std::get<1>(args_tuple)(Rand::gen_)};
            const auto randnr2{std::get<1>(args_tuple)(Rand::gen_)};
            state.ResumeTiming();
            auto r{std::get<0>(args_tuple)(randnr1, randnr2)};
            benchmark::DoNotOptimize(r);
        }
    }
}
BENCHMARK_CAPTURE(gcd, gcd16, math::gcd<uint16_t>, Rand::distrib16_);
BENCHMARK_CAPTURE(gcd, gcd_stein16, math::gcd_stein<uint16_t>, Rand::distrib16_);
BENCHMARK_CAPTURE(gcd, gcd32, math::gcd<uint32_t>, Rand::distrib32_);
BENCHMARK_CAPTURE(gcd, gcd_stein32, math::gcd_stein<uint32_t>, Rand::distrib32_);
BENCHMARK_CAPTURE(gcd, gcd64, math::gcd<uint64_t>, Rand::distrib64_);
BENCHMARK_CAPTURE(gcd, gcd_stein64, math::gcd_stein<uint64_t>, Rand::distrib64_);
} // namespace
