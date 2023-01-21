#include "util/allthethings.h"

namespace
{
double crunsh_n(int n)
{
    ul::PerformanceProfiler perfscope0("gen", 2);
    double res{1.0};
    ++n;
    double sec{};
    auto sloop = ul::profiler_now();
    for (int i = n; --i;)
    {
        auto s = ul::profiler_now();
        ul::PerformanceProfiler perfscope1("single_gen", 3);
        auto r = ul::math::randomFrac();
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
        ul::PerformanceProfiler perfscope0("all", 0);
        ul::math::randomFrac();
        {
            ul::PerformanceProfiler perfscope1("crunsh_n", 1);
            const auto res = crunsh_n(100000);
            perfscope1.startNewItem("output");
            std::cout << "calc result: " << res << "\n";
        }
    }

    std::cout << ul::PerformanceProfiler::dumpAllItems();
}
} // namespace

int main()
{
    demo_tooperf_measurement();

    return ul::prog_exit_success;
}
