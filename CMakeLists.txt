cmake_minimum_required(VERSION 3.28)
project(HyperCPU CXX C)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(ROOT_DIR ${HyperCPU_SOURCE_DIR})

message(STATUS "Generating source files list")
include(cmake/SourceListGenerator.cmake)

add_subdirectory(dist/googletest)
add_subdirectory(bench)
add_subdirectory(src)
add_subdirectory(test)
