cmake_minimum_required(VERSION 3.10)

project(dev)

add_subdirectory(sdks)
add_subdirectory(3rdparty)

ul_include(googlebenchmark.cmake)

add_subdirectory(libs)
add_subdirectory(apps)

ul_include(clang-format.cmake)
ul_include(githooks.cmake)

set(UL_USE_DEFAULT_CLANG_TIDY_CONFIG ON)
set(UL_CLANG_TIDY_DIRS "libs")
ul_include(clang-tidy.cmake)
