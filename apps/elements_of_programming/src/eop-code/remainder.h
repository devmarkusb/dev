#ifndef EOP_REMAINDER
#define EOP_REMAINDER

#include "intrinsics.h"

template <typename T>
REQUIRES(ArchimedeanMonoid(T))
T remainder_recursive(T a, T b) {
    // Precondition: $a \geq b > 0$
    if (a - b >= b) {
        a = remainder_recursive(a, b + b);
        if (a < b)
            return a;
    }
    return a - b;
}

template <typename T>
REQUIRES(ArchimedeanMonoid(T))
T remainder_nonnegative(T a, T b) {
    // Precondition: $a \geq 0 \wedge b > 0$
    if (a < b)
        return a;
    return remainder_recursive(a, b);
}

// Default remainder for EuclideanSemiring

template <typename T>
REQUIRES(EuclideanSemiring(T))
T remainder(T a, T b) {
    return a % b;
}

// Default remainder for EuclideanSemimodule

template <typename T, typename S>
REQUIRES(EuclideanSemimodule(T, S))
T remainder(T a, T b) {
    return remainder_nonnegative(a, b);
}

#endif
