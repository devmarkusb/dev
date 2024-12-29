project(util)

set(target ${PROJECT_NAME})

file(GLOB_RECURSE target_INCS "include/*.h")

add_library(${target} INTERFACE ${target_INCS})

target_link_libraries(${target} INTERFACE mb-util)

set(${target}_INCLUDE_DIRS
        ${CMAKE_CURRENT_LIST_DIR}/include
        CACHE INTERNAL "" FORCE)

target_include_directories(${target} INTERFACE ${${target}_INCLUDE_DIRS})
