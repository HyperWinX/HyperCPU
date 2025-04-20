cmake_minimum_required(VERSION 3.25)

# pog
option(POG_BUNDLED_RE2 OFF CACHE BOOL "Use bundled re2" FORCE)
option(POG_BUNDLED_FMT OFF CACHE BOOL "Use bundled fmt" FORCE)
option(POG_TESTS OFF CACHE BOOL "Build tests" FORCE)
add_subdirectory(pog)

# hpool
add_subdirectory(HPool)