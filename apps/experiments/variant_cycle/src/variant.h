#ifndef VARIANT_H_eiht3498
#define VARIANT_H_eiht3498

#include "variant_decl.h"
#include "type_a.h"
#include "type_b.h"
#include <variant>

int doSth(const Var& v)
{
    Var aLocalOne{TypeB{}};
    return std::visit([&aLocalOne](const auto& t) { return doSthSpecific(t, aLocalOne); }, v);
}

#endif
