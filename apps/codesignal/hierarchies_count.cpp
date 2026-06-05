#include "util/allthethings.h"

UL_PRAGMA_WARNINGS_PUSH
// clang-format off
UL_WARNING_DISABLE_CLANG_ALL
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-function"

// clang-format on

namespace {
[[nodiscard]] constexpr size_t nonneg_sz(int i) {
    UL_EXPECT(i >= 0);
    return static_cast<size_t>(i);
}

[[nodiscard]] size_t vec_idx(int i, size_t size) {
    UL_EXPECT(i >= 0);
    UL_EXPECT(static_cast<size_t>(i) < size);
    return static_cast<size_t>(i);
}

inline namespace mb {
void recurse_children(
    int& num_hierarchies, std::set<int>& visited, int n, const std::vector<std::vector<int>>& children, int parent) {
    UL_EXPECT(n > 0);
    UL_EXPECT(static_cast<size_t>(n) == children.size());
    UL_EXPECT(0 <= parent && parent < n);

    auto& v{visited};
    auto& nh{num_hierarchies};
    const size_t parent_i = vec_idx(parent, children.size());
    for (int c /* child */ : children[parent_i]) {
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
    UL_EXPECT(1 <= n && n <= 100);
    UL_EXPECT(
        n - 1 <= static_cast<int>(respect_list.size()) && static_cast<int>(respect_list.size()) <= n * (n - 1) / 2);
    for (const auto& resp_pair : respect_list) {
        UL_EXPECT(resp_pair.size() == 2);
        UL_EXPECT(0 <= resp_pair[0] && resp_pair[0] < n);
        UL_EXPECT(0 <= resp_pair[1] && resp_pair[1] < n);
        UL_EXPECT(resp_pair[0] != resp_pair[1]);
    }

    int nh{}; // number of hierarchies

    const size_t n_sz = nonneg_sz(n);
    std::vector<std::vector<int>> c(n_sz); // children
    for (const auto& rp /* respect pair */ : respect_list) {
        c[vec_idx(rp[0], n_sz)].push_back(rp[1]);
        c[vec_idx(rp[1], n_sz)].push_back(rp[0]);
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

    UL_ENSURE(1 <= nh && nh < 1'000'000'007);
    return nh;
}
} // namespace mb

namespace chatgpt {
using std::vector;

// Function to check if it's possible to add the pair (a, b) to the hierarchy
bool is_valid(
    int a,
    int b,
    const vector<vector<int>>& respect_list,
    vector<int>& hierarchy) { // cppcheck-suppress constParameterReference ; hierarchy is updated.
    UL_EXPECT(respect_list.size() == hierarchy.size());
    UL_EXPECT(0 <= a && a < static_cast<int>(hierarchy.size()));
    UL_EXPECT(0 <= b && b < static_cast<int>(hierarchy.size()));

    const size_t a_i = vec_idx(a, respect_list.size());
    const size_t b_i = vec_idx(b, respect_list.size());
    const size_t a_h = vec_idx(a, hierarchy.size());
    const size_t b_h = vec_idx(b, hierarchy.size());

    // Check if a respects b
    if (find(respect_list[a_i].begin(), respect_list[a_i].end(), b) == respect_list[a_i].end()) {
        return false;
    }

    // Check if b respects a
    if (find(respect_list[b_i].begin(), respect_list[b_i].end(), a) == respect_list[b_i].end()) {
        return false;
    }

    // Check if a and b are already in the hierarchy
    if (hierarchy[a_h] != -1 && hierarchy[b_h] != -1) {
        return false;
    }

    // Check if a is already a descendant of b or vice versa
    if (hierarchy[a_h] != -1 || hierarchy[b_h] != -1) {
        int curr_a = a;
        int curr_b = b;
        size_t curr_a_h = vec_idx(curr_a, hierarchy.size());
        size_t curr_b_h = vec_idx(curr_b, hierarchy.size());
        while (hierarchy[curr_a_h] != -1) {
            curr_a = hierarchy[curr_a_h];
            curr_a_h = vec_idx(curr_a, hierarchy.size());
        }
        while (hierarchy[curr_b_h] != -1) {
            curr_b = hierarchy[curr_b_h];
            curr_b_h = vec_idx(curr_b, hierarchy.size());
        }
        if (curr_a == curr_b) {
            return false;
        }
    }

    return true;
}

// DFS function to find all the possible hierarchies
void dfs(int curr, vector<vector<int>>& respect_list, vector<int>& hierarchy, int& count) {
    UL_EXPECT(respect_list.size() == hierarchy.size());
    UL_EXPECT(0 <= curr && curr <= static_cast<int>(hierarchy.size()));

    // If we have assigned a parent to all the employees, increment the count
    if (curr == hierarchy.size()) {
        count++;
        return;
    }

    // Try all the possible pairs of (curr, x) where x is an employee who respects curr
    const size_t curr_i = vec_idx(curr, respect_list.size());
    const size_t curr_h = vec_idx(curr, hierarchy.size());
    for (int x : respect_list[curr_i]) {
        if (is_valid(curr, x, respect_list, hierarchy)) {
            hierarchy[curr_h] = x;
            dfs(curr + 1, respect_list, hierarchy, count);
            hierarchy[curr_h] = -1;
        }
    }
}

int solution(int n, vector<vector<int>> respect_list) {
    const size_t n_sz = nonneg_sz(n);
    UL_EXPECT(respect_list.size() == n_sz);
    for (const auto& neighbors : respect_list) {
        for (int x : neighbors) {
            UL_EXPECT(0 <= x && x < n);
        }
    }

    // Initialize the hierarchy with all employees having no parent (-1)
    vector<int> hierarchy(n_sz, -1);

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
