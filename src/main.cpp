#include "tooperf_demo.h"
#include "source.h"
#include "util/random.h"
#include "toolib/finally.h"
#include "toolib/performance/performance.h"
#if TOO_ENABLE_PROFILING_GPERF
#include "gperftools/profiler.h"
#endif
#include <omp.h>
#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cmath>
#include <iostream>
#include <functional>
#include <limits>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>


int main(int, char* [])
{
#if TOO_ENABLE_PROFILING_GPERF
    ProfilerStart("./app.prof");
    auto autoStopProfiling = too::finally([]() { ProfilerStop(); });
#endif

    return 0;
}
