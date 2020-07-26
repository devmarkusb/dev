project(elements-of-programming LANGUAGES CXX)
set(TargetAppName ${PROJECT_NAME})

add_executable(${TargetAppName}
        src/main.cpp
)

target_include_directories(${TargetAppName} PUBLIC ${lib_util_INCLUDE_DIRS})
target_include_directories(${TargetAppName} PUBLIC ${tfl_INCLUDE_DIRS})
