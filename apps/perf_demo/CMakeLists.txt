project(perf_demo)
set(target ${PROJECT_NAME})

add_executable(${target}
        src/main.cpp
)

target_link_libraries(${target} util)
