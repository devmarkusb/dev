#ifndef CONSOLE_TABLE_H_ouixh3gn478ghy3479y
#define CONSOLE_TABLE_H_ouixh3gn478ghy3479y

#include "args.h"

#include "ConsoleTable.h"

inline void printTableOfArgs(const Args& args) {
    ConsoleTable argsTable{"arg", "content"};
    argsTable.setStyle(0);

    argsTable += {"text", args.text_};
    argsTable += {"int", std::to_string(args.int_)};

    std::cout << argsTable;
}

#endif
