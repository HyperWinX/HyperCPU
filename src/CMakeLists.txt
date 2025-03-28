set(GENERIC_INCLUDE_DIR 
  ${HyperCPU_SOURCE_DIR}/src
  ${HyperCPU_SOURCE_DIR}/dist/argparse/include
  ${HyperCPU_SOURCE_DIR}/dist/pog/include
  ${HyperCPU_SOURCE_DIR}/dist/eternal/include
  ${HyperCPU_SOURCE_DIR}/dist/HPool)

add_library(emulator-core STATIC ${SOURCES_emulator-core})
target_include_directories(emulator-core PUBLIC ${GENERIC_INCLUDE_DIR} ${HyperCPU_SOURCE_DIR}/src/Emulator)
target_link_libraries(emulator-core ${LD_FLAGS} fmt)

add_library(assembler-core STATIC ${SOURCES_assembler-core})
target_include_directories(assembler-core PUBLIC ${GENERIC_INCLUDE_DIR} ${HyperCPU_SOURCE_DIR}/src/Assembler)
target_link_libraries(assembler-core pog)

add_executable(hcasm ${SOURCES_assembler-main})
target_include_directories(hcasm PUBLIC ${GENERIC_INCLUDE_DIR} ${HyperCPU_SOURCE_DIR}/src/Assembler)
target_link_libraries(hcasm assembler-core pog)

add_executable(hcemul ${SOURCES_emulator-main})
target_include_directories(hcemul PUBLIC ${GENERIC_INCLUDE_DIR} ${HyperCPU_SOURCE_DIR}/src/Emulator)
target_link_libraries(hcemul emulator-core assembler-core)

add_custom_target(default
  DEPENDS
    hcasm
    hcemul
)
