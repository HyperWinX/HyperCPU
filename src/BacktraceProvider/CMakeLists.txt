cmake_minimum_required(VERSION 3.25)

add_library(
    hcpu::backtrace-provider
    STATIC
        BacktraceProvider.cpp
        BacktraceProvider.hpp
)

target_include_directories(
    hcpu::backtrace-provider
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(
    hcpu::backtrace-provider
    PUBLIC
        fmt::fmt
        hcpu_unwind
        pch_cstd
)
