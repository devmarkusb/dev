#ifndef ARGS_H_oiufh3478txb7394b4g
#define ARGS_H_oiufh3478txb7394b4g

#include "CLI/CLI.hpp"
#include <optional>
#include <string>

struct Args
{
    std::string text_{"some text"};
    int int_{42};

    static std::pair<std::optional<Args>, int> parseCommandLine(int argc, char** argv)
    {
        Args args;
        CLI::App app{"CLI11 lib experimental app"};

        app.add_option("-t,--text", args.text_, "some text");
        app.add_option("-i,--int", args.int_, "some integer");

        std::optional<Args> resArgs;
        int exitCode{};
        try
        {
            app.parse(argc, argv);
            resArgs = args;
        }
        catch (const CLI::ParseError& e)
        {
            exitCode = app.exit(e);
        }

        return std::make_pair(resArgs, exitCode);
    }
};

#endif
