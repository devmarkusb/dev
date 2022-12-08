include(${ul_CMAKE_DIRS}/cmake_util.cmake)

project(communication_processor)
set(TargetAppName ${PROJECT_NAME})

ul_include(defaults.cmake)

add_executable(${TargetAppName}
        src/main.cpp
)

ul_set_target_pthread(${TargetAppName})

target_include_directories(${TargetAppName} PRIVATE
        ${lib_consumer_api_INCLUDE_DIRS}
        ${lib_producer_api_INCLUDE_DIRS}
)

target_link_libraries(${TargetAppName} PRIVATE
        consumer_api
        producer_api
)
