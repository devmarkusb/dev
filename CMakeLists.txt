cmake_minimum_required(VERSION 3.10)

project(dev LANGUAGES C CXX)

add_subdirectory(sdks)
add_subdirectory(3rdparty)

add_subdirectory(libs)
add_subdirectory(apps)

ul_include(githooks.cmake)
ul_include(clang-format.cmake)
#ul_include(clang-tidy.cmake)
#ul_include(cppcheck.cmake)
