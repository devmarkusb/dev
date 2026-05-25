project(tmp LANGUAGES C CXX) # CUDA)
set(target ${PROJECT_NAME})

mb_ul_include(asio.cmake)
mb_ul_include(gperftools.cmake)

######################################################################################################################

set(targetAsLibForTest ${PROJECT_NAME}AsLibForTest)
add_library(${targetAsLibForTest} STATIC src/cuda/tmp.cu src/tmp.cpp src/tmp.h)

target_link_libraries(${targetAsLibForTest} PUBLIC mb::toolib util)

mb_ul_use_asio(${targetAsLibForTest} ${CMAKE_SOURCE_DIR}/3rdparty/asio-1.12.2.tar.gz
        MD5=43c53b8d255edc385dc4e704e59b3641
)

mb_devenv_set_target_defaults(${targetAsLibForTest})

######################################################################################################################

add_executable(${target} src/main.cpp)

target_link_libraries(${target} PRIVATE ${targetAsLibForTest})

mb_devenv_set_target_defaults(${target})
#mb_devenv_set_target_cuda_separable_compilation(${target})

mb_ul_use_gperftools(${target} ${CMAKE_SOURCE_DIR}/3rdparty/gperftools-2.6.3.tar.gz)

######################################################################################################################

if(NOT MB_DEV_BUILD_TESTS)
    return()
endif()

set(targetTest ${PROJECT_NAME}-test)

add_executable(${targetTest} src/tmp.test.cpp)

target_link_libraries(
    ${targetTest}
    PRIVATE GTest::gmock_main GTest::gtest ${targetAsLibForTest}
)

mb_devenv_set_target_defaults(${targetTest})
mb_devenv_add_simple_test(${targetTest})
