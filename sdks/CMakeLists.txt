if (TOO_BUILD_UNITTESTS)
    include(${TOO_CMAKE_INC_GOOGLETEST_AS_SUBDIR})
endif ()

add_subdirectory(ToolsFL/tooBasicCodeSupport)
add_subdirectory(ToolsFL/tooLinklib)
add_subdirectory(ToolsFL/tooMem)
add_subdirectory(ToolsFL/tooString)

add_subdirectory(Toolib)
