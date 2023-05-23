#ifndef TYPE_B_H_FHUN3478GH
#define TYPE_B_H_FHUN3478GH

#include "type_b_decl.h"
#include "variant_decl.h"
#include <variant>

inline int doSthSpecific(const TypeB&, const Var& v) {
    Var a_local_one{TypeA{}};
    return 2
           + std::visit(
               [&a_local_one](const auto& t) {
                   return doSthSpecific(t, a_local_one);
               },
               v);
}

#endif
