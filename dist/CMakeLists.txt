cmake_minimum_required(VERSION 3.25)

# pog
set(POG_BUNDLED_RE2 OFF CACHE BOOL "Use bundled re2" FORCE)
set(POG_BUNDLED_FMT OFF CACHE BOOL "Use bundled fmt" FORCE)
set(POG_TESTS OFF CACHE BOOL "Build tests" FORCE)
add_subdirectory(pog)

# hpool
set(HPOOL_BUILD_TESTS OFF CACHE BOOL "Whether to include test target into configuration" FORCE)
set(HPOOL_BUILD_BENCHMARKS OFF CACHE BOOL "Whether to include benchmark target into configuration" FORCE)
add_subdirectory(HPool)