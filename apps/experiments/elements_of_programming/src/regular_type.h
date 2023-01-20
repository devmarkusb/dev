#ifndef REGULAR_TYPE_H_o3xtinh23478gty2347g
#define REGULAR_TYPE_H_o3xtinh23478gty2347g

#include "util/allthethings.h"

struct RegularEx1
{
};

inline bool operator==(const RegularEx1&, const RegularEx1&)
{
    return true;
}

template <typename Regular>
void checkRegularity(const Regular& r)
{
    Regular rOther;
    bool _{r == rOther};
    ul::ignore_unused(_);
    Regular rCopiedFrom{r};
    ul::ignore_unused(rCopiedFrom);
    rOther = r;
    // total ordering?
    // underlying type?
}

inline void checkRegularity()
{
    RegularEx1 r;
    checkRegularity(r);
}

#endif
