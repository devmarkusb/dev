if (TOO_BUILD_UNITTESTS)
    too_include(googletest_as_subdir.cmake)
endif ()

add_subdirectory(tfl)
add_subdirectory(toolib)
