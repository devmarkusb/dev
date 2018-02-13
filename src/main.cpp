#include "Toolib/performance/performance.h"
#include "Toolib/finally.h"
//#if !TOO_DEPLOYMENT_BUILD && !TOO_OS_WINDOWS
//#include "gperftools/profiler.h"
//#endif
#include <iostream>
#include <math.h>
#include <random>
#include <string>


namespace g_pcs_random
{
std::random_device dev;
std::mt19937 mt{dev()};
std::uniform_real_distribution<double> dist{0.0, 1.0};

double gen()
{
    return g_pcs_random::dist(g_pcs_random::mt);
}
}


double crunsh_n(int n)
{
    double res{1.0};
    ++n;
    for (int i = n; --i; )
    {
        too::CPerformanceProfiler perfscope1("single_gen");
        auto r = g_pcs_random::dist(g_pcs_random::mt);
        res+= r;
    }
    return res;
}

int main(int, char*[])
{
//#if !TOO_DEPLOYMENT_BUILD && !TOO_OS_WINDOWS
//    ProfilerStart("./app.prof");
//    auto autoStopProfiling = too::finally([](){ ProfilerStop(); });
//#endif
    {
        too::CPerformanceProfiler perfscope0("all");
        {
            too::CPerformanceProfiler perfscope1("crunsh_n");
            const auto res = crunsh_n(100000);
            perfscope1.StartNewItem("output");
            std::cout << res << "\n";
        }
    }

    std::cout << too::CPerformanceProfiler::DumpAllItems(false);

    return 0;
}
