#ifndef TYPE_B_fhun3478gh
#define TYPE_B_fhun3478gh

#include "type_b_decl.h"
#include "variant_decl.h"
#include <variant>

inline int doSthSpecific(const TypeB&, const Var& v) {
    Var aLocalOne{TypeA{}};
    return 2
           + std::visit(
               [&aLocalOne](const auto& t) {
                   return doSthSpecific(t, aLocalOne);
               },
               v);
}

#endif
