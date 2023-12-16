#ifndef ARGS_H_OIUFH3478TXB7394B4G4387561543
#define ARGS_H_OIUFH3478TXB7394B4G4387561543

#include "CLI/CLI.hpp"
#include <optional>
#include <string>

struct Args {
    static std::pair<std::optional<Args>, int> parse_command_line(int argc, char** argv) {
        Args args;
        CLI::App app{"C++ Modules experimental app"};

        std::optional<Args> res_args;
        int exit_code{};
        try {
            app.parse(argc, argv);
            res_args = args;
        } catch (const CLI::ParseError& e) {
            exit_code = app.exit(e);
        }

        return std::make_pair(res_args, exit_code);
    }
};

#endif
