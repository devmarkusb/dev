if (TOO_BUILD_UNITTESTS)
    include(${TOO_CMAKE_INC_GOOGLETEST_AS_SUBDIR})
endif ()

add_subdirectory(tfl)
add_subdirectory(Toolib)
