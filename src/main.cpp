#include "Toolib/performance/performance.h"
#include <conio.h>
#include <iostream>
#include <math.h>
#include <random>
#include <string>


namespace g_pcs_random
{
std::random_device dev;
std::mt19937 mt;
std::uniform_real_distribution<double> dist(0.0, 1.0);

double gen()
{
    return g_pcs_random::dist(g_pcs_random::dev);
}
}


double crunsh_n(int n)
{
    double res{1.0};
    ++n;
    for (int i = n; --i; )
    {
        too::CPerformanceProfiler perfscope1("single_gen");
        auto r = g_pcs_random::dist(g_pcs_random::dev);
        if (r < 0.00001)
            r*= 10000;
        else if (r < 0.0001)
            r*= 1000;
        else if (r < 0.001)
            r*= 100;
        else if (r < 0.01)
            r*= 10;
        else if (r >= 0.01)
            r*= 2;
        res*= r;
    }
    return res;
}

int main(int, char*[])
{
    std::getchar();
    {
        too::CPerformanceProfiler perfscope0("all");
        {
            too::CPerformanceProfiler perfscope1("crunsh_n");
            const auto res = crunsh_n(1000);
            perfscope1.StartNewItem("output");
            std::cout << res << "\n";
        }
    }

    std::cout << too::CPerformanceProfiler::DumpAllItems(false);

    std::getchar();
    return 0;
}
