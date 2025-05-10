cmake_minimum_required(VERSION 3.22)

add_library(hcpu::pch INTERFACE CStd.hpp)
target_precompile_headers(hcpu::pch INTERFACE CStd.hpp)
