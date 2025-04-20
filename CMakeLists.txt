cmake_minimum_required(VERSION 3.25)

include(cmake/Configuration.cmake)
detect_compilers()

project(HyperCPU CXX)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(ROOT_DIR ${HyperCPU_SOURCE_DIR})
set(BENCHMARK_ENABLE_GTEST_TESTS OFF) # Disable gtest requirement for google/benchmark
set(FMT_SYSTEM_HEADER ON) # Fix -Wstrinop-overflow warning

set_compile_flags()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

message(STATUS "Generating source files list")
include(cmake/SourceListGenerator.cmake)
add_subdirectory(dist/argparse)
add_subdirectory(dist/pog)
add_subdirectory(bench)
add_subdirectory(src)
add_subdirectory(test)
