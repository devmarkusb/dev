project(tmp LANGUAGES C CXX)# CUDA)
set(TargetAppName ${PROJECT_NAME})

too_include(asio.cmake)
too_include(gperftools.cmake)
too_include(openmp.cmake)

######################################################################################################################

set(TargetAppNameAsLibForTest ${PROJECT_NAME}AsLibForTest)
add_library(${TargetAppNameAsLibForTest} STATIC
        src/cuda/tmp.cu
        src/tmp.c
        src/tmp.cpp
        src/tmp.h
)

target_include_directories(${TargetAppNameAsLibForTest} PUBLIC ${lib_util_INCLUDE_DIRS})
target_include_directories(${TargetAppNameAsLibForTest} PUBLIC ${tfl_INCLUDE_DIRS})
target_include_directories(${TargetAppNameAsLibForTest} PUBLIC ${toolib_INCLUDE_DIRS})

target_link_libraries(${TargetAppNameAsLibForTest} PUBLIC toolib)

too_use_asio(${TargetAppNameAsLibForTest} ${CMAKE_SOURCE_DIR}/3rdparty/asio-1.12.2.tar.gz
        MD5=43c53b8d255edc385dc4e704e59b3641)

too_set_target_defaults(${TargetAppNameAsLibForTest})


######################################################################################################################

add_executable(${TargetAppName}
        src/main.cpp
)

target_link_libraries(${TargetAppName} PRIVATE ${TargetAppNameAsLibForTest})

too_set_target_defaults(${TargetAppName})
too_set_target_openmp(${TargetAppName})
#too_set_target_cuda_separable_compilation(${TargetAppName})

too_use_gperftools(${TargetAppName} ${CMAKE_SOURCE_DIR}/3rdparty/gperftools-2.6.3.tar.gz)


######################################################################################################################

if (NOT TOO_BUILD_UNITTESTS)
    return ()
endif ()

set(TargetAppNameTest ${PROJECT_NAME}Test)

add_executable(${TargetAppNameTest}
        src/tmp.test.cpp
)

target_link_libraries(${TargetAppNameTest} PRIVATE gmock_main gtest ${TargetAppNameAsLibForTest})

too_set_target_defaults(${TargetAppNameTest})
too_set_target_openmp(${TargetAppNameTest})

too_run_target_postbuild(${TargetAppNameTest})
