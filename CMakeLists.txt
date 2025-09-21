cmake_minimum_required(VERSION 3.5)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
include(pkg-utils)
include(CPM)

pkg_get_version(EXT ${CMAKE_CURRENT_SOURCE_DIR}/include/ext/_version VERSION)

project(ext VERSION "${VERSION}" LANGUAGES C CXX)

option(EXT_BUILD_TESTS "Set to ON to build tests" OFF)
option(EXT_NO_WIN32_EX "Set to ON to exclude the win32-ex library" OFF)

add_library(ext INTERFACE)

target_include_directories(ext INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

if (WIN32 AND NOT EXT_NO_WIN32_EX)
    CPMAddPackage("gh:ntoskrnl7/win32-ex@0.8.12")
    target_link_libraries(ext INTERFACE win32ex)
endif()

if (EXT_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
