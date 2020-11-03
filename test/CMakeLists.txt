cmake_minimum_required(VERSION 3.10)

project(unittest)

# gtest를 다운로드 받아서 빌드합니다.
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

include_directories("${gtest_SOURCE_DIR}/include")


#  포함 경로를 설정합니다.
if (WIN32)
  include_directories("../platforms/windows/")
elseif(APPLE)
  include_directories("../platforms/macos/")
elseif(UNIX)
  include_directories("../platforms/linux/")
endif()
include_directories("../include")


# 소스 파일을 설정합니다.
if (WIN32)
  file(GLOB PLATFORMS_SOURCE_FILES ./platforms/windows/*.cpp)
elseif(APPLE)
  file(GLOB PLATFORMS_SOURCE_FILES ./platforms/macos/*.cpp)
elseif(UNIX)
  file(GLOB PLATFORMS_SOURCE_FILES ./platforms/linux/*.cpp)
endif()
file(GLOB SOURCE_FILES ./*.cpp)


# 실행 파일 빌드 설정
add_executable(unittest ${SOURCE_FILES} ${PLATFORMS_SOURCE_FILES})
target_link_libraries(unittest gtest gtest_main)

if (CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
  message("CMAKE_BUILD_TYPE (default) : " ${CMAKE_BUILD_TYPE})
else()
  message("CMAKE_BUILD_TYPE : " ${CMAKE_BUILD_TYPE})
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

enable_testing()

# macOS의 경우 LC_ALL=C으로 테스트가 실행되어 문자열 변환이 안되는 현상이 있습니다.
# 그래서 테스트를 실행할때 LC_ALL을 en_US.UTF-8로 지정하여 문자열 변환이 잘되도록 처리했습니다.
if (APPLE)
  add_test(NAME unittest COMMAND ${CMAKE_COMMAND} -E env LC_ALL=en_US.UTF-8 ${CMAKE_BINARY_DIR}/unittest)
else()
  add_test(NAME unittest COMMAND unittest)
endif()