cmake_minimum_required(VERSION 3.10)

project(dev LANGUAGES C CXX)

add_subdirectory(sdks)
add_subdirectory(3rdparty)

add_subdirectory(libs)
add_subdirectory(apps)

too_include(githooks.cmake)
too_include(clang-format.cmake)
too_include(clang-tidy.cmake)
too_include(cppcheck.cmake)
