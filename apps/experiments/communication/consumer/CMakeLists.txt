include(${ul_CMAKE_DIRS}/cmake_util.cmake)

project(communication_consumer)
set(target ${PROJECT_NAME})

ul_include(defaults.cmake)

add_executable(${target}
        src/main.cpp
)

ul_set_target_pthread(${target})

target_include_directories(${target} PRIVATE
        ${lib_consumer_api_INCLUDE_DIRS}
)

target_link_libraries(${target} PRIVATE
        consumer_api
)
