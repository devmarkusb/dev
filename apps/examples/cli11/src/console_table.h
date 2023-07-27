#ifndef CONSOLE_TABLE_H_OUIXH3GN478GHY3479Y
#define CONSOLE_TABLE_H_OUIXH3GN478GHY3479Y

#include "args.h"

#include "ConsoleTable.h"

inline void print_table_of_args(const Args& args) {
    ConsoleTable args_table{"arg", "content"};
    args_table.setStyle(0);

    args_table += {"text", args.text};
    args_table += {"int", std::to_string(args.int_)};

    std::cout << args_table;
}

#endif
