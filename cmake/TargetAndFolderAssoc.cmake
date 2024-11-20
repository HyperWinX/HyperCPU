set(__TARGETS_LIST
# HyperCPU core sources
  core
  main

# Testing
  modular_testing
  integration_testing
)

set(__DIRECTORIES_LIST
# core target
  ${ROOT_DIR}/src/core

# main target
  ${ROOT_DIR}/src/main

# modulartesting_src target
  ${ROOT_DIR}/test/modular

# integrationtesting_src
  ${ROOT_DIR}/test/integration
)
