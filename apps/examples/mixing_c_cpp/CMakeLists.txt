project(mixing_c_cpp LANGUAGES C CXX)
set(target ${PROJECT_NAME})

######################################################################################################################

set(targetAsLibForTest ${PROJECT_NAME}AsLibForTest)
add_library(${targetAsLibForTest} STATIC
        src/tmp.c
        src/tmp.cpp
        src/tmp.h
)

target_include_directories(${targetAsLibForTest} PUBLIC ${lib_util_INCLUDE_DIRS})
target_include_directories(${targetAsLibForTest} PUBLIC ${ul_INCLUDE_DIRS})

ul_use_asio(${targetAsLibForTest} ${CMAKE_SOURCE_DIR}/3rdparty/asio-1.12.2.tar.gz
        MD5=43c53b8d255edc385dc4e704e59b3641)

ul_set_target_defaults(${targetAsLibForTest})


######################################################################################################################

add_executable(${target}
        src/main.cpp
)

target_link_libraries(${target} PRIVATE ${targetAsLibForTest})

ul_set_target_defaults(${target})
ul_set_target_openmp(${target})


######################################################################################################################

if (NOT UL_BUILD_UNITTESTS)
    return ()
endif ()

set(targetTest ${PROJECT_NAME}Test)

add_executable(${targetTest}
        src/tmp.test.cpp
)

target_link_libraries(${targetTest} PRIVATE gmock_main gtest ${targetAsLibForTest})

ul_set_target_defaults(${targetTest})
ul_set_target_openmp(${targetTest})

ul_run_target_postbuild(${targetTest})
