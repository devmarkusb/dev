#include "util/allthethings.h"
#include <cassert>

UL_PRAGMA_WARNINGS_PUSH
// clang-format off
UL_WARNING_DISABLE_CLANG_ALL
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-function"

// clang-format on
namespace {
inline namespace mb {
void recurse_children(
    int& num_hierarchies, std::set<int>& visited, int n, const std::vector<std::vector<int>>& children, int parent) {
    auto& v{visited};
    auto& nh{num_hierarchies};
    for (int c /* child */ : children[static_cast<size_t>(parent)]) {
        auto [_, inserted]{v.insert(c)};
        if (!inserted)
            continue;
        std::cout << "->" << c;
        if (static_cast<int>(v.size()) == n) {
            std::cout << "; ";
            ++nh;
        } else
            recurse_children(nh, v, n, children, c);
        v.erase(c);
    }
}

[[maybe_unused]] int solution(int n, const std::vector<std::vector<int>>& respect_list) {
    assert(1 <= n && n <= 100);
    assert(n - 1 <= static_cast<int>(respect_list.size()) && static_cast<int>(respect_list.size()) <= n * (n - 1) / 2);
#ifndef NDEBUG
    for (const auto& resp_pair : respect_list) {
        assert(resp_pair.size() == 2);
        assert(0 <= resp_pair[0] && resp_pair[0] < n);
        assert(0 <= resp_pair[1] && resp_pair[0] < n);
        assert(resp_pair[0] != resp_pair[1]);
    }
#endif
    int nh{}; // number of hierarchies

    std::vector<std::vector<int>> c(static_cast<size_t>(n)); // children
    for (const auto& rp /* respect pair */ : respect_list) {
        c[static_cast<size_t>(rp[0])].push_back(rp[1]);
        c[static_cast<size_t>(rp[1])].push_back(rp[0]);
    }

    std::set<int> v; // visited
    for (int r = 0; r < n; ++r) {
        v.insert(r);
        std::cout << r;
        if (static_cast<int>(v.size()) == n) {
            std::cout << "; ";
            ++nh;
        } else
            recurse_children(nh, v, n, c, r);
        v.erase(r);
    }

    assert(1 <= nh && nh < 1'000'000'007);
    return nh;
}
} // namespace mb

namespace chatgpt {
using std::vector;

// Function to check if it's possible to add the pair (a, b) to the hierarchy
bool is_valid(int a, int b, vector<vector<int>>& respect_list, vector<int>& hierarchy) {
    // Check if a respects b
    if (find(respect_list[a].begin(), respect_list[a].end(), b) == respect_list[a].end()) {
        return false;
    }

    // Check if b respects a
    if (find(respect_list[b].begin(), respect_list[b].end(), a) == respect_list[b].end()) {
        return false;
    }

    // Check if a and b are already in the hierarchy
    if (hierarchy[a] != -1 && hierarchy[b] != -1) {
        return false;
    }

    // Check if a is already a descendant of b or vice versa
    if (hierarchy[a] != -1 && hierarchy[b] != -1) {
        int curr_a = a;
        int curr_b = b;
        while (hierarchy[curr_a] != -1) {
            curr_a = hierarchy[curr_a];
        }
        while (hierarchy[curr_b] != -1) {
            curr_b = hierarchy[curr_b];
        }
        if (curr_a == curr_b) {
            return false;
        }
    }

    return true;
}

// DFS function to find all the possible hierarchies
void dfs(int curr, vector<vector<int>>& respect_list, vector<int>& hierarchy, int& count) {
    // If we have assigned a parent to all the employees, increment the count
    if (curr == hierarchy.size()) {
        count++;
        return;
    }

    // Try all the possible pairs of (curr, x) where x is an employee who respects curr
    for (int x : respect_list[curr]) {
        if (is_valid(curr, x, respect_list, hierarchy)) {
            hierarchy[curr] = x;
            dfs(curr + 1, respect_list, hierarchy, count);
            hierarchy[curr] = -1;
        }
    }
}

int solution(int n, vector<vector<int>> respect_list) {
    // Initialize the hierarchy with all employees having no parent (-1)
    vector<int> hierarchy(n, -1);

    // Initialize the count of different hierarchies
    int count = 0;

    // Start the DFS from the first employee
    dfs(0, respect_list, hierarchy, count);

    return count;
}

UL_PRAGMA_WARNINGS_POP
} // namespace chatgpt
} // namespace

UL_PRAGMA_WARNINGS_POP

int main() {
    std::cout << solution(4, {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {1, 3}}) << "\n"; // expected 32
    std::cout << solution(3, {{0, 1}, {1, 2}, {0, 2}}) << "\n"; // expected 9
    return 0;
}