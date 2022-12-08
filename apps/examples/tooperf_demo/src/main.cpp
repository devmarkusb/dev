#include "toolib/performance/performance.h"
#include "util/allthethings.h"

namespace too = mb::too;

namespace
{
double crunsh_n(int n)
{
    too::PerformanceProfiler perfscope0("gen", 2);
    double res{1.0};
    ++n;
    double sec{};
    auto sloop = ul::profiler_now();
    for (int i = n; --i;)
    {
        auto s = ul::profiler_now();
        too::PerformanceProfiler perfscope1("single_gen", 3);
        auto r = ul::math::random_frac();
        res += r;
        sec += ul::profiler_diff_s(s, ul::profiler_now());
    }
    std::cout << ul::profiler_diff_s(sloop, ul::profiler_now()) << "\n";
    std::cout << sec << "\n";
    return res;
}

void demo_tooperf_measurement()
{
    {
        too::PerformanceProfiler perfscope0("all", 0);
        ul::math::random_frac();
        {
            too::PerformanceProfiler perfscope1("crunsh_n", 1);
            const auto res = crunsh_n(100000);
            perfscope1.startNewItem("output");
            std::cout << "calc result: " << res << "\n";
        }
    }

    std::cout << too::PerformanceProfiler::dumpAllItems();
}
} // namespace

int main()
{
    demo_tooperf_measurement();

    return ul::prog_exit_success;
}
