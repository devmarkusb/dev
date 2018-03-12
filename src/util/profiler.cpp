#include "profiler.h"
#include <chrono>


ProfilerTimePoint pcs_profiler_now()
{
    const auto now = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now());
    return now.time_since_epoch().count();
}

double pcs_profiler_diff_s(ProfilerTimePoint start, ProfilerTimePoint end)
{
    return (end - start) / 1e9;
}
