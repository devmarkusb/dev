#include "args.h"
import m1;

int main(int argc, char** argv) {
    const auto [args, exitCode]{Args::parse_command_line(argc, argv)};

    if (!args) {
        return exitCode;
    }

    std::cout << f(41);

    return 0;
}
