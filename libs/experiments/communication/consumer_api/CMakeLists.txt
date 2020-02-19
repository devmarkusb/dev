include(${tfl_CMAKE_DIRS}/cmake_util.cmake)

project(consumer_api LANGUAGES C CXX)
set(TargetLibName ${PROJECT_NAME})

file(GLOB_RECURSE TargetToolib_INCS "include/*.h*")
file(GLOB_RECURSE TargetToolib_SRC_INCS "src/*.h*")

set(TargetLibName_SOURCES
        src/consumer.cpp
)

add_library(${TargetLibName} SHARED
        ${TargetLibName_SOURCES}
        ${TargetLibName_INCS}
        ${TargetLibName_SRC_INCS}
)

target_include_directories(${TargetLibName} PRIVATE
        include
)

set(lib_${TargetLibName}_INCLUDE_DIRS
        ${CMAKE_CURRENT_LIST_DIR}/include
        CACHE INTERNAL "" FORCE)
