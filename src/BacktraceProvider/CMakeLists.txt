cmake_minimum_required(VERSION 3.25)


add_library(
    backtrace-provider
    STATIC
        BacktraceProvider.cpp
        BacktraceProvider.hpp
)
target_include_directories(
    backtrace-provider
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(
    backtrace-provider
    PUBLIC
        fmt::fmt
        argparse::argparse
        pog
        eternal::eternal
        hcpu_unwind
        pch
)