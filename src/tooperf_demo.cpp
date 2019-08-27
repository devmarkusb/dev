#include "tooperf_demo.h"
#include "toolib/performance/performance.h"
#include "toolib/profiler.h"
#include "toolib/random.h"
#include <iostream>


namespace
{
double crunsh_n(int n)
{
    too::PerformanceProfiler perfscope0("gen", 2);
    double res{1.0};
    ++n;
    double sec{};
    auto sloop = too::profiler_now();
    for (int i = n; --i;)
    {
        auto s = too::profiler_now();
        too::PerformanceProfiler perfscope1("single_gen", 3);
        auto r = too::math::random_frac();
        res += r;
        sec += too::profiler_diff_s(s, too::profiler_now());
    }
    std::cout << too::profiler_diff_s(sloop, too::profiler_now()) << "\n";
    std::cout << sec << "\n";
    return res;
}
} // namespace

void demo_tooperf_measurement()
{
    {
        too::PerformanceProfiler perfscope0("all", 0);
        too::math::random_frac();
        {
            too::PerformanceProfiler perfscope1("crunsh_n", 1);
            const auto res = crunsh_n(100000);
            perfscope1.startNewItem("output");
            std::cout << "calc result: " << res << "\n";
        }
    }

    std::cout << too::PerformanceProfiler::dumpAllItems();
}
