include(${tfl_CMAKE_DIRS}/cmake_util.cmake)
too_include(defaults.cmake)

if (TOO_BUILD_UNITTESTS)
    too_include(googletest_as_subdir.cmake)
endif ()
