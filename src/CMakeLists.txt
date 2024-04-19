include_directories(${HyperCPU_SOURCE_DIR}/include)

set(CORE_SRCS core/cpu.cpp
              core/opcode_handler.cpp
              core/instructions.cpp
              core/helpers/stack.cpp
              core/helpers/io_ops.cpp)

set(CPU_SRCS ${CORE_SRCS} main.cpp)

set(TESTS_SRCS ${CORE_SRCS} ../test/tests.cpp)

add_executable(emulator ${CPU_SRCS})
set_target_properties(emulator PROPERTIES COMPILE_FLAGS "-Wall -Wextra -O2")

add_executable(tests ${TESTS_SRCS})
target_link_libraries(tests gtest_main gtest pthread)
add_custom_command(TARGET tests POST_BUILD COMMAND ${PROJECT_SOURCE_DIR}/build/tests && rm -f ${PROJECT_SOURCE_DIR}/build/tests)
set_target_properties(tests PROPERTIES COMPILE_FLAGS "-Wall -Wextra -std=c++23 -Wno-pointer-arith -g -O0")
