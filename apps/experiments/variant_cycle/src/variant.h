#ifndef VARIANT_H_EIHT3498
#define VARIANT_H_EIHT3498

#include "type_a.h"
#include "type_b.h"
#include "variant_decl.h"
#include <variant>

inline int do_sth(const Var& v) {
    Var a_local_one{TypeB{}};
    return std::visit(
        [&a_local_one](const auto& t) {
            return doSthSpecific(t, a_local_one);
        },
        v);
}

#endif
