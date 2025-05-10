cmake_minimum_required(VERSION 3.22)

# hpool
set(HPOOL_BUILD_TESTS OFF CACHE BOOL "Whether to include test target into configuration" FORCE)
set(HPOOL_BUILD_BENCHMARKS OFF CACHE BOOL "Whether to include benchmark target into configuration" FORCE)
add_subdirectory(HPool)

add_library(dist::hpool ALIAS hpool)
