if (TOO_BUILD_UNITTESTS)
    include(${TOO_CMAKE_INC_GOOGLETEST_AS_SUBDIR})
endif ()

add_subdirectory(tfl/basiccodesupport)
add_subdirectory(tfl/linklib)
add_subdirectory(tfl/mem)
add_subdirectory(tfl/string)

add_subdirectory(Toolib)
