project(mixing_c_cpp LANGUAGES C CXX)
set(target ${PROJECT_NAME})

######################################################################################################################

set(targetAsLibForTest ${PROJECT_NAME}AsLibForTest)
add_library(${targetAsLibForTest} STATIC src/tmp.c src/tmp.cpp src/tmp.h)

target_link_libraries(${targetAsLibForTest} util)

mb_ul_include(asio.cmake)
mb_ul_use_asio(${targetAsLibForTest} ${CMAKE_SOURCE_DIR}/3rdparty/asio-1.12.2.tar.gz
        MD5=43c53b8d255edc385dc4e704e59b3641
)

mb_devenv_set_target_defaults(${targetAsLibForTest})

######################################################################################################################

add_executable(${target} src/main.cpp)

target_link_libraries(${target} PRIVATE ${targetAsLibForTest})

mb_devenv_set_target_defaults(${target})

######################################################################################################################

if(NOT MB_DEV_BUILD_TESTS)
    return()
endif()

set(targetTest ${PROJECT_NAME}-test)

mb_devenv_add_test(${targetTest} PRIVATE GTest::gmock ${targetAsLibForTest})
