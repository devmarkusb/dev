cmake_minimum_required(VERSION 3.4.1)

add_subdirectory(sdks/ToolsFL/tooBuildEnv)
include(${TOO_CMAKE_INC_BUILDNR})
project(performance_clean_sheet VERSION 0.1.${BUILD_NR}.0)
message(STATUS "project version: " ${PROJECT_VERSION})
set(TargetAppName ${PROJECT_NAME})

include(${TOO_CMAKE_INC_DEFAULTS})

add_subdirectory(sdks)

add_executable(${TargetAppName}
    src/threads_n_cachelines.cpp
    src/main.cpp
)

target_include_directories(${TargetAppName} PUBLIC src)
target_include_directories(${TargetAppName} PUBLIC ${tooBasicCodeSupport_INCLUDE_DIRS})
target_include_directories(${TargetAppName} PUBLIC ${tooString_INCLUDE_DIRS})
target_include_directories(${TargetAppName} PUBLIC ${Toolib_INCLUDE_DIRS})
target_include_directories(${TargetAppName} SYSTEM PUBLIC ${Boost_INCLUDE_DIRS})

if (WIN32)
    set_property(TARGET ${TargetAppName} APPEND PROPERTY COMPILE_DEFINITIONS UNICODE _UNICODE)
endif ()

set_target_properties(${TargetAppName} PROPERTIES DEBUG_POSTFIX "d")

target_link_libraries(${TargetAppName} PUBLIC Toolib)
