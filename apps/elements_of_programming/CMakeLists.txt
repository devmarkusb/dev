project(elements_of_programming)
set(target ${PROJECT_NAME})

mb_ul_include(cli11.cmake)

add_executable(${target} src/args.h src/main.cpp)
target_link_libraries(${target} PRIVATE CLI11::CLI11 ConsoleTableLib util)

if(MB_DEV_BUILD_TESTS)
    add_executable(
        ${target}-test
        src/exercises.cpp
        src/exercises.h
        src/exercises.test.cpp
    )
    mb_devenv_add_simple_test(${target}-test)
    target_link_libraries(${target}-test GTest::gtest_main util)
endif()

add_executable(${target}-eop-code src/eop-code/eop.cpp)
target_link_libraries(${target}-eop-code PRIVATE mb::util)
