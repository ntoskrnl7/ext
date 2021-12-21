cmake_minimum_required(VERSION 3.10)

include(../cmake/CPM.cmake)

if (NOT DEFINED CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE "Debug")
  message("CMAKE_BUILD_TYPE (default) : " ${CMAKE_BUILD_TYPE})
else()
  message("CMAKE_BUILD_TYPE : " ${CMAKE_BUILD_TYPE})
endif()

project(unittest LANGUAGES C CXX)

CPMAddPackage(NAME ext SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

if (MSVC_VERSION LESS_EQUAL 1700)
  if (MSVC_VERSION GREATER_EQUAL 1600)
    add_definitions(-DGTEST_HAS_TR1_TUPLE=0)
  endif()
  CPMAddPackage(
    NAME googletest
    GITHUB_REPOSITORY google/googletest
    GIT_TAG release-1.7.0
    VERSION 1.7.0
    OPTIONS "INSTALL_GTEST OFF" "gtest_force_shared_crt"
  )
  include_directories("${gtest_SOURCE_DIR}/include")
else()
  CPMAddPackage(
    NAME googletest
    GITHUB_REPOSITORY google/googletest
    GIT_TAG release-1.10.0
    VERSION 1.10.0
    OPTIONS "INSTALL_GTEST OFF" "gtest_force_shared_crt"
  )
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(gtest INTERFACE -Wno-deprecated-copy)
    target_compile_options(gtest_main INTERFACE -Wno-deprecated-copy)
endif()

file(GLOB SOURCE_FILES ./*.cpp)

add_executable(unittest ${SOURCE_FILES} ${PLATFORMS_SOURCE_FILES})
target_link_libraries(unittest ext gtest gtest_main)

if (CXX_USE_BOOST)
  add_definitions(-DCXX_USE_BOOST)
  find_package(Boost 1.69.0 REQUIRED COMPONENTS thread system chrono)
  include_directories(${Boost_INCLUDE_DIRS})
  target_link_directories(unittest PRIVATE ${Boost_LIBRARY_DIRS})
endif()

get_property(CXX_STANDARD_SPECIFIED TARGET unittest PROPERTY CXX_STANDARD SET)
if (CXX_STANDARD_SPECIFIED)
  get_property(CXX_STANDARD_VAR TARGET unittest PROPERTY CXX_STANDARD)
  message("CXX_STANDARD : " ${CXX_STANDARD_VAR})
else()
  set_property(TARGET unittest PROPERTY CXX_STANDARD 17)
  get_property(CXX_STANDARD_VAR TARGET unittest PROPERTY CXX_STANDARD)
  message("CXX_STANDARD (default): " ${CXX_STANDARD_VAR})
endif()
set_property(TARGET unittest PROPERTY CXX_STANDARD_REQUIRED ON)

if (WIN32)
elseif(APPLE)
elseif(UNIX)
  target_link_libraries(unittest rt)
endif()

enable_testing()

# macOS의 경우 LC_ALL=C으로 테스트가 실행되어 문자열 변환이 안되는 현상이 있습니다.
# 그래서 테스트를 실행할때 LC_ALL을 en_US.UTF-8로 지정하여 문자열 변환이 잘되도록 처리했습니다.
if (APPLE)
  add_test(NAME unittest COMMAND ${CMAKE_COMMAND} -E env LC_ALL=en_US.UTF-8 ${CMAKE_BINARY_DIR}/unittest)
else()
  add_test(NAME unittest COMMAND unittest)
endif()