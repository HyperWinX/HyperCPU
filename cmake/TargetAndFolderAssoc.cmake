set(__TARGETS_LIST
# HyperCPU core sources
  emulator-core
  emulator-main

  assembler-core
  assembler-main

  backtrace-provider


# Testing
  modular_testing
  integration_testing
)

set(__DIRECTORIES_LIST
# emulator-core target
  ${ROOT_DIR}/src/Emulator/Core

# emulator-main target
  ${ROOT_DIR}/src/Emulator/Main

# assembler-core target
  ${ROOT_DIR}/src/Assembler/Core

# assembler-main target
  ${ROOT_DIR}/src/Assembler/Main

# backtrace-provider target
  ${ROOT_DIR}/src/BacktraceProvider

# modulartesting_src target
  ${ROOT_DIR}/test/Modular

# integrationtesting_src
  ${ROOT_DIR}/test/Integration
)
