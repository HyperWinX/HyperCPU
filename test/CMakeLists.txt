set(TESTS_INCLUDE_DIR 
  ${HyperCPU_SOURCE_DIR}/src
  ${HyperCPU_SOURCE_DIR}/test)

add_executable(modular_testing ${SOURCES_modular_testing})
target_link_libraries(modular_testing core gtest_main gtest pthread)
target_include_directories(modular_testing PUBLIC ${TESTS_INCLUDE_DIR})
set_target_properties(modular_testing PROPERTIES COMPILE_FLAGS ${HCPU_COMPILE_FLAGS})

add_executable(integration_testing ${SOURCES_integration_testing})
target_link_libraries(integration_testing core gtest_main gtest pthread)
target_include_directories(integration_testing PUBLIC ${TESTS_INCLUDE_DIR})
set_target_properties(integration_testing PROPERTIES COMPILE_FLAGS ${HCPU_COMPILE_FLAGS})

if(HCPU_DEBUG_INFO_ENABLED)
  target_link_libraries(modular_testing -fsanitize=address,undefined -fno-sanitize-recover=all)
  target_link_libraries(integration_testing -fsanitize=address,undefined -fno-sanitize-recover=all)
endif()

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
