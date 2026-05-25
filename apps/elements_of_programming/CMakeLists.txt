project(elements_of_programming)
set(target ${PROJECT_NAME})

mb_ul_include(cli11.cmake)

add_executable(${target} src/args.h src/main.cpp)
target_link_libraries(${target} PRIVATE CLI11::CLI11 ConsoleTableLib util)

if(MB_DEV_BUILD_TESTS)
    mb_devenv_add_test(${target}-test PRIVATE util)
    target_sources(${target}-test PRIVATE src/exercises.cpp src/exercises.h)
endif()

add_executable(${target}-eop-code src/eop-code/eop.cpp)
target_link_libraries(${target}-eop-code PRIVATE mb::util)
