include(../cmake/Variables.cmake)

set(TESTS_INCLUDE_DIR 
  ${HyperCPU_SOURCE_DIR}/src
  ${HyperCPU_SOURCE_DIR}/test)

add_executable(modular_testing-noopt ${SOURCES_modular_testing})
target_link_libraries(modular_testing-noopt core gtest_main gtest pthread -fno-sanitize-recover=all -fsanitize=address,undefined)
target_include_directories(modular_testing-noopt PUBLIC ${TESTS_INCLUDE_DIR})
set_target_properties(modular_testing-noopt PROPERTIES COMPILE_FLAGS ${TESTING_COMPILE_FLAGS_NOOPT})

add_executable(modular_testing-allopt ${SOURCES_modular_testing})
target_link_libraries(modular_testing-allopt core gtest_main gtest pthread -fno-sanitize-recover=all -fsanitize=address,undefined)
target_include_directories(modular_testing-allopt PUBLIC ${TESTS_INCLUDE_DIR})
set_target_properties(modular_testing-allopt PROPERTIES COMPILE_FLAGS ${TESTING_COMPILE_FLAGS_ALLOPT})

add_executable(integration_testing-noopt ${SOURCES_integration_testing})
target_link_libraries(integration_testing-noopt core gtest_main gtest pthread -fno-sanitize-recover=all -fsanitize=address,undefined)
target_include_directories(integration_testing-noopt PUBLIC ${TESTS_INCLUDE_DIR})
set_target_properties(integration_testing-noopt PROPERTIES COMPILE_FLAGS ${TESTING_COMPILE_FLAGS_NOOPT})

add_executable(integration_testing-allopt ${SOURCES_integration_testing})
target_link_libraries(integration_testing-allopt core gtest_main gtest pthread -fno-sanitize-recover=all -fsanitize=address,undefined)
target_include_directories(integration_testing-allopt PUBLIC ${TESTS_INCLUDE_DIR})
set_target_properties(integration_testing-allopt PROPERTIES COMPILE_FLAGS ${TESTING_COMPILE_FLAGS_ALLOPT})

add_custom_target(run-all-tests-github
    ${CMAKE_BINARY_DIR}/modular_testing-noopt
  COMMAND
    ${CMAKE_BINARY_DIR}/modular_testing-allopt
  COMMAND
    ${CMAKE_BINARY_DIR}/modular_testing-noopt
  COMMAND
    ${CMAKE_BINARY_DIR}/modular_testing-allopt
  DEPENDS
    build-all-tests-github
)

add_custom_target(build-all-tests-github
  DEPENDS
    modular_testing-noopt
    modular_testing-allopt
    integration_testing-noopt
    integration_testing-allopt
)

add_custom_target(run-all-tests
    ${CMAKE_BINARY_DIR}/modular_testing-noopt
  COMMAND
    ${CMAKE_BINARY_DIR}/integration_testing-noopt
  DEPENDS
    modular_testing-noopt
    integration_testing-noopt
)

add_custom_target(build-all-tests
  DEPENDS
    modular_testing
    integration_testing
)
