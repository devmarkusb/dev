#ifndef GCM_H_XM5GUIH8349HX3894H891HG
#define GCM_H_XM5GUIH8349HX3894H891HG

#include "math.h"
#include "mb/ul/ul.hpp"
#include <algorithm>

namespace math {
using LineSegment = int;

inline LineSegment gcm0(LineSegment a, LineSegment b) {
    UL_EXPECT(b > 0);
    UL_EXPECT(a > 0);
    if (a == b)
        return a;
    if (a < b)
        return gcm0(a, b - a);
    else
        return gcm0(a - b, b);
}

inline LineSegment gcm1(LineSegment a, LineSegment b) {
    UL_EXPECT(b > 0);
    UL_EXPECT(a > 0);
    while (a != b) {
        if (a < b)
            b -= a;
        else
            a -= b;
    }
    return a;
}

inline LineSegment gcm2(LineSegment a, LineSegment b) {
    UL_EXPECT(b > 0);
    UL_EXPECT(a > 0);
    while (a != b) {
        while (a > b)
            a -= b;
        std::swap(a, b);
    }
    return a;
}

inline LineSegment segment_remainder0(LineSegment a, LineSegment b) {
    UL_EXPECT(b > 0);
    UL_EXPECT(a > 0);
    while (a > b)
        a -= b;
    return a;
}

inline LineSegment segment_remainder1(LineSegment a, LineSegment b) {
    UL_EXPECT(b > 0);
    UL_EXPECT(a > 0);
    if (a <= b)
        return a;
    if (a - b <= b)
        return a - b;
    a = segment_remainder1(a, b + b);
    if (a <= b)
        return a;
    return a - b;
}

inline LineSegment remainder0(LineSegment a, LineSegment b) {
    UL_EXPECT(b > 0);
    if (a < b)
        return a;
    if (a - b < b)
        return a - b;
    a = remainder0(a, b + b);
    if (a < b)
        return a;
    return a - b;
}

inline LineSegment largest_doubling(LineSegment a, LineSegment b) {
    UL_EXPECT(b > 0);
    while (a - b >= b)
        b += b;
    return b;
}

inline LineSegment remainder1(LineSegment a, LineSegment b) {
    UL_EXPECT(b > 0);
    if (a < b)
        return a;
    auto c = largest_doubling(a, b);
    a -= c;
    while (c != b) {
        c /= 2;
        if (c <= a)
            a -= c;
    }
    return a;
}

inline LineSegment gcm3(LineSegment a, LineSegment b) {
    UL_EXPECT(b > 0);
    UL_EXPECT(a > 0);
    while (a != b) {
        a = segment_remainder0(a, b);
        std::swap(a, b);
    }
    return a;
}

//! Faster segment remainder.
inline LineSegment gcm4(LineSegment a, LineSegment b) {
    UL_EXPECT(b > 0);
    UL_EXPECT(a > 0);
    while (a != b) {
        a = segment_remainder1(a, b);
        std::swap(a, b);
    }
    return a;
}

//! Remainder instead of segment remainder.
inline LineSegment gcm5(LineSegment a, LineSegment b) {
    UL_EXPECT(b > 0);
    while (b) {
        a = remainder0(a, b);
        std::swap(a, b);
    }
    return a;
}

//! Faster remainder.
inline LineSegment gcm6(LineSegment a, LineSegment b) {
    UL_EXPECT(b > 0);
    while (b) {
        a = remainder1(a, b);
        std::swap(a, b);
    }
    return a;
}

inline int quotient0(LineSegment a, LineSegment b) {
    UL_EXPECT(b > 0);
    if (a < b)
        return 0;
    auto c = largest_doubling(a, b);
    auto n(1);
    a = a - c;
    while (c != b) {
        c /= 2;
        n = n + n;
        if (c <= a) {
            a = a - c;
            n = n + 1;
        }
    }
    return n;
}

inline std::pair<int, LineSegment> quotient_remainder0(LineSegment a, LineSegment b) {
    UL_EXPECT(b > 0);
    if (a < b)
        return {0, a};
    auto c = largest_doubling(a, b);
    auto n(1);
    a = a - c;
    while (c != b) {
        c /= 2;
        n = n + n;
        if (c <= a) {
            a = a - c;
            n = n + 1;
        }
    }
    return {n, a};
}

//! Ordinary /, %.
inline std::pair<int, LineSegment> quotient_remainder1(LineSegment a, LineSegment b) {
    UL_EXPECT(b > 0);
    return {a / b, a % b};
}

//! Fibonacci.
inline LineSegment remainder2(LineSegment a, LineSegment b) {
    UL_EXPECT(b > 0);
    if (a < b)
        return a;
    auto c = b;
    do {
        auto tmp = c;
        c = b + c;
        b = tmp;
    } while (a >= c);
    do {
        if (a >= b)
            a = a - b;
        auto tmp = c - b;
        c = b;
        b = tmp;
    } while (b < c);
    return a;
}

//! Fibonacci.
inline std::pair<int, LineSegment> quotient_remainder2(LineSegment a, LineSegment b) {
    UL_EXPECT(b > 0);
    if (a < b)
        return {0, a};
    auto c{b};
    do {
        auto tmp = c;
        c += b;
        b = tmp;
    } while (a >= c);
    auto n{1};
    //auto m{n};
    do {
        ++n;
        if (a >= b) {
            a -= b;
            //auto tmp2{n};
            //n += m;
            //m = tmp2;
        }
        auto tmp = c - b;
        c = b;
        b = tmp;
    } while (b < c);
    return {n, a};
}

template <EuclideanDomainAddMult E>
E gcd(E a, E b) {
    while (b != E(0)) {
        a = a % b;
        std::swap(a, b);
    }
    return a;
}

template <EuclideanDomainAddMult E>
std::pair<E, E> extended_gcd(E a, E b) {
    E x0{1};
    E x1{0};
    while (b != E{0}) {
        // compute new r and x
        auto qr = quotient_remainder1(a, b);
        E x2 = x0 - qr.first * x1;
        // shift r and x
        x0 = x1;
        x1 = x2;
        a = b;
        b = qr.second;
    }
    return {x0, a};
}

template <EuclideanDomainAddMult E>
E bezout_y(E x, E a, E b) {
    return (gcd(a, b) - a * x) / b;
}

template <BinaryInteger N>
N gcd_stein(N m, N n) {
    if constexpr (std::is_signed_v<N>) {
        if (m < N(0))
            m = -m;
        if (n < N(0))
            n = -n;
    }
    if (m == N(0))
        return n;
    if (n == N(0))
        return m;
    UL_ASSERT(m > 0 && n > 0);
    int d_m = 0;
    while (even(m)) {
        m >>= 1;
        ++d_m;
    }
    int d_n = 0;
    while (even(n)) {
        n >>= 1;
        ++d_n;
    }
    UL_ASSERT(odd(m) && odd(n));
    while (m != n) {
        if (n > m)
            std::swap(n, m);
        m -= n;
        do
            m >>= 1;
        while (even(m));
    }
    UL_ASSERT(m == n);
    return static_cast<N>(m << std::min(d_m, d_n));
}
} // namespace math

#endif
