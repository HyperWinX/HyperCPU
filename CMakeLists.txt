cmake_minimum_required(VERSION 3.25)

project(HyperCPU CXX)

option(HCPU_LTO "HCPU: Enable LTO if possible" OFF)
option(HCPU_NATIVE_OPTIMIZATIONS "HCPU: Optimize for current ISA implementation" OFF)
option(HCPU_SANITIZERS "HCPU: Enable sanitizers" OFF)
option(HCPU_BUILD_TESTS "HCPU: Build tests" ON)
option(HCPU_BUILD_BENCHMARKS "HCPU: Build benchmarks" OFF)

# FIXME: add pthread, boost & re2
find_package(GTest 1.14.0 REQUIRED)         # GoogleTest
find_package(benchmark 1.9.1 REQUIRED)      # Google Benchmark
find_package(absl 20250127.0 REQUIRED)      # Abseil (CMake target: absl::absl)
find_package(libbacktrace CONFIG REQUIRED)  # libbacktrace (CMake target: libbacktrace::libbacktrace)
find_package(argparse 3.2 REQUIRED)         # argparse.cpp (CMake target: argparse::argparse)
find_package(eternal 1.0.1 REQUIRED)        # Eternal (CMake target: eternal::eternal)
# find_package(RE2 20240702 REQUIRED)         # RE2 (CMake target: re2::re2)
find_package(fmt 11.1.4 REQUIRED)           # fmtlib (CMake target: fmt::fmt)
find_package(libunwind 1.8.1 REQUIRED)      # libunwind (CMake target: libunwind::libunwind)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# FIXME: remove later
# retained for backwards comparability, should be supplied in CLI or presets
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# FIXME: do we need this now?
# Disable gtest requirement for google/benchmark
set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
# Fix -Wstrinop-overflow warning
set(FMT_SYSTEM_HEADER ON) 

# FIXME: patch hpool to enable -Werror
add_compile_options(
    -Wall
    -Wextra
    # -Werror
    -Wno-pointer-arith
    -Wno-unused-const-variable
    -Wno-missing-field-initializers
    -Wno-stringop-overflow
)

add_compile_options(
    $<$<CONFIG:Debug>:-ggdb3>
    $<$<CONFIG:Debug>:-D__HCPU_DEBUG>
    $<$<CONFIG:Release>:-O3>
)

# FIXME: enable this by default when this becomes operational
if(HCPU_LTO)
    check_ipo_supported(RESULT result OUTPUT output)
    if(result)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
        message(STATUS "HCPU: Enabled lTO")
    else()
        message(WARNING "HCPU: LTO is not supported: ${output}")
    endif()
else()
    message(STATUS "HCPU: Skipping LTO")
endif()

if(HCPU_NATIVE_OPTIMIZATIONS)
    add_compile_options(-march=native)
    message(STATUS "HCPU: Enabled optimizations for current ISA implementation")
else()
    message(STATUS "HCPU: Skipping current ISA optimizations")
endif()

if(HCPU_SANITIZERS)
    add_compile_options(-fsanitize=address,leak)
    add_link_options(-fsanitize=address,leak)
    message(STATUS "HCPU: Enabling sanitizers")
else()
    message(STATUS "HCPU: Skipping sanitizers")
endif()

add_library(hcpu_unwind INTERFACE)
target_link_libraries(
    hcpu_unwind
    INTERFACE
        libunwind::libunwind libbacktrace::libbacktrace
)
target_compile_definitions(
    hcpu_unwind
    INTERFACE
        HCPU_ENABLE_LIBUNWIND
)

add_subdirectory(dist)
add_subdirectory(src)

if(HCPU_BUILD_BENCHMARKS)
    add_subdirectory(bench)
endif()

if(HCPU_BUILD_TESTS)
    # FIXME: rename to tests
    add_subdirectory(test)
endif()