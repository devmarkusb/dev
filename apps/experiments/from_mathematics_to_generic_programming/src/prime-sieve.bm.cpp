#include "prime-sieve.h"
#include "benchmark/benchmark.h"
#include <vector>

namespace
{
constexpr auto m{10'000};
constexpr auto mi{(m - 3) / 2};

void sift2_vecbool(benchmark::State& state)
{
    std::vector<bool> primes;
    primes.resize(mi);
    for (auto _ : state)
    {
        math::sift2(std::begin(primes), mi);
    }
}

void sift2_vecu8(benchmark::State& state)
{
    std::vector<uint8_t> primes;
    primes.resize(mi);
    for (auto _ : state)
    {
        math::sift2(std::begin(primes), mi);
    }
}

void sift2_vecu16(benchmark::State& state)
{
    std::vector<uint16_t> primes;
    primes.resize(mi);
    for (auto _ : state)
    {
        math::sift2(std::begin(primes), mi);
    }
}

void sift2_vecu32(benchmark::State& state)
{
    std::vector<uint32_t> primes;
    primes.resize(mi);
    for (auto _ : state)
    {
        math::sift2(std::begin(primes), mi);
    }
}

void sift2_vecu64(benchmark::State& state)
{
    std::vector<uint64_t> primes;
    primes.resize(mi);
    for (auto _ : state)
    {
        math::sift2(std::begin(primes), mi);
    }
}

BENCHMARK(sift2_vecbool);
BENCHMARK(sift2_vecu8);
BENCHMARK(sift2_vecu16);
BENCHMARK(sift2_vecu32);
BENCHMARK(sift2_vecu64);
} // namespace
