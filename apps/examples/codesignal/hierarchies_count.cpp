#include "util/allthethings.h"
#include <cassert>

namespace
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

int solution(int n, const std::vector<std::vector<int>>& respectList)
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
} // namespace

int main()
{
    std::cout << solution(3, {{0, 1}, {1, 2}, {0, 2}});
    return 0;
}