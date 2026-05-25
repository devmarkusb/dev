project(modules)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API
    "aa1f7df0-828a-4fcd-9afc-2dc80491aca7"
)

mb_ul_include(cli11.cmake)

add_executable(modules)
target_sources(modules PUBLIC src/main.cpp)
target_sources(
    modules
    PUBLIC FILE_SET modules TYPE CXX_MODULES FILES src/m1.cpp src/m2.cpp
)
target_link_libraries(modules PRIVATE CLI11::CLI11 mb::util)
mb_devenv_set_target_defaults(modules)
