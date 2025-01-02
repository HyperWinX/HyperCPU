cmake_minimum_required(VERSION 3.28)
project(HyperCPU CXX C)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(ROOT_DIR ${HyperCPU_SOURCE_DIR})

include(cmake/Configuration.cmake)

set(HCPU_SANITIZERS_ENABLED ON)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
  message(STATUS "Configuring build with debug info")
  set_compile_flags(ON)
else()
  message(STATUS "Configuring release build")
  set_compile_flags(OFF)
endif()

if (${HCPU_SANITIZERS_ENABLED})
  message(STATUS "Enabling sanitizers")
  set(LD_FLAGS "${LD_FLAGS} -fsanitize=undefined,address,leak")
else()
  message(STATUS "Not enabling sanitizers")
endif()

string(STRIP ${LD_FLAGS} LD_FLAGS)

if (CMAKE_BUILD_TYPE STREQUAL Release)
  find_package(GTest REQUIRED)
  set(GTEST_LINK_TARGET "GTest::gtest")
else()
  set(GTEST_LINK_TARGET "gtest")
endif()

message(STATUS "Generating source files list")
include(cmake/SourceListGenerator.cmake)

add_subdirectory(dist/argparse)
add_subdirectory(dist/pog)
add_subdirectory(bench)
add_subdirectory(src)
add_subdirectory(test)
