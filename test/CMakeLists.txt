include(../cmake/Variables.cmake)

set(TESTS_INCLUDE_DIR 
  ${HyperCPU_SOURCE_DIR}/src
  ${HyperCPU_SOURCE_DIR}/test)

find_package(GTest REQUIRED)

add_executable(modular_testing-noopt ${HyperCPU_SOURCE_DIR}/test/main.cpp ${SOURCES_modular_testing})
target_link_libraries(modular_testing-noopt core GTest::gtest pthread)
target_include_directories(modular_testing-noopt PUBLIC ${TESTS_INCLUDE_DIR})
set_target_properties(modular_testing-noopt PROPERTIES COMPILE_FLAGS ${NOOPT_COMPILE_FLAGS})

add_executable(modular_testing-allopt ${HyperCPU_SOURCE_DIR}/test/main.cpp ${SOURCES_modular_testing})
target_link_libraries(modular_testing-allopt core-fast GTest::gtest pthread)
target_include_directories(modular_testing-allopt PUBLIC ${TESTS_INCLUDE_DIR})
set_target_properties(modular_testing-allopt PROPERTIES COMPILE_FLAGS ${FAST_COMPILE_FLAGS})

add_executable(integration_testing-noopt ${HyperCPU_SOURCE_DIR}/test/main.cpp ${SOURCES_integration_testing})
target_link_libraries(integration_testing-noopt core GTest::gtest pthread)
target_include_directories(integration_testing-noopt PUBLIC ${TESTS_INCLUDE_DIR})
set_target_properties(integration_testing-noopt PROPERTIES COMPILE_FLAGS ${NOOPT_COMPILE_FLAGS})

add_executable(integration_testing-allopt ${HyperCPU_SOURCE_DIR}/test/main.cpp ${SOURCES_integration_testing})
target_link_libraries(integration_testing-allopt core-fast GTest::gtest pthread)
target_include_directories(integration_testing-allopt PUBLIC ${TESTS_INCLUDE_DIR})
set_target_properties(integration_testing-allopt PROPERTIES COMPILE_FLAGS ${FAST_COMPILE_FLAGS})

if (${HCPU_SANITIZERS_ENABLED})
  link_libraries(-fsanitize=address,leak,undefined)
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_link_libraries(integration_testing-noopt -flto=thin)
  target_link_libraries(modular_testing-noopt -flto=thin)
  message(STATUS "Clang detected: enabled -flto=thin")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GCC")
  target_link_libraries(integration_testing-noopt -flto)
  target_link_libraries(modular_testing-noopt -flto)
endif()

add_custom_target(run-all-tests-github
    ${CMAKE_BINARY_DIR}/modular_testing-noopt
  COMMAND
    ${CMAKE_BINARY_DIR}/integration_testing-noopt
  COMMAND
    ${CMAKE_BINARY_DIR}/modular_testing-allopt
  COMMAND
    ${CMAKE_BINARY_DIR}/integration_testing-allopt
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
