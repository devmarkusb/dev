project(variant_cycle LANGUAGES CXX)
set(TargetAppName ${PROJECT_NAME})

add_executable(${TargetAppName}
        src/main.cpp
        src/type_a.h
        src/type_a_decl.h
        src/type_b.h
        src/variant.h
        src/variant_decl.h
)

target_include_directories(${TargetAppName} PUBLIC ${lib_util_INCLUDE_DIRS})
target_include_directories(${TargetAppName} PUBLIC ${ul_INCLUDE_DIRS})
