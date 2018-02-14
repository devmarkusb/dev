cmake_minimum_required(VERSION 3.4.1)

add_subdirectory(sdks/ToolsFL/tooBuildEnv)
include(${TOO_CMAKE_INC_BUILDNR})
project(performance_clean_sheet VERSION 0.1.${BUILD_NR}.0)
message(STATUS "project version: " ${PROJECT_VERSION})
set(TargetAppName ${PROJECT_NAME})

include(${TOO_CMAKE_INC_DEFAULTS})

add_subdirectory(sdks)


######################################################################################################################

set(TargetAppNameAsLibForTest ${PROJECT_NAME}AsLibForTest)
add_library(${TargetAppNameAsLibForTest} STATIC
        src/threads_n_cachelines.cpp
        src/tooperf_demo.cpp
        src/tooperf_demo.h
        src/util/random.h
        src/source.cpp
        src/source.h
        src/source.c)

target_include_directories(${TargetAppNameAsLibForTest} PUBLIC src)
target_include_directories(${TargetAppNameAsLibForTest} PUBLIC ${tooBasicCodeSupport_INCLUDE_DIRS})
target_include_directories(${TargetAppNameAsLibForTest} PUBLIC ${tooString_INCLUDE_DIRS})
target_include_directories(${TargetAppNameAsLibForTest} PUBLIC ${Toolib_INCLUDE_DIRS})
target_include_directories(${TargetAppNameAsLibForTest} SYSTEM PUBLIC ${Boost_INCLUDE_DIRS})

target_link_libraries(${TargetAppNameAsLibForTest} PUBLIC Toolib)
if (LINUX)
    target_link_libraries(${TargetAppNameAsLibForTest} PUBLIC pthread)
endif ()

if (NOT TOO_DEPLOYMENT_BUILD AND NOT WIN32)
    add_dependencies(${TargetAppNameAsLibForTest} gperftools)
    target_include_directories(${TargetAppNameAsLibForTest} PRIVATE ${gperftools_profiler_INCLUDE})
    target_link_libraries(${TargetAppNameAsLibForTest} PRIVATE gperftools_profiler)
endif ()


######################################################################################################################

add_executable(${TargetAppName}
        src/main.cpp
        )

target_link_libraries(${TargetAppName} PRIVATE ${TargetAppNameAsLibForTest})

if (WIN32)
    set_property(TARGET ${TargetAppName} APPEND PROPERTY COMPILE_DEFINITIONS UNICODE _UNICODE)
endif ()

set_target_properties(${TargetAppName} PROPERTIES DEBUG_POSTFIX "d")


######################################################################################################################

if (NOT TOO_BUILD_UNITTESTS)
    return ()
endif ()

set(TargetAppNameTest ${PROJECT_NAME}Test)
add_executable(${TargetAppNameTest}
        src/source.test.cpp)

if (WIN32)
    set_property(TARGET ${TargetAppNameTest} APPEND PROPERTY COMPILE_DEFINITIONS UNICODE _UNICODE)
endif ()

set_target_properties(${TargetAppNameTest} PROPERTIES DEBUG_POSTFIX "d")

target_link_libraries(${TargetAppNameTest} PRIVATE gmock_main gtest ${TargetAppNameAsLibForTest})

set(do_auto_test    ON)

if (do_auto_test)
    add_custom_command(
            TARGET ${TargetAppNameTest} POST_BUILD
            COMMAND ${TargetAppNameTest}
    )
endif ()
