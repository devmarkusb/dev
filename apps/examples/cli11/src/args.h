#ifndef ARGS_H_OIUFH3478TXB7394B4G
#define ARGS_H_OIUFH3478TXB7394B4G

#include "CLI/CLI.hpp"
#include <optional>
#include <string>

struct Args {
    std::string text{"some text"};
    int int_{42};

    static std::pair<std::optional<Args>, int> parse_command_line(int argc, char** argv) {
        Args args;
        CLI::App app{"CLI11 lib experimental app"};

        app.add_option("-t,--text", args.text, "some text");
        app.add_option("-i,--int", args.int_, "some integer");

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
