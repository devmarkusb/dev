include(${ul_CMAKE_DIRS}/cmake_util.cmake)

project(threads_n_cachelines)
set(target ${PROJECT_NAME})

ul_include(defaults.cmake)

add_executable(${target}
        src/main.cpp
)

ul_set_target_pthread(${target})
