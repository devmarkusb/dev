#include "args.h"
#include "ul/ul.h"

namespace {
const size_t some_nr{5};

void f(bool& crash, size_t& nr) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if (++nr == some_nr) {
        crash = true;
    }
}
}

int main(int argc, char** argv) {
    const auto [args, exitCode]{Args::parse_command_line(argc, argv)};

    if (!args) {
        return exitCode;
    }

    bool crash{};

    size_t nr{0};
    while (true) {
        f(crash, nr);
        if (crash) {
            ul::crash(SIGABRT);
        }
    }

    return 0;
}
