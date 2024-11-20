file(GLOB_RECURSE CORE_SRCS ${HyperCPU_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE TEST_SRCS ${HyperCPU_SOURCE_DIR}/test/*.cpp)
list(REMOVE_ITEM ALL_SRCS "${HyperCPU_SOURCE_DIR}/src/main.cpp")


set(TESTS_SRCS ${CORE_SRCS} ${TEST_SRCS})

set(FAST_COMPILE_FLAGS "-Wall -Wextra -Wno-pointer-arith -O3 -Wno-unused-const-variable")
set(DEBUG_COMPILE_FLAGS "-Wall -Wextra -Werror -Wno-pointer-arith -O0 -ggdb3 -Wno-unused-const-variable -fno-sanitize-recover=all -fsanitize=address,undefined")

set(TESTS_INCLUDE_DIR 
  ${HyperCPU_SOURCE_DIR}/src
  ${HyperCPU_SOURCE_DIR}/test)

add_executable(modular_testing ${SOURCES_modular_testing})
target_link_libraries(modular_testing gtest_main gtest pthread)
target_include_directories(modular_testing PUBLIC ${TESTS_INCLUDE_DIR})
set_target_properties(modular_testing PROPERTIES COMPILE_FLAGS ${FAST_COMPILE_FLAGS})

add_executable(integration_testing ${SOURCES_modular_testing})
target_link_libraries(integration_testing gtest_main gtest pthread)
target_include_directories(integration_testing PUBLIC ${TESTS_INCLUDE_DIR})
set_target_properties(integration_testing PROPERTIES COMPILE_FLAGS ${FAST_COMPILE_FLAGS})

add_custom_target(all-tests 
    ${CMAKE_BINARY_DIR}/modular_testing
  COMMAND
    ${CMAKE_BINARY_DIR}/integration_testing
  DEPENDS
    modular_testing
    integration_testing
)
