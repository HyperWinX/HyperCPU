# FIXME: Add separate precompiled headers here, too
cmake_minimum_required(VERSION 3.25)


include(GoogleTest)

add_subdirectory(Integration)
add_subdirectory(Modular)
add_subdirectory(Pog)
add_subdirectory(Python/Buildsystem)
