include(../cmake/Variables.cmake)

set(TESTS_INCLUDE_DIR 
  ${HyperCPU_SOURCE_DIR}/dist/eternal/include
  ${HyperCPU_SOURCE_DIR}/src/Emulator
  ${HyperCPU_SOURCE_DIR}/test)

add_executable(modular_testing ${HyperCPU_SOURCE_DIR}/test/main.cpp ${SOURCES_modular_testing})
target_link_libraries(modular_testing emulator-core assembler-core gtest pthread)
target_include_directories(modular_testing PUBLIC ${TESTS_INCLUDE_DIR})

add_executable(integration_testing ${HyperCPU_SOURCE_DIR}/test/main.cpp ${SOURCES_integration_testing})
target_link_libraries(integration_testing emulator-core assembler-core gtest pthread)
target_include_directories(integration_testing PUBLIC ${TESTS_INCLUDE_DIR})

add_custom_target(run-all-tests-github
    ${CMAKE_BINARY_DIR}/modular_testing --gtest_brief=1
  COMMAND
    ${CMAKE_BINARY_DIR}/integration_testing --gtest_brief=1
  DEPENDS
    build-all-tests-github
)

add_custom_target(build-all-tests-github
  DEPENDS
    modular_testing
    integration_testing
)
