#include "source.h"
#include "toolib/finally.h"
#include "toolib/performance/performance.h"
#include "toolib/profiler.h"
#include "toolib/random.h"
#if TOO_ENABLE_PROFILING_GPERF
#include "gperftools/profiler.h"
#endif
#include "util/allthethings.h"


int main(int, char* [])
{
#if TOO_ENABLE_PROFILING_GPERF
    ProfilerStart("./app.prof");
    auto autoStopProfiling = too::finally([]() { ProfilerStop(); });
#endif


    return 0;
}
