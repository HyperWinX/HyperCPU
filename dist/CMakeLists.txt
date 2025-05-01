cmake_minimum_required(VERSION 3.25)

# hpool
set(HPOOL_BUILD_TESTS OFF CACHE BOOL "Whether to include test target into configuration" FORCE)
set(HPOOL_BUILD_BENCHMARKS OFF CACHE BOOL "Whether to include benchmark target into configuration" FORCE)
add_subdirectory(HPool)