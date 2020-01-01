project(threads_n_cachelines LANGUAGES C CXX)
set(TargetAppName ${PROJECT_NAME})

add_executable(${TargetAppName}
        src/main.cpp
)

too_set_target_pthread(${TargetAppName})
