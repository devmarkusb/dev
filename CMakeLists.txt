cmake_minimum_required(VERSION 3.4.1)

include(sdks/tfl/buildenv/cmake_util.cmake)
too_include(buildnr.cmake)

project(dev VERSION 0.1.${BUILD_NR}.0 LANGUAGES C CXX)# CUDA)
message(STATUS "project version: " ${PROJECT_VERSION})
set(TargetAppName ${PROJECT_NAME})

too_include(defaults.cmake)

add_subdirectory(3rdparty)
add_subdirectory(sdks)

add_subdirectory(libs)
add_subdirectory(apps)
