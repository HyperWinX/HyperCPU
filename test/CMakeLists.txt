file(GLOB_RECURSE CORE_SRCS ${HyperCPU_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE TEST_SRCS ${HyperCPU_SOURCE_DIR}/test/*.cpp)
list(REMOVE_ITEM ALL_SRCS "${HyperCPU_SOURCE_DIR}/src/main.cpp")
set(TESTS_SRCS ${CORE_SRCS} ${TEST_SRCS})

include_directories(${HyperCPU_SOURCE_DIR}/src)

add_executable(tests ${TESTS_SRCS})

add_executable(tests-debug ${TESTS_SRCS})
target_link_libraries(tests-debug gtest_main gtest pthread gcov)
set_target_properties(tests-debug PROPERTIES COMPILE_FLAGS "-Wall -Wextra -Werror -std=c++23 -Wno-pointer-arith -O0 -ggdb3")

add_test(NAME tests COMMAND tests)
add_test(NAME tests-debug COMMAND tests-debug)
