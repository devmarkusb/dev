include(${tfl_CMAKE_DIRS}/cmake_util.cmake)

project(threads_n_cachelines LANGUAGES C CXX)
set(TargetAppName ${PROJECT_NAME})

too_include(defaults.cmake)

add_executable(${TargetAppName}
        src/main.cpp
)

too_set_target_pthread(${TargetAppName})
