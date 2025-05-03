add_library(
    pog
    INTERFACE
        # add other headers
        Pog/Pog.hpp
)

target_precompile_headers(pog INTERFACE Pog/Pog.hpp)

target_include_directories(pog INTERFACE ${CMAKE_SOURCE_DIR})
