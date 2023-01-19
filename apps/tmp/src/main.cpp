#include "tmp.h"
#if UL_ENABLE_PROFILING_GPERF
#include "gperftools/profiler.h"
#endif
#include "util/allthethings.h"

int main(int, char*[])
{
#if UL_ENABLE_PROFILING_GPERF
    ProfilerStart("./app.prof");
    auto autoStopProfiling = too::finally(
        []()
        {
            ProfilerStop();
        });
#endif


    return 0;
}
