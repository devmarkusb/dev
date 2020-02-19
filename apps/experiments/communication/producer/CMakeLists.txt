include(${tfl_CMAKE_DIRS}/cmake_util.cmake)

project(communication_producer LANGUAGES C CXX)
set(TargetAppName ${PROJECT_NAME})

too_include(defaults.cmake)

add_executable(${TargetAppName}
        src/main.cpp
)

too_set_target_pthread(${TargetAppName})

target_include_directories(${TargetAppName} PRIVATE
        ${lib_producer_api_INCLUDE_DIRS}
)

target_link_libraries(${TargetAppName} PRIVATE
        producer_api
)
