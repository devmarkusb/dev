#include "tmp.h"
#if MB_UL_ENABLE_PROFILING_GPERF
#include "gperftools/profiler.h"
#endif
#include "util/allthethings.h"

int main(int, char*[]) {
#if MB_UL_ENABLE_PROFILING_GPERF
    ProfilerStart("./app.prof");
    auto autoStopProfiling = ul::finally([]() {
        ProfilerStop();
    });
#endif


    return 0;
}
