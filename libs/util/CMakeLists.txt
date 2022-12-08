project(util)

set(target ${PROJECT_NAME})

file(GLOB_RECURSE target_INCS "include/*.h")

add_library(${target} INTERFACE ${target_INCS})

target_include_directories(${target} INTERFACE ${ul_INCLUDE_DIRS})

get_target_property(interfaceInclDirs ${target} INTERFACE_INCLUDE_DIRECTORIES)

set(lib_util_INCLUDE_DIRS
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${interfaceInclDirs}
        CACHE INTERNAL "" FORCE)
