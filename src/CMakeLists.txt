include_directories(${HyperCPU_SOURCE_DIR}/include)

file(GLOB_RECURSE ALL_SRCS ${HyperCPU_SOURCE_DIR}/src/*.cpp)
string(REPLACE ${HyperCPU_SOURCE_DIR}/src/main.cpp "" CORE_SRCS ${ALL_SRCS})

set(CPU_SRCS ${ALL_SRCS})

set(TESTS_SRCS ${CORE_SRCS} ${HyperCPU_SOURCE_DIR}/tests/tests.cpp)

message(STATUS "all srcs: ${ALL_SRCS}")
message(STATUS "core srcs: ${CORE_SRCS}")
message(STATUS "tests srcs: ${TESTS_SRCS}")

add_custom_target(
    copy-compile-commands ALL
    ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_CURRENT_LIST_DIR}
    )

add_executable(emulator ${CPU_SRCS})
set_target_properties(emulator PROPERTIES COMPILE_FLAGS "-Wall -Wextra -O2")

add_executable(tests ${TESTS_SRCS})
target_link_libraries(tests gtest_main gtest pthread)
add_custom_command(TARGET tests POST_BUILD COMMAND ${PROJECT_SOURCE_DIR}/build/tests && rm -f ${PROJECT_SOURCE_DIR}/build/tests)
set_target_properties(tests PROPERTIES COMPILE_FLAGS "-Wall -Wextra -std=c++23 -Wno-pointer-arith -g -O0")
