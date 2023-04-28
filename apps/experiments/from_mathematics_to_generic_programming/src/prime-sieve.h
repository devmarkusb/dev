#ifndef PRIME_SIEVE_H_sfib53gb2493gx5
#define PRIME_SIEVE_H_sfib53gb2493gx5

#include "ul/ul.h"
#include <algorithm>
#include <type_traits>

namespace math {
template <typename>
concept RandomAccessIterator = true;

template <typename T>
concept Integral = std::is_integral_v<T>;

namespace impl {
template <RandomAccessIterator I, Integral N>
void mark_sieve(I first, I last, N factor) {
    UL_EXPECT(first != last);
    *first = false;
    while (last - first > factor) {
        first = first + factor;
        *first = false;
    }
}
} // namespace impl

//template <RandomAccessIterator I, Integer N>
//void sift0(I first, N n)
//{
//    std::fill(first, first + n, true);
//    N i(0);
//    N index_square(3);
//    while (index_square < n)
//    {
//        // invariant: index_square = 2i^2 + 6i + 3
//        if (first[i])
//        {
//            // if candidate is prime
//            mark_sieve(
//                first + index_square,
//                first + n, // last
//                i + i + 3); // factor
//        }
//        ++i;
//        index_square = 2 * i * (i + 3) + 3;
//    }
//}
//
//template <RandomAccessIterator I, Integer N>
//void sift1(I first, N n)
//{
//    I last = first + n;
//    std::fill(first, last, true);
//    N i(0);
//    N index_square(3);
//    N factor(3);
//    while (index_square < n)
//    {
//        // invariant: index_square = 2i^2 + 6i + 3,
//        // factor = 2i + 3
//        if (first[i])
//        {
//            mark_sieve(first + index_square, last, factor);
//        }
//        ++i;
//        factor = i + i + 3;
//        index_square = 2 * i * (i + 3) + 3;
//    }
//}

template <RandomAccessIterator I, Integral N>
void sift2(I first, N n) {
    I last = first + n;
    std::fill(first, last, true);
    N i(0);
    N index_square(3);
    N factor(3);
    while (index_square < n) {
        // invariant: index_square = 2i^2 + 6i + 3,
        // factor = 2i + 3
        if (first[i]) {
            impl::mark_sieve(first + index_square, last, factor);
        }
        ++i;
        index_square += factor;
        factor += N(2);
        index_square += factor;
    }
}
} // namespace math

#endif
