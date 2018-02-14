#include "tooperf_demo.h"
#include "util/random.h"
#include "Toolib/performance/performance.h"
#include <iostream>


namespace
{
double crunsh_n(int n)
{
    double res{1.0};
    ++n;
    for (int i = n; --i;)
    {
        too::CPerformanceProfiler perfscope1("single_gen");
        auto r = pcs::gen_rand_nr();
        res += r;
    }
    return res;
}
} // namespace

void demo_tooperf_measurement()
{
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
}
