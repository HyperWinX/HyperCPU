# TODO: refactor dependencies for each target, there is something useless there for sure
# TODO: refactor all includes relevant to CMAKE_SOURCE_DIR, like #include <src/some-header.hpp>

add_library(
    pch
    INTERFACE
        "pch.hpp"
)
target_precompile_headers(pch INTERFACE "pch.hpp")

add_library(
    pog
    INTERFACE
        Pog/Pog.hpp
)
target_precompile_headers(pog INTERFACE Pog/Pog.hpp)

target_include_directories(
    pog
    INTERFACE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/Pog
)

add_subdirectory(Emulator)
add_subdirectory(Assembler)
add_subdirectory(BacktraceProvider)
