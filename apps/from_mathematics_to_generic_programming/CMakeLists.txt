project(from_mathematics_to_generic_programming)

add_executable(multiplyBm
    src/math.h
    src/multiply.bm.cpp
    src/multiply.cpp
    src/multiply.h
)
target_link_libraries(multiplyBm benchmark_main util)


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
target_include_directories(mathTest PRIVATE
    ${CMAKE_SOURCE_DIR}/3rdparty/..
)
target_link_libraries(mathTest gtest_main util)


add_executable(prime-sieveTest
    src/prime-sieve.h
    src/prime-sieve.test.cpp
)
ul_add_test(prime-sieveTest)
target_link_libraries(prime-sieveTest gtest_main mb-util)


add_executable(prime-sieveBm
    src/prime-sieve.bm.cpp
    src/prime-sieve.h
)
target_link_libraries(prime-sieveBm benchmark_main mb-util)


ul_include(matplotlib-cpp.cmake)
add_executable(prime-graph
    src/prime-sieve.h
    src/prime-graph.cpp
)
target_include_directories(prime-graph PRIVATE ${matplotlib-cpp_INCLUDE_DIRS})
target_link_libraries(prime-graph matplotlib_cpp mb-util)


add_executable(prime-palindromes
    src/prime-sieve.h
    src/prime-palindromes.cpp
)
target_link_libraries(prime-palindromes mb-util)


add_executable(gcmTest
    src/gcm.h
    src/gcm.test.cpp
)
ul_add_test(gcmTest)
target_link_libraries(gcmTest gtest_main util)


add_executable(gcmBm
    src/gcm.bm.cpp
    src/gcm.h
)
target_link_libraries(gcmBm benchmark_main util)
