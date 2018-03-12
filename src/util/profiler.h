//! Minimalist profiling functions which can also be used from C code.
#ifndef PROFILER_H_eouixn2t3478xgt381g
#define PROFILER_H_eouixn2t3478xgt381g

#include <stdint.h>


// mixed C/C++ code goes here
#ifdef __cplusplus
extern "C"
{
#endif

typedef int64_t ProfilerTimePoint;

ProfilerTimePoint pcs_profiler_now();
double pcs_profiler_diff_s(ProfilerTimePoint start, ProfilerTimePoint end);

#ifdef __cplusplus
}
#endif

#endif
