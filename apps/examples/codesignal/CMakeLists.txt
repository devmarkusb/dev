project(codesignal LANGUAGES CXX)

add_executable(hierarchies_count
        hierarchies_count.cpp
)

target_include_directories(hierarchies_count PUBLIC ${lib_util_INCLUDE_DIRS})

add_executable(tree_diameter
        tree_diameter.cpp
        )

target_include_directories(tree_diameter PUBLIC ${lib_util_INCLUDE_DIRS})
