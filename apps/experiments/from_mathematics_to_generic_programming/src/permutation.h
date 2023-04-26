#ifndef PERMUTATION_H_porihgx789x34789hg89734g
#define PERMUTATION_H_porihgx789x34789hg89734g

#include "math.h"
#include <algorithm>
#include <iterator>
#include <utility>

namespace math
{
template <std::forward_iterator I0, std::forward_iterator I1>
std::pair<I0, I1> swap_ranges(I0 first0, I0 last0, I1 first1, I1 last1)
{
    while (first0 != last0 && first1 != last1)
    {
        std::swap(*first0++, *first1++);
    }
    return {first0, first1};
}

template <std::forward_iterator I0, std::forward_iterator I1, Integer N>
std::pair<I0, I1> swap_ranges_n(I0 first0, I1 first1, N n)
{
    while (n != N(0))
    {
        std::swap(*first0++, *first1++);
        --n;
    }
    return {first0, first1};
}

template <std::forward_iterator I>
void gries_mills_rotate(I f, I m, I l)
{
    // u = distance(f, m) && v = distance(m, l)
    if (f == m || m == l)
        return; // u == 0 || v == 0
    std::pair<I, I> p = swap_ranges(f, m, m, l);
    while (p.first != m || p.second != l)
    {
        if (p.first == m)
        { // u < v
            f = m;
            m = p.second; // v = v - u
        }
        else
        { // v < u
            f = p.first; // u = u - v
        }
        p = swap_ranges(f, m, m, l);
    }
    // u == v
}

// Just working, not sure if that's the expected solution.
template <std::forward_iterator I>
void gries_mills_rotate_n(I f, I m, I l)
{
    auto u = std::distance(f, m);
    auto v = std::distance(m, l);
    if (u == 0 || v == 0)
        return;
    std::pair<I, I> p = swap_ranges_n(f, m, std::min(u, v));
    while (u != v)
    {
        if (u < v)
        {
            f = m;
            m = p.second;
            v = v - u;
        }
        else
        {
            UL_ASSERT(v < u);
            f = p.first;
            u = u - v;
        }
        p = swap_ranges_n(f, m, std::min(u, v));
    }
    UL_ASSERT(u == v);
}
} // namespace math

#endif
