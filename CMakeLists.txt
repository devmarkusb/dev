# CMake project `mb.dev` -- options `MB_DEV_*`, shared tooling from `devenv/`.

cmake_minimum_required(VERSION 3.30...4.3)

project(
    mb.dev
    DESCRIPTION "personal development playground"
    LANGUAGES C CXX
    VERSION 0.1.0
)

option(
    MB_DEV_BUILD_TESTS
    "Enable building tests and test infrastructure. Default: ${PROJECT_IS_TOP_LEVEL}. Values: { ON, OFF }."
    ${PROJECT_IS_TOP_LEVEL}
)

list(PREPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/devenv/cmake")

if(MB_DEV_BUILD_TESTS)
    include(mb-devenv-ctest-root)
endif()
include(mb-devenv-defaults)
if(MB_DEV_BUILD_TESTS)
    include(mb-devenv-googletest)
endif()

include("${PROJECT_SOURCE_DIR}/sdks/util/cmake/cmake-util.cmake")

# From fetched https://github.com/devmarkusb/pre-commit (see fetchcontent-lockfile.json).
mb_pre_commit_setup()

set(MB_UTIL_BUILD_TESTS ${MB_DEV_BUILD_TESTS} CACHE BOOL "" FORCE)
set(MB_TOOLIB_BUILD_TESTS ${MB_DEV_BUILD_TESTS} CACHE BOOL "" FORCE)

add_subdirectory(sdks)
add_subdirectory(3rdparty)
add_subdirectory(libs)
add_subdirectory(apps)
