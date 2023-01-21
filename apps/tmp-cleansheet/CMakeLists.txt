project(tmp-cleansheet LANGUAGES CXX)
set(target ${PROJECT_NAME})

add_executable(${target}
        src/main.cpp
)

target_include_directories(${target} PUBLIC ${lib_util_INCLUDE_DIRS})
target_include_directories(${target} PUBLIC ${ul_INCLUDE_DIRS})

ul_include(asio.cmake)
ul_use_asio(${target} ${CMAKE_SOURCE_DIR}/3rdparty/asio-1.12.2.tar.gz
        MD5=43c53b8d255edc385dc4e704e59b3641)
