project(codesignal LANGUAGES CXX)

add_executable(hierarchies_count
        hierarchies_count.cpp
)

target_include_directories(hierarchies_count PUBLIC ${lib_util_INCLUDE_DIRS})
