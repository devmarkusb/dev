#include "util/allthethings.h"
#include <cassert>

namespace
{
inline namespace mb
{
void recurseChildren(
    int& numHierarchies, std::set<int>& visited, int n, const std::vector<std::vector<int>>& children, int parent)
{
    auto& v{visited};
    auto& nh{numHierarchies};
    for (int c /* child */ : children[static_cast<size_t>(parent)])
    {
        auto [_, inserted]{v.insert(c)};
        if (!inserted)
            continue;
        std::cout << "->" << c;
        if (static_cast<int>(v.size()) == n)
        {
            std::cout << "; ";
            ++nh;
        }
        else
            recurseChildren(nh, v, n, children, c);
        v.erase(c);
    }
}

[[maybe_unused]] int solution(int n, const std::vector<std::vector<int>>& respectList)
{
    assert(1 <= n && n <= 100);
    assert(n - 1 <= static_cast<int>(respectList.size()) && static_cast<int>(respectList.size()) <= n * (n - 1) / 2);
#ifndef NDEBUG
    for (const auto& respPair : respectList)
    {
        assert(respPair.size() == 2);
        assert(0 <= respPair[0] && respPair[0] < n);
        assert(0 <= respPair[1] && respPair[0] < n);
        assert(respPair[0] != respPair[1]);
    }
#endif
    int nh{}; // number of hierarchies

    std::vector<std::vector<int>> c(static_cast<size_t>(n)); // children
    for (const auto& rp /* respect pair */ : respectList)
    {
        c[static_cast<size_t>(rp[0])].push_back(rp[1]);
        c[static_cast<size_t>(rp[1])].push_back(rp[0]);
    }

    std::set<int> v; // visited
    for (int r = 0; r < n; ++r)
    {
        v.insert(r);
        std::cout << r;
        if (static_cast<int>(v.size()) == n)
        {
            std::cout << "; ";
            ++nh;
        }
        else
            recurseChildren(nh, v, n, c, r);
        v.erase(r);
    }

    assert(1 <= nh && nh < 1'000'000'007);
    return nh;
}
} // namespace mb

namespace chatgpt
{
UL_PRAGMA_WARNINGS_PUSH
UL_WARNING_DISABLE_CLANG_ALL
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-function"
using std::vector;

// Function to check if it's possible to add the pair (a, b) to the hierarchy
bool isValid(int a, int b, vector<vector<int>>& respectList, vector<int>& hierarchy)
{
    // Check if a respects b
    if (find(respectList[a].begin(), respectList[a].end(), b) == respectList[a].end())
    {
        return false;
    }

    // Check if b respects a
    if (find(respectList[b].begin(), respectList[b].end(), a) == respectList[b].end())
    {
        return false;
    }

    // Check if a and b are already in the hierarchy
    if (hierarchy[a] != -1 && hierarchy[b] != -1)
    {
        return false;
    }

    // Check if a is already a descendant of b or vice versa
    if (hierarchy[a] != -1 && hierarchy[b] != -1)
    {
        int currA = a;
        int currB = b;
        while (hierarchy[currA] != -1)
        {
            currA = hierarchy[currA];
        }
        while (hierarchy[currB] != -1)
        {
            currB = hierarchy[currB];
        }
        if (currA == currB)
        {
            return false;
        }
    }

    return true;
}

// DFS function to find all the possible hierarchies
void dfs(int curr, vector<vector<int>>& respectList, vector<int>& hierarchy, int& count)
{
    // If we have assigned a parent to all the employees, increment the count
    if (curr == hierarchy.size())
    {
        count++;
        return;
    }

    // Try all the possible pairs of (curr, x) where x is an employee who respects curr
    for (int x : respectList[curr])
    {
        if (isValid(curr, x, respectList, hierarchy))
        {
            hierarchy[curr] = x;
            dfs(curr + 1, respectList, hierarchy, count);
            hierarchy[curr] = -1;
        }
    }
}

int solution(int n, vector<vector<int>> respectList)
{
    // Initialize the hierarchy with all employees having no parent (-1)
    vector<int> hierarchy(n, -1);

    // Initialize the count of different hierarchies
    int count = 0;

    // Start the DFS from the first employee
    dfs(0, respectList, hierarchy, count);

    return count;
}

UL_PRAGMA_WARNINGS_POP
} // namespace chatgpt
} // namespace

int main()
{
    std::cout << solution(4, {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {1, 3}}) << "\n"; // expected 32
    std::cout << solution(3, {{0, 1}, {1, 2}, {0, 2}}) << "\n"; // expected 9
    return 0;
}