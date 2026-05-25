project(consumer_api)
set(TargetLibName ${PROJECT_NAME})

file(GLOB_RECURSE TargetLibName_INCS "include/*.h*")
file(GLOB_RECURSE TargetLibName_SRC_INCS "src/*.h*")

set(TargetLibName_SOURCES src/consumer.cpp)

add_library(
    ${TargetLibName}
    SHARED
    ${TargetLibName_SOURCES}
    ${TargetLibName_INCS}
    ${TargetLibName_SRC_INCS}
)

target_include_directories(${TargetLibName} PUBLIC include)

mb_devenv_set_target_defaults(${TargetLibName})

set(lib_${TargetLibName}_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}/include
    CACHE INTERNAL
    ""
    FORCE
)
