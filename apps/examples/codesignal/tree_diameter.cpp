#include "util/allthethings.h"

namespace
{
namespace mb
{
UL_PRAGMA_WARNINGS_PUSH
UL_WARNING_DISABLE_CLANG(sign-conversion)

[[maybe_unused]] int solution(int n, std::vector<std::vector<int>> tree)
{
    // convert input to adjacency list
    std::vector<std::vector<size_t>> tree_adjlist(static_cast<size_t>(n));
    for (const auto& e : tree)
    {
        tree_adjlist[e[0]].push_back(e[1]);
        tree_adjlist[e[1]].push_back(e[0]);
    }

    // calc path lengths between any two nodes; Prio-DFS, max. distance has highest prio
    std::pair<int, size_t> max_d{};
    size_t start = 0;
    for (int i = 1; i <= 2; ++i)
    {
        std::vector<size_t> dad(static_cast<size_t>(n), static_cast<size_t>(n));
        std::vector<int> dist(static_cast<size_t>(n), 0);
        std::queue<size_t> nodes;
        nodes.push(start);

        size_t node{};
        while (!nodes.empty())
        {
            node = nodes.front();
            nodes.pop();

            if (dist[node] > max_d.first)
            {
                max_d.first = dist[node];
                max_d.second = node;
            }

            for (size_t a : tree_adjlist[node])
            {
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

inline namespace chatgpt
{
UL_PRAGMA_WARNINGS_PUSH
UL_WARNING_DISABLE_CLANG_ALL
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-function"
using std::vector;

int solution(int n, vector<vector<int>> tree)
{
    // Initialize a vector to store the maximum depth of each vertex.
    vector<int> max_depths(n, -1);

    // Initialize a variable to store the maximum depth of the tree.
    int max_depth = 0;

    // Iterate through all the vertices of the tree.
    for (int i = 0; i < n; i++)
    {
        // Initialize a variable to store the current depth.
        int depth = 0;

        // Follow the path from the current vertex to the root of the tree, keeping track of the depth.
        for (int j = i; max_depths[j] == -1; j = tree[j][0])
        {
            depth++;
        }

        // Add the depth of the current vertex to the maximum depths vector.
        max_depths[i] = depth + max_depths[tree[i][0]];

        // Update the maximum depth of the tree if necessary.
        max_depth = std::max(max_depth, max_depths[i]);
    }

    // Return the maximum depth of the tree.
    return max_depth;
}

UL_PRAGMA_WARNINGS_POP
} // namespace chatgpt
} // namespace

int main()
{
    std::cout << solution(3, {{1, 2}, {2, 0}}) << "\n"; // expected 2
    return 0;
}