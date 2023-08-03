include(${ul_CMAKE_DIRS}/cmake_util.cmake)
ul_include(defaults.cmake)

add_subdirectory(cli11)
add_subdirectory(cmake_util_test)
add_subdirectory(codesignal)
add_subdirectory(communication)
add_subdirectory(elements_of_programming)
add_subdirectory(from_mathematics_to_generic_programming)
add_subdirectory(mixing_c_cpp)
add_subdirectory(perf_demo)
add_subdirectory(programming_principles_practice)
add_subdirectory(threads_n_cachelines)
add_subdirectory(variant_cycle)
add_subdirectory(views_coro-alt)

# clean sheets
add_subdirectory(tmp)
add_subdirectory(tmp-cleansheet)
