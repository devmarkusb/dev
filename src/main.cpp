#include <toolib/mem/alloc/default.h>
#include "tooperf_demo.h"
#include "source.h"
#include "util/random.h"
#include "toolib/finally.h"
#include "toolib/performance/performance.h"
#if TOO_ENABLE_PROFILING_GPERF
#include "gperftools/profiler.h"
#endif
#include "allthethings.h"

#include "toolib/mem/alloc/default.h"
#include "toolib/mem/alloc/linear.h"
#include "toolib/mem/allocator.h"


int main(int, char* [])
{
#if TOO_ENABLE_PROFILING_GPERF
    ProfilerStart("./app.prof");
    auto autoStopProfiling = too::finally([]() { ProfilerStop(); });
#endif

    //std::cout << "Default\n";
    //for (int k = 1; k <= 3; ++k)
    //{
    //    auto tstart = too::profiler_now();
    //    std::map<std::string, int> m;
    //    for (int i = 1; i <= 1'000'000; ++i)
    //    {
    //        m[std::to_string(pcs::gen_rand_nr())] = 42;
    //    }
    //    auto t = too::profiler_diff_s(tstart, too::profiler_now());
    //    std::cout << "t: " << t << "\n";
    //}
    //
    //std::cout << "Custom\n";
    //for (int k = 1; k <= 3; ++k)
    //{
    //    auto tstart = too::profiler_now();
    //
    //    using Arena = too::mem::alloc::Linear<>;
    //    using MapPair = std::pair<const std::string, int>;
    //    using Allocator = too::mem::Allocator<MapPair, Arena>;
    //    Arena a{too::mem::Bytes{50'000'000}, too::mem::Bytes{alignof(MapPair)}};
    //    Allocator al{a};
    //    std::map<std::string, int, std::less<>, Allocator> m{al};
    //    for (int i = 1; i <= 1'000'000; ++i)
    //    {
    //        m[std::to_string(pcs::gen_rand_nr())] = 42;
    //    }
    //    auto t = too::profiler_diff_s(tstart, too::profiler_now());
    //    std::cout << "t: " << t << "\n";
    //}

    std::cout << "Custom with stats\n";
    for (int k = 1; k <= 3; ++k)
    {
        auto tstart = too::profiler_now();

        using Arena = too::mem::alloc::Linear<too::mem::alloc::Statistics>;
        using MapPair = std::pair<const std::string, int>;
        using Allocator = too::mem::Allocator<MapPair, Arena>;
        Arena a{too::mem::Bytes{100'000'000}, too::mem::Bytes{alignof(MapPair)}};
        Allocator al{a};
        std::map<std::string, int, std::less<>, Allocator> m{al};
        for (int i = 1; i <= 1'000'000; ++i)
        {
            m[std::to_string(pcs::gen_rand_nr())] = 42;
        }
        auto t = too::profiler_diff_s(tstart, too::profiler_now());
        std::cout << "t: " << t << ", peak: " << *a.peak() << "\n";
    }

    std::cout << "Default with stats\n";
    for (int k = 1; k <= 3; ++k)
    {
        auto tstart = too::profiler_now();

        using Arena = too::mem::alloc::DefaultNewDelete<too::mem::alloc::Statistics>;
        using MapPair = std::pair<const std::string, int>;
        using Allocator = too::mem::Allocator<MapPair, Arena>;
        Arena a;
        Allocator al{a};
        std::map<std::string, int, std::less<>, Allocator> m{al};
        for (int i = 1; i <= 1'000'000; ++i)
        {
            m[std::to_string(pcs::gen_rand_nr())] = 42;
        }
        auto t = too::profiler_diff_s(tstart, too::profiler_now());
        std::cout << "t: " << t << ", peak: " << *a.peak() << "\n";
    }

    return 0;
}
