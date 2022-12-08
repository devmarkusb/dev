project(mixing_c_cpp LANGUAGES C CXX)
set(TargetAppName ${PROJECT_NAME})

######################################################################################################################

set(TargetAppNameAsLibForTest ${PROJECT_NAME}AsLibForTest)
add_library(${TargetAppNameAsLibForTest} STATIC
        src/tmp.c
        src/tmp.cpp
        src/tmp.h
)

target_include_directories(${TargetAppNameAsLibForTest} PUBLIC ${lib_util_INCLUDE_DIRS})
target_include_directories(${TargetAppNameAsLibForTest} PUBLIC ${ul_INCLUDE_DIRS})
target_include_directories(${TargetAppNameAsLibForTest} PUBLIC ${toolib_INCLUDE_DIRS})

target_link_libraries(${TargetAppNameAsLibForTest} PUBLIC toolib)

ul_use_asio(${TargetAppNameAsLibForTest} ${CMAKE_SOURCE_DIR}/3rdparty/asio-1.12.2.tar.gz
        MD5=43c53b8d255edc385dc4e704e59b3641)

ul_set_target_defaults(${TargetAppNameAsLibForTest})


######################################################################################################################

add_executable(${TargetAppName}
        src/main.cpp
)

target_link_libraries(${TargetAppName} PRIVATE ${TargetAppNameAsLibForTest})

ul_set_target_defaults(${TargetAppName})
ul_set_target_openmp(${TargetAppName})


######################################################################################################################

if (NOT UL_BUILD_UNITTESTS)
    return ()
endif ()

set(TargetAppNameTest ${PROJECT_NAME}Test)

add_executable(${TargetAppNameTest}
        src/tmp.test.cpp
)

target_link_libraries(${TargetAppNameTest} PRIVATE gmock_main gtest ${TargetAppNameAsLibForTest})

ul_set_target_defaults(${TargetAppNameTest})
ul_set_target_openmp(${TargetAppNameTest})

ul_run_target_postbuild(${TargetAppNameTest})
