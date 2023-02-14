project(from_mathematics_to_generic_programming)

add_executable(multiplyBm
    src/multiply.bm.cpp
    src/multiply.cpp
    src/multiply.h
)

target_include_directories(multiplyBm PRIVATE ${ul_INCLUDE_DIRS})
target_link_libraries(multiplyBm benchmark::benchmark benchmark::benchmark_main)

add_executable(primeSieveTest
        src/prime-sieve.h
        src/prime-sieve.test.cpp
        )
ul_add_test(primeSieveTest)
target_include_directories(primeSieveTest PRIVATE ${ul_INCLUDE_DIRS})
target_link_libraries(primeSieveTest gtest_main)


add_executable(primeSieveBm
        src/prime-sieve.bm.cpp
        src/prime-sieve.h
        )

target_include_directories(primeSieveBm PRIVATE ${ul_INCLUDE_DIRS})
target_link_libraries(primeSieveBm benchmark::benchmark benchmark::benchmark_main)
