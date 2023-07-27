#include "args.h"
#include "console_table.h"

int main(int argc, char** argv) {
    const auto [args, exitCode]{Args::parse_command_line(argc, argv)};

    if (!args) {
        return exitCode;
    }

    print_table_of_args(*args);

    return 0;
}