#include "args.h"
#include "entities.h"
#include "exercises.h"
#include "regular_type.h"
#include "util/allthethings.h"

int main(int argc, char** argv) {
    const auto [args, exitCode]{Args::parse_command_line(argc, argv)};

    if (!args) {
        return exitCode;
    }
    if (args->a)
        print_orbit_structure_random_nr_generators();
    return {};
}
