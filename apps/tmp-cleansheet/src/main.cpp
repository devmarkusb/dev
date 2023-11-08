#include "util/allthethings.h"

template <typename F>
concept HasCallMethod = requires(F f) { f.call(); };
template <typename F>
concept HasCallOp = requires(F) { decltype(&F::operator()){}; };

struct Foo {
//    int call(){ return {};}
    void call(){}
    void operator()(int){}
};

namespace {
template <typename T>
struct Info {
static auto choose_type() {
    if constexpr (HasCallMethod<T>) {
        return std::type_identity<decltype(T{}.call())>{};
    } else {
        return std::type_identity<T>{};
    }
}

using Type = typename decltype(choose_type())::type;
};

template <typename T>
struct Info2 {
    using Type = decltype(&T::operator());
};
}

int main()
{
//    using Choice = /*std::conditional_t*/apply_if_t<HasCallMethod<Foo>, decltype(Foo{}.call()), decltype(Foo{}.call())>;
    if constexpr (HasCallMethod<Foo>)
        std::cout << "has! " << std::endl;
    else
        std::cout << "no!" << std::endl;
    if constexpr (std::is_same_v<Info<Foo>::Type, void>)
        std::cout << "void! " << std::endl;
    else
        std::cout << "other!" << std::endl;
    if constexpr (std::is_same_v<Info2<Foo>::Type, void(Foo::*)(int)>)
        std::cout << "void! " << std::endl;
    else
        std::cout << "other!" << std::endl;
    if constexpr (HasCallOp<Foo>)
        std::cout << "y! " << std::endl;
    else
        std::cout << "n!" << std::endl;
}