project(communication_allinone)
set(target ${PROJECT_NAME})

add_executable(${target} src/alternative.h src/application.h src/main.cpp)

mb_ul_include(asio.cmake)
mb_ul_use_asio(${target} ${CMAKE_SOURCE_DIR}/3rdparty/asio-1.12.2.tar.gz
        MD5=43c53b8d255edc385dc4e704e59b3641
)

mb_devenv_set_target_pthread(${target})
mb_devenv_set_target_defaults(${target})

target_include_directories(
    ${target}
    PRIVATE ${lib_consumer_api_INCLUDE_DIRS} ${lib_producer_api_INCLUDE_DIRS}
)

target_link_libraries(${target} PRIVATE consumer_api producer_api util)
