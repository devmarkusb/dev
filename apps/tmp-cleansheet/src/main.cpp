#include "util/allthethings.h"

struct Foo { using Bar = int; };

template<typename T>
void doSmth(T)
{
    if constexpr (requires { typename T::Bar; })
        std::cout << "has nested! " << typename T::Bar {} << std::endl;
    else
        std::cout << "no nested!" << std::endl;
}

int main()
{
    doSmth(Foo {});
    //doSmth(0);
}