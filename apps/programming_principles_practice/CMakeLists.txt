project(programming_principles_practice)
set(target ${PROJECT_NAME})

add_executable(${target}
        src/main.cpp
)

target_include_directories(${target} PUBLIC ${lib_util_INCLUDE_DIRS})
target_include_directories(${target} PUBLIC ${ul_INCLUDE_DIRS})
