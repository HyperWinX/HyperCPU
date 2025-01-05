set(GENERIC_INCLUDE_DIR 
  ${HyperCPU_SOURCE_DIR}/src
  ${HyperCPU_SOURCE_DIR}/dist/argparse/include
  ${HyperCPU_SOURCE_DIR}/dist/pog/include)

add_library(emulator-core STATIC ${SOURCES_emulator-core})
target_include_directories(emulator-core PUBLIC ${GENERIC_INCLUDE_DIR} ${HyperCPU_SOURCE_DIR}/src/emulator)
set_target_properties(emulator-core PROPERTIES COMPILE_FLAGS ${HCPU_COMPILE_FLAGS})
target_link_libraries(emulator-core ${LD_FLAGS})

add_library(assembler-core STATIC ${SOURCES_assembler-core})
target_include_directories(assembler-core PUBLIC ${GENERIC_INCLUDE_DIR} ${HyperCPU_SOURCE_DIR}/src/assembler)
target_link_libraries(assembler-core pog)

add_executable(emulator ${SOURCES_emulator-main})
target_include_directories(emulator PUBLIC ${GENERIC_INCLUDE_DIR})
set_target_properties(emulator PROPERTIES COMPILE_FLAGS ${HCPU_COMPILE_FLAGS})

add_executable(hcasm ${SOURCES_assembler-main})
target_include_directories(hcasm PUBLIC ${GENERIC_INCLUDE_DIR} ${HyperCPU_SOURCE_DIR}/src/assembler)
target_link_libraries(hcasm assembler-core pog)
set_target_properties(hcasm PROPERTIES COMPILE_FLAGS ${HCPU_COMPILE_FLAGS})