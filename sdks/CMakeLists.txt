if (TOO_BUILD_UNITTESTS)
    include(${TOO_CMAKE_INC_GOOGLETEST_AS_SUBDIR})
endif ()

add_subdirectory(ToolsFL/tooBasicCodeSupport)
add_subdirectory(ToolsFL/tooLinklib)
add_subdirectory(ToolsFL/tooMem)
add_subdirectory(ToolsFL/tooString)

add_subdirectory(Toolib)

# Usage:
# 1) Add the following lines to the target that you want to profile:
#   if (NOT TOO_DEPLOYMENT_BUILD AND NOT WIN32)
#       add_dependencies(${TargetAppName} gperftools)
#       target_include_directories(${TargetAppName} PRIVATE ${gperftools_profiler_INCLUDE})
#       target_link_libraries(${TargetAppName} PRIVATE gperftools_profiler)
#   endif ()
# 2) Run the target with environment variable CPUPROFILE=result.prof (if that doesn't work in
# CLion, consult your psychologist, or find the right place for the var to actually work).
# Alternatively add the following to your code:
#   #if !TOO_DEPLOYMENT_BUILD && !TOO_OS_WINDOWS
#   #include "gperftools/profiler.h"
#   #endif
#   ...
#   #if !TOO_DEPLOYMENT_BUILD && !TOO_OS_WINDOWS
#       ProfilerStart("./app.prof");
#       auto autoStopProfiling = too::finally([](){ ProfilerStop(); });
#   #endif
# 3) Analyse results by
#   -changing dir to bin dir, where the binary and the prof file reside
#   -running
#       <path-to-pprof>/pprof --gv targetbinary app.prof
#       path-to-pprof could e.g. be builddir/sdks/gpertools/bin
if (NOT TOO_DEPLOYMENT_BUILD AND NOT WIN32)
    include(ExternalProject)
    set(gperftools_PREFIX ${CMAKE_BINARY_DIR}/sdks/gperftools)
    ExternalProject_Add(gperftools
            URL                ${CMAKE_CURRENT_LIST_DIR}/gperftools-2.6.3.tar.gz
            URL_MD5            D65C5E58931BE568AAC1621F2D8AD8D0
            SOURCE_DIR         ${gperftools_PREFIX}/src
            PREFIX             ${gperftools_PREFIX}
            STAMP_DIR          ${gperftools_PREFIX}/stamp
            BINARY_DIR         ${gperftools_PREFIX}/_build
            INSTALL_DIR        ${gperftools_PREFIX}
            CONFIGURE_COMMAND
            CC=${CMAKE_C_COMPILER} CXX=${CMAKE_CXX_COMPILER} CFLAGS=-g <SOURCE_DIR>/configure --prefix=<INSTALL_DIR> --enable-frame-pointers
            BUILD_COMMAND      make -j ${TOO_NPROC}
            INSTALL_COMMAND    make install
            )
    add_library(gperftools_profiler SHARED IMPORTED GLOBAL)
    set(gperftools_profiler_INCLUDE "${gperftools_PREFIX}/include")
    file(MAKE_DIRECTORY ${gperftools_profiler_INCLUDE}) # not there yet at generation time
    set_target_properties(gperftools_profiler PROPERTIES
            IMPORTED_LOCATION "${gperftools_PREFIX}/lib/libprofiler.so"
            INTERFACE_INCLUDE_DIRECTORIES ${gperftools_profiler_INCLUDE}
            )
endif()
