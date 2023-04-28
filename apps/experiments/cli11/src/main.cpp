#include "args.h"
#include "console_table.h"

int main(int argc, char** argv) {
    const auto [args, exitCode]{Args::parseCommandLine(argc, argv)};

    if (!args) {
        return exitCode;
    }

    printTableOfArgs(*args);

    return 0;
}