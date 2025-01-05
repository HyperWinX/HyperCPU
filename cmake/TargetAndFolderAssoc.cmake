set(__TARGETS_LIST
# HyperCPU core sources
  emulator-core
  emulator-main

  assembler-core
  assembler-main


# Testing
  modular_testing
  integration_testing
)

set(__DIRECTORIES_LIST
# emulator-core target
  ${ROOT_DIR}/src/emulator/core

# emulator-main target
  ${ROOT_DIR}/src/emulator/main

# assembler-core target
  ${ROOT_DIR}/src/assembler/core

# assembler-main target
  ${ROOT_DIR}/src/assembler/main

# modulartesting_src target
  ${ROOT_DIR}/test/modular

# integrationtesting_src
  ${ROOT_DIR}/test/integration
)
