project(tmp-cleansheet)
set(target ${PROJECT_NAME})

add_executable(${target} src/main.cpp)

target_link_libraries(${target} util)

mb_ul_include(asio.cmake)
mb_ul_use_asio(${target} ${CMAKE_SOURCE_DIR}/3rdparty/asio-1.12.2.tar.gz
        MD5=43c53b8d255edc385dc4e704e59b3641
)
