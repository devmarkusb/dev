#include "prime-sieve.h"
#include "benchmark/benchmark.h"
#include <string>

namespace
{
void sift2(benchmark::State& state)
{
    for (auto _ : state)
    {
    }
}

BENCHMARK(sift2);
} // namespace
