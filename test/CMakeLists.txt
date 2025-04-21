# TODO: Enable CTest integration
# FIXME: Add separate precompiled headers here, too
cmake_minimum_required(VERSION 3.25)


add_subdirectory(Integration)
add_subdirectory(Modular)

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
