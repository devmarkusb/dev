project(from_mathematics_to_generic_programming)

add_executable(multiplyBm
    src/multiply.bm.cpp
    src/multiply.cpp
    src/multiply.h
)
target_include_directories(multiplyBm PRIVATE ${ul_INCLUDE_DIRS})
target_link_libraries(multiplyBm benchmark::benchmark benchmark::benchmark_main)


add_executable(prime-sieveTest
        src/prime-sieve.h
        src/prime-sieve.test.cpp
        )
ul_add_test(prime-sieveTest)
target_include_directories(prime-sieveTest PRIVATE ${ul_INCLUDE_DIRS})
target_link_libraries(prime-sieveTest gtest_main)


ul_include(matplotlib-cpp.cmake)
add_executable(prime-graph
        src/prime-sieve.h
        src/prime-graph.cpp
        )
target_include_directories(prime-graph PRIVATE ${ul_INCLUDE_DIRS} ${matplotlib-cpp_INCLUDE_DIRS})
target_link_libraries(prime-graph PRIVATE matplotlib_cpp)


add_executable(prime-sieveBm
        src/prime-sieve.bm.cpp
        src/prime-sieve.h
        )
target_include_directories(prime-sieveBm PRIVATE ${ul_INCLUDE_DIRS})
target_link_libraries(prime-sieveBm benchmark::benchmark benchmark::benchmark_main)
