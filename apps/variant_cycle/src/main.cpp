#include "variant.h"
#include "util/allthethings.h"

int main(int, char*[]) {
    Var v{TypeB{}};
    std::cout << do_sth(v);
    return 0;
}
