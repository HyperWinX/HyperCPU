include_directories(${HyperCPU_SOURCE_DIR}/include)

file(GLOB_RECURSE CORE_SRCS ${HyperCPU_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE TEST_SRCS ${HyperCPU_SOURCE_DIR}/test/*.cpp)
list(REMOVE_ITEM ALL_SRCS "${HyperCPU_SOURCE_DIR}/src/main.cpp")
set(TESTS_SRCS ${CORE_SRCS} ${TEST_SRCS})


add_executable(tests ${TESTS_SRCS})
target_link_libraries(tests gtest_main gtest pthread)
set_target_properties(tests PROPERTIES COMPILE_FLAGS "-Wall -std=c++23 -Wno-strict-aliasing -Wno-pointer-arith -O2")
add_custom_command(TARGET tests COMMAND POST_BUILD strip -s ${PROJECT_SOURCE_DIR}/build/tests)
add_custom_command(TARGET tests POST_BUILD COMMAND ${PROJECT_SOURCE_DIR}/build/tests && rm -f ${PROJECT_SOURCE_DIR}/build/tests)

add_executable(tests-debug ${TESTS_SRCS})
target_link_libraries(tests-debug gtest_main gtest pthread -fsanitize=address)
set_target_properties(tests-debug PROPERTIES COMPILE_FLAGS "-Wall -Wextra -Werror -std=c++23 -Wno-pointer-arith -O0 -ggdb3")