file(GLOB_RECURSE CORE_SRCS ${HyperCPU_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE TEST_SRCS ${HyperCPU_SOURCE_DIR}/test/*.cpp)
list(REMOVE_ITEM ALL_SRCS "${HyperCPU_SOURCE_DIR}/src/main.cpp")
set(TESTS_SRCS ${CORE_SRCS} ${TEST_SRCS})

set(DEBUG_COMPILE_FLAGS "-std=c++23 -Wall -Wextra -Werror -std=c++23 -Wno-pointer-arith -O0 -ggdb3 -Wno-unused-const-variable -fno-sanitize-recover=all -fsanitize=address,undefined")

include_directories(${HyperCPU_SOURCE_DIR}/src)
include_directories(${HyperCPU_SOURCE_DIR}/test)

add_executable(tests ${TESTS_SRCS})
target_link_libraries(tests gtest_main gtest pthread gcov)
set_target_properties(tests PROPERTIES COMPILE_FLAGS "-std=c++23 -Wall -Wextra -std=c++23 -Wno-pointer-arith -O1 -ggdb3 -Wno-unused-const-variable")

add_executable(tests-debug ${TESTS_SRCS})
target_link_libraries(tests-debug gtest_main gtest pthread gcov -fno-sanitize-recover=all -fsanitize=address -fsanitize=undefined)
set_target_properties(tests-debug PROPERTIES COMPILE_FLAGS ${DEBUG_COMPILE_FLAGS})

add_test(NAME tests COMMAND tests)
add_test(NAME tests-debug COMMAND tests-debug)
