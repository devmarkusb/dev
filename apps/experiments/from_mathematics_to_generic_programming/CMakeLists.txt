project(from_mathematics_to_generic_programming)

add_executable(multiplyBm
    src/multiply.bm.cpp
    src/multiply.cpp
    src/multiply.h
)

target_include_directories(multiplyBm PRIVATE ${ul_INCLUDE_DIRS})

target_link_libraries(multiplyBm benchmark::benchmark)