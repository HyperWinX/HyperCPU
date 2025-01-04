include(../cmake/Variables.cmake)

set(TESTS_INCLUDE_DIR 
  ${HyperCPU_SOURCE_DIR}/src/emulator
  ${HyperCPU_SOURCE_DIR}/test)

message(STATUS "Linking tests to ${GTEST_LINK_TARGET}")
add_executable(modular_testing ${HyperCPU_SOURCE_DIR}/test/main.cpp ${SOURCES_modular_testing})
target_link_libraries(modular_testing emulator-core gtest pthread)
target_include_directories(modular_testing PUBLIC ${TESTS_INCLUDE_DIR})
set_target_properties(modular_testing PROPERTIES COMPILE_FLAGS "${HCPU_COMPILE_FLAGS} -g")

add_executable(integration_testing ${HyperCPU_SOURCE_DIR}/test/main.cpp ${SOURCES_integration_testing})
target_link_libraries(integration_testing emulator-core gtest pthread)
target_include_directories(integration_testing PUBLIC ${TESTS_INCLUDE_DIR})
set_target_properties(integration_testing PROPERTIES COMPILE_FLAGS ${HCPU_COMPILE_FLAGS})

add_custom_target(run-all-tests-github
    ${CMAKE_BINARY_DIR}/modular_testing
  COMMAND
    ${CMAKE_BINARY_DIR}/integration_testing
  DEPENDS
    build-all-tests-github
)

add_custom_target(build-all-tests-github
  DEPENDS
    modular_testing
    integration_testing
)

add_custom_target(run-all-tests
    ${CMAKE_BINARY_DIR}/modular_testing
  COMMAND
    ${CMAKE_BINARY_DIR}/integration_testing
  DEPENDS
    modular_testing
    integration_testing
)

add_custom_target(build-all-tests
  DEPENDS
    modular_testing
    integration_testing
)
