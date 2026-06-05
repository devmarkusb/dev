#include "util/allthethings.h"

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

namespace mb {
UL_PRAGMA_WARNINGS_PUSH
// clang-format off
UL_WARNING_DISABLE_CLANG(sign-conversion)
UL_WARNING_DISABLE_CLANG(missing-prototypes)

// clang-format on

[[maybe_unused]] int solution(int n, const std::vector<std::vector<int>>& tree) {
    UL_EXPECT(n >= 2);
    UL_EXPECT(tree.size() == static_cast<size_t>(n - 1));
    for (const auto& e : tree) {
        UL_EXPECT(e.size() == 2);
        UL_EXPECT(0 <= e[0] && e[0] < n);
        UL_EXPECT(0 <= e[1] && e[1] < n);
        UL_EXPECT(e[0] != e[1]);
    }

    // convert input to adjacency list
    const size_t n_sz = nonneg_sz(n);
    std::vector<std::vector<size_t>> tree_adjlist(n_sz);
    for (const auto& e : tree) {
        const size_t u = vec_idx(e[0], n_sz);
        const size_t v = vec_idx(e[1], n_sz);
        tree_adjlist[u].push_back(v);
        tree_adjlist[v].push_back(u);
    }

    // calc path lengths between any two nodes; Prio-DFS, max. distance has highest prio
    std::pair<int, size_t> max_d{};
    size_t start = 0;
    for (int i = 1; i <= 2; ++i) {
        std::vector<size_t> dad(n_sz, n_sz);
        std::vector<int> dist(n_sz, 0);
        std::queue<size_t> nodes;
        nodes.push(start);

        while (!nodes.empty()) {
            const size_t node = nodes.front();
            nodes.pop();

            if (dist[node] > max_d.first) {
                max_d.first = dist[node];
                max_d.second = node;
            }

            for (size_t a : tree_adjlist[node]) {
                if (dad[node] == a)
                    continue;
                dad[a] = node;
                nodes.push(a);
                dist[a] = dist[node] + 1;
            }
        }

        start = max_d.second;
    }

    return max_d.first;
}

UL_PRAGMA_WARNINGS_POP
} // namespace mb

inline namespace chatgpt {
UL_PRAGMA_WARNINGS_PUSH
UL_WARNING_DISABLE_CLANG_ALL
// clang-format off
UL_WARNING_DISABLE_GCC(sign-compare)
UL_WARNING_DISABLE_GCC(unused-function)
// clang-format on
using std::vector;

int solution(int n, const vector<vector<int>>& tree) {
    UL_EXPECT(n > 0);
    const size_t n_sz = nonneg_sz(n);
    UL_EXPECT(tree.size() == n_sz);
    for (int i = 0; i < n; ++i) {
        const size_t i_i = vec_idx(i, n_sz);
        UL_EXPECT(!tree[i_i].empty());
        UL_EXPECT(0 <= tree[i_i][0] && tree[i_i][0] < n);
    }

    // Initialize a vector to store the maximum depth of each vertex.
    vector<int> max_depths(n_sz, -1);

    // Initialize a variable to store the maximum depth of the tree.
    int max_depth = 0;

    // Iterate through all the vertices of the tree.
    for (int i = 0; i < n; i++) {
        const size_t i_i = vec_idx(i, n_sz);
        // Initialize a variable to store the current depth.
        int depth = 0;

        // Follow the path from the current vertex to the root of the tree, keeping track of the depth.
        int j = i;
        size_t j_i = vec_idx(j, n_sz);
        while (max_depths[j_i] == -1) {
            j = tree[j_i][0];
            j_i = vec_idx(j, n_sz);
            depth++;
        }

        // Add the depth of the current vertex to the maximum depths vector.
        const size_t parent_i = vec_idx(tree[i_i][0], n_sz);
        max_depths[i_i] = depth + max_depths[parent_i];

        // Update the maximum depth of the tree if necessary.
        max_depth = std::max(max_depth, max_depths[i_i]);
    }

    // Return the maximum depth of the tree.
    return max_depth;
}

UL_PRAGMA_WARNINGS_POP
} // namespace chatgpt
} // namespace

int main() {
    std::cout << solution(3, {{1, 2}, {2, 0}}) << "\n"; // expected 2
    return 0;
}
