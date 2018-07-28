cmake_minimum_required(VERSION 3.4.1)

include(sdks/tfl/buildenv/cmake_util.cmake)
too_include(buildnr.cmake)

project(performance_clean_sheet VERSION 0.1.${BUILD_NR}.0 LANGUAGES C CXX)# CUDA)
message(STATUS "project version: " ${PROJECT_VERSION})
set(TargetAppName ${PROJECT_NAME})

too_include(defaults.cmake)

too_include(openmp.cmake)
too_include(gperftools.cmake)

add_subdirectory(sdks)


######################################################################################################################

set(TargetAppNameAsLibForTest ${PROJECT_NAME}AsLibForTest)
add_library(${TargetAppNameAsLibForTest} STATIC
        src/cuda/cleansheet.cu
        src/source.c
        src/source.cpp
        src/source.h
        src/threads_n_cachelines.cpp
        src/tooperf_demo.cpp
        src/tooperf_demo.h
        src/util/profiler.cpp
        src/util/profiler.h
        src/util/random.cpp
        src/util/random.h
)

target_include_directories(${TargetAppNameAsLibForTest} PUBLIC src)
target_include_directories(${TargetAppNameAsLibForTest} PUBLIC ${tfl_INCLUDE_DIRS})
target_include_directories(${TargetAppNameAsLibForTest} PUBLIC ${toolib_INCLUDE_DIRS})
target_include_directories(${TargetAppNameAsLibForTest} SYSTEM PUBLIC ${Boost_INCLUDE_DIRS})

target_link_libraries(${TargetAppNameAsLibForTest} PUBLIC toolib)

too_set_target_defaults(${TargetAppNameAsLibForTest})


######################################################################################################################

add_executable(${TargetAppName}
        src/main.cpp
)

target_link_libraries(${TargetAppName} PRIVATE ${TargetAppNameAsLibForTest})

too_set_target_defaults(${TargetAppName})
too_set_target_openmp(${TargetAppName})
#too_set_target_cuda_separable_compilation(${TargetAppName})

too_use_gperftools(${TargetAppName} ${CMAKE_SOURCE_DIR}/sdks/gperftools-2.6.3.tar.gz)


######################################################################################################################

if (NOT TOO_BUILD_UNITTESTS)
    return ()
endif ()

set(TargetAppNameTest ${PROJECT_NAME}Test)

add_executable(${TargetAppNameTest}
        src/source.test.cpp)

target_link_libraries(${TargetAppNameTest} PRIVATE gmock_main gtest ${TargetAppNameAsLibForTest})

too_set_target_defaults(${TargetAppNameTest})
too_set_target_openmp(${TargetAppNameTest})

too_run_target_postbuild(${TargetAppNameTest})
