project(tooperf_demo LANGUAGES C CXX)
set(TargetAppName ${PROJECT_NAME})

add_executable(${TargetAppName}
        src/main.cpp
)

target_include_directories(${TargetAppName} PUBLIC ${lib_util_INCLUDE_DIRS})
target_include_directories(${TargetAppName} PUBLIC ${tfl_INCLUDE_DIRS})
target_include_directories(${TargetAppName} PUBLIC ${toolib_INCLUDE_DIRS})

target_link_libraries(${TargetAppName} PUBLIC toolib)
