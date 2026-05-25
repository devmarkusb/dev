project(communication_consumer)
set(target ${PROJECT_NAME})

add_executable(${target} src/main.cpp)

mb_devenv_set_target_pthread(${target})
mb_devenv_set_target_defaults(${target})

target_include_directories(${target} PRIVATE ${lib_consumer_api_INCLUDE_DIRS})

target_link_libraries(${target} PRIVATE consumer_api)
