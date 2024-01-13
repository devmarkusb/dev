module;

#include <iostream>

export module m1;

namespace m1 {
export int f(int x) {
    std::cout << "hello from f\n";
    return x + 1;
}
} // namespace m1
