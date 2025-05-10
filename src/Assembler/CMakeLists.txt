cmake_minimum_required(VERSION 3.22)

add_library(
    hcpu::assembler-core
    STATIC
        Core/StatementCompilers.cpp
        Core/Parsers.cpp
        Core/Tokenizers.cpp
        Core/Compiler.cpp
        Core/BinaryTransformer.cpp
        Utils/Extension.hpp
        Core/BinaryTransformer.hpp
        Core/OpcodeNameAssoc.hpp
        Core/RegNameAssoc.hpp
        Core/Compiler.hpp
        Core/ModeNameAssoc.hpp
)

target_include_directories(hcpu::assembler-core PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(
    hcpu::assembler-core
    PUBLIC
        fmt::fmt
        argparse::argparse
        eternal::eternal
        re2::re2
        pch
        pog
        hpool
)

add_executable(hcasm Main/Main.cpp)

target_link_libraries(hcasm PRIVATE hcpu::assembler-core)
