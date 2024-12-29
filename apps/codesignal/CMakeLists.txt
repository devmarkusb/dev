project(codesignal)

add_executable(hierarchies_count
        hierarchies_count.cpp
)
target_link_libraries(hierarchies_count util)

add_executable(tree_diameter
        tree_diameter.cpp
        )
target_link_libraries(tree_diameter util)
