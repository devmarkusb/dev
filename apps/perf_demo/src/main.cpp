#include "util/allthethings.h"

namespace {
double crunsh_n(int n) {
    ul::PerformanceProfiler perfscope0("gen", 2);
    double res{1.0};
    ++n;
    double sec{};
    auto sloop = ul::profiler_now();
    for (int i = n; --i;) {
        auto s = ul::profiler_now();
        ul::PerformanceProfiler perfscope1("single_gen", 3);
        auto r = ul::math::random_frac();
        res += r;
        sec += std::chrono::duration<double>(ul::profiler_diff(s, ul::profiler_now())).count();
    }
    std::cout << std::chrono::duration<double>(ul::profiler_diff(sloop, ul::profiler_now())).count() << "\n";
    std::cout << sec << "\n";
    return res;
}

void demo_tooperf_measurement() {
    {
        ul::PerformanceProfiler perfscope0("all", 0);
        ul::math::random_frac();
        {
            ul::PerformanceProfiler perfscope1("crunsh_n", 1);
            const auto res = crunsh_n(100'000);
            perfscope1.start_new_item("output");
            std::cout << "calc result: " << res << "\n";
        }
    }

    std::cout << ul::PerformanceProfiler::dump_all_items();
}
} // namespace

int main() {
    demo_tooperf_measurement();

    return ul::prog_exit_success;
}
