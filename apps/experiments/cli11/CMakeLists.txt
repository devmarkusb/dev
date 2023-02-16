project(cli11)

ul_include(cli11.cmake)
ul_include(consoletable.cmake)

add_executable(cli11-exp
    src/args.h
    src/console_table.h
    src/main.cpp
)
target_include_directories(cli11-exp PRIVATE ${ConsoleTable_INCLUDE_DIRS})
target_link_libraries(cli11-exp PRIVATE CLI11::CLI11 ConsoleTableLib)
