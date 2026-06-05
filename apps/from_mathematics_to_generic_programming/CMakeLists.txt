project(from_mathematics_to_generic_programming)

mb_ul_include(googlebenchmark.cmake)

add_executable(
    multiplyBm
    src/math.h
    src/multiply.bm.cpp
    src/multiply.cpp
    src/multiply.h
)
target_link_libraries(multiplyBm benchmark_main util)

if(MB_DEV_BUILD_TESTS)
    add_executable(
        mathTest
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
    mb_devenv_add_simple_test(mathTest)
    add_library(bigint_3rdparty INTERFACE)
    target_include_directories(
        bigint_3rdparty
        SYSTEM
        INTERFACE ${CMAKE_SOURCE_DIR}/3rdparty
    )
    target_link_libraries(mathTest GTest::gtest_main util bigint_3rdparty)

    add_executable(prime-sieveTest src/prime-sieve.h src/prime-sieve.test.cpp)
    mb_devenv_add_simple_test(prime-sieveTest)
    target_link_libraries(prime-sieveTest GTest::gtest_main mb::util)
endif()

add_executable(prime-sieveBm src/prime-sieve.bm.cpp src/prime-sieve.h)
target_link_libraries(prime-sieveBm benchmark_main mb::util)

mb_ul_include(matplotlib-cpp.cmake)
add_executable(prime-graph src/prime-sieve.h src/prime-graph.cpp)
target_link_libraries(prime-graph matplotlib_cpp mb::util)

add_executable(prime-palindromes src/prime-sieve.h src/prime-palindromes.cpp)
target_link_libraries(prime-palindromes mb::util)

if(MB_DEV_BUILD_TESTS)
    add_executable(gcmTest src/gcm.h src/gcm.test.cpp)
    mb_devenv_add_simple_test(gcmTest)
    target_link_libraries(gcmTest GTest::gtest_main util)
endif()

add_executable(gcmBm src/gcm.bm.cpp src/gcm.h)
target_link_libraries(gcmBm benchmark_main util)
