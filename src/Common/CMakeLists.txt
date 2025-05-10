cmake_minimum_required(VERSION 3.22)


add_library(
    hcpu::common
    INTERFACE
        Defs.hpp
        NotImplemented.hpp
        LanguageSpec/AllowedFlags.hpp
        LanguageSpec/Flags.hpp
        LanguageSpec/Opcodes.hpp
        LanguageSpec/Registers.hpp
)

target_include_directories(hcpu::common INTERFACE ${CMAKE_SOURCE_DIR})

target_link_libraries(hcpu::Common INTERFACE spdlog::spdlog hcpu::pch)
