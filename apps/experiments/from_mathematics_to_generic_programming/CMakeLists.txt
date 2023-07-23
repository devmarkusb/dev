project(from_mathematics_to_generic_programming)

add_executable(multiplyBm
    src/math.h
    src/multiply.bm.cpp
    src/multiply.cpp
    src/multiply.h
)
target_include_directories(multiplyBm PRIVATE ${ul_INCLUDE_DIRS})
target_link_libraries(multiplyBm benchmark::benchmark benchmark::benchmark_main)


add_executable(mathTest
    src/ch13-crypt.h
    src/ch13-crypt.test.cpp
    src/math.h
    src/math.test.cpp
    src/multiply.cpp
    src/multiply.h
    src/multiply.test.cpp
    src/permutation.h
    src/permutation.test.cpp
)
ul_add_test(mathTest)
target_include_directories(mathTest PRIVATE ${ul_INCLUDE_DIRS})
target_link_libraries(mathTest gtest_main)


add_executable(prime-sieveTest
    src/prime-sieve.h
    src/prime-sieve.test.cpp
)
ul_add_test(prime-sieveTest)
target_include_directories(prime-sieveTest PRIVATE ${ul_INCLUDE_DIRS})
target_link_libraries(prime-sieveTest gtest_main)


add_executable(prime-sieveBm
    src/prime-sieve.bm.cpp
    src/prime-sieve.h
)
target_include_directories(prime-sieveBm PRIVATE ${ul_INCLUDE_DIRS})
target_link_libraries(prime-sieveBm benchmark::benchmark benchmark::benchmark_main)


ul_include(matplotlib-cpp.cmake)
add_executable(prime-graph
    src/prime-sieve.h
    src/prime-graph.cpp
)
target_include_directories(prime-graph PRIVATE ${ul_INCLUDE_DIRS} ${matplotlib-cpp_INCLUDE_DIRS})
target_link_libraries(prime-graph PRIVATE matplotlib_cpp)


add_executable(prime-palindromes
    src/prime-sieve.h
    src/prime-palindromes.cpp
)
target_include_directories(prime-palindromes PRIVATE ${ul_INCLUDE_DIRS})


add_executable(gcmTest
    src/gcm.h
    src/gcm.test.cpp
)
ul_add_test(gcmTest)
target_include_directories(gcmTest PRIVATE ${ul_INCLUDE_DIRS})
target_link_libraries(gcmTest gtest_main)


add_executable(gcmBm
    src/gcm.bm.cpp
    src/gcm.h
)
target_include_directories(gcmBm PRIVATE ${ul_INCLUDE_DIRS})
target_link_libraries(gcmBm benchmark::benchmark benchmark::benchmark_main)
