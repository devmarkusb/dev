#ifndef REGULAR_TYPE_H_O3XTINH23478GTY2347G
#define REGULAR_TYPE_H_O3XTINH23478GTY2347G

#include "util/allthethings.h"

struct RegularEx1 {};

inline bool operator==(const RegularEx1&, const RegularEx1&) {
    return true;
}

template <typename Regular>
void check_regularity(const Regular& r) {
    Regular r_other;
    bool _{r == r_other};
    ul::ignore_unused(_);
    Regular r_copied_from{r};
    ul::ignore_unused(r_copied_from);
    r_other = r;
    // total ordering?
    // underlying type?
}

inline void check_regularity() {
    RegularEx1 r;
    check_regularity(r);
}

#endif
