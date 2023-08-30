#include "util/allthethings.h"

struct S {
    int i{};
};

template<typename T>
concept ContextC = ul::AnyOf<T, int, S>;


int f(const ContextC auto& t) {
    if constexpr (std::is_same_v<decltype(t), S>) {
        return t.i;
    } else {
        return {};
    }
}

int main(int, char*[]) {
    f(42);
    f(S{2});
    return 0;
}
