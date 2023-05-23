#ifndef VARIANT_DECL_H_DH239784
#define VARIANT_DECL_H_DH239784

#include "type_a_decl.h"
#include "type_b_decl.h"
#include <variant>

using Var = std::variant<TypeA, TypeB>;

#endif
