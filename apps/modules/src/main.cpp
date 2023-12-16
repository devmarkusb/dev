#include "args.h"
import m1;
import m2;

int main(int argc, char** argv) {
    const auto [args, exitCode]{Args::parse_command_line(argc, argv)};

    if (!args) {
        return exitCode;
    }

    std::cout << m1::f(41);
    std::cout << m2::f(41);

    return 0;
}
