project(variant_cycle)
set(target ${PROJECT_NAME})

add_executable(${target}
        src/main.cpp
        src/type_a.h
        src/type_a_decl.h
        src/type_b.h
        src/variant.h
        src/variant_decl.h
)

target_link_libraries(${target} util)
