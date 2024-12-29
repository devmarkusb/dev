project(debug)

ul_include(cli11.cmake)

add_executable(debug
    src/args.h
    src/main.cpp
)
target_link_libraries(debug PRIVATE CLI11::CLI11 mb-util)
