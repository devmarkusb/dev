project(elements_of_programming)
set(target ${PROJECT_NAME})

ul_include(cli11.cmake)

add_executable(${target}
    src/args.h
    src/main.cpp
)
target_include_directories(${target} PUBLIC ${lib_util_INCLUDE_DIRS})
target_include_directories(${target} PUBLIC ${ul_INCLUDE_DIRS})
target_link_libraries(${target} PRIVATE CLI11::CLI11 ConsoleTableLib)

add_executable(${target}-test
    src/exercises.cpp
    src/exercises.h
    src/exercises.test.cpp
)
ul_add_test(${target}-test)
target_include_directories(${target}-test PUBLIC ${lib_util_INCLUDE_DIRS})
target_include_directories(${target}-test PRIVATE ${ul_INCLUDE_DIRS})
target_link_libraries(${target}-test gtest_main)

add_executable(${target}-eop-code
    src/eop-code/eop.cpp
)
target_include_directories(${target}-eop-code PUBLIC ${ul_INCLUDE_DIRS})
