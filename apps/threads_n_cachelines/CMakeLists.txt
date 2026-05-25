project(threads_n_cachelines)
set(target ${PROJECT_NAME})

add_executable(${target} src/main.cpp)

mb_devenv_set_target_pthread(${target})
mb_devenv_set_target_defaults(${target})
