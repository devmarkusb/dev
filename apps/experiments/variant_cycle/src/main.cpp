#include "variant.h"
#include "util/allthethings.h"

int main(int, char*[]) {
    Var v{TypeB{}};
    std::cout << doSth(v);
    return 0;
}
