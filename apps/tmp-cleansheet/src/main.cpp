#include "util/allthethings.h"

namespace {
void f(int) {
}

template<typename>
struct DomainDecl;

template<>
struct DomainDecl<decltype(&f)> {
    using Type = int;
};

template<typename T>
struct DomainDecl<std::plus<T>> {
    using Type = T;
};

template<typename F>
using Domain = DomainDecl<F>::Type;

template<typename F>
concept UnaryInvocable = std::invocable<F, Domain<F>>;

template<typename F>
concept BinaryInvocable = std::invocable<F, Domain<F>, Domain<F>>;

template<typename T>
concept Plus = BinaryInvocable<std::plus<T>>;

void g(UnaryInvocable auto) {
}

void h(Plus auto) {
}
}

int main(int, char*[]) {
    f(1);
    g(f);
    h(std::plus<std::string>{});

    return 0;
}
