project(views_coro-alt)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${lib_util_INCLUDE_DIRS})
