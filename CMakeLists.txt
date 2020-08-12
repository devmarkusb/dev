cmake_minimum_required(VERSION 3.4.1)

project(dev LANGUAGES C CXX)

add_subdirectory(sdks)
add_subdirectory(3rdparty)

add_subdirectory(libs)
add_subdirectory(apps)

too_include(githooks.cmake)
too_include(clang-format.cmake)
