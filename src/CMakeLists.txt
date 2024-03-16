include_directories(${HyperCPU_SOURCE_DIR}/include)

set(CORE_SRCS cpu.cpp
              opcode_handler.cpp
              instructions.cpp)

set(CPU_SRCS ${CORE_SRCS} main.cpp)

set(TESTS_SRCS ${CORE_SRCS} ../test/tests.cpp)

add_executable(emulator ${CPU_SRCS})
set_target_properties(emulator PROPERTIES COMPILE_FLAGS "-Wall -Werror -O2")

add_executable(tests ${TESTS_SRCS})
target_link_libraries(tests gtest_main gtest pthread)
add_custom_command(TARGET tests POST_BUILD COMMAND ${PROJECT_SOURCE_DIR}/build/tests && rm -f ${PROJECT_SOURCE_DIR}/build/tests)
set_target_properties(tests PROPERTIES COMPILE_FLAGS "-Wall -Werror -std=c++23 -g -Og")
