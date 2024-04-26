include_directories(${HyperCPU_SOURCE_DIR}/include)

file(GLOB_RECURSE ALL_SRCS ${HyperCPU_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM ALL_SRCS "${HyperCPU_SOURCE_DIR}/src/main.cpp")
set(CORE_SRCS ${ALL_SRCS})
set(CPU_SRCS ${ALL_SRCS})

set(TESTS_SRCS ${CORE_SRCS} ${HyperCPU_SOURCE_DIR}/test/tests.cpp)

add_executable(emulator ${CPU_SRCS})
set_target_properties(emulator PROPERTIES COMPILE_FLAGS "-Wall -Wextra -O2")

add_executable(tests ${TESTS_SRCS})
target_link_libraries(tests gtest_main gtest pthread)
add_custom_command(TARGET tests POST_BUILD COMMAND ${PROJECT_SOURCE_DIR}/build/tests && rm -f ${PROJECT_SOURCE_DIR}/build/tests)
set_target_properties(tests PROPERTIES COMPILE_FLAGS "-Wall -Wextra -Werror -std=c++23 -Wno-pointer-arith -g -O0")
