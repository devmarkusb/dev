ul_include(buildnr.cmake)
project(cmake_util_test VERSION 0.42.${BUILD_NR}.0 LANGUAGES C CXX)
message(STATUS "cmake_util_test project version: " ${PROJECT_VERSION})
set(TargetAppName ${PROJECT_NAME})

add_executable(${TargetAppName}
        src/main.cpp
)
