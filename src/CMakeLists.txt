set(GENERIC_INCLUDE_DIR 
  ${HyperCPU_SOURCE_DIR}/src
  ${HyperCPU_SOURCE_DIR}/dist/argparse/include
  ${HyperCPU_SOURCE_DIR}/dist/pog/include
  ${HyperCPU_SOURCE_DIR}/dist/eternal/include
  ${HyperCPU_SOURCE_DIR}/dist/HPool)

get_property(HCPU_CXX_FLAGS GLOBAL PROPERTY HCPU_CXX_FLAGS)
get_property(HCPU_LINK_FLAGS GLOBAL PROPERTY HCPU_LINK_FLAGS)

add_library(emulator-core STATIC ${SOURCES_emulator-core})
target_compile_options(emulator-core PUBLIC "${HCPU_CXX_FLAGS}")
target_include_directories(emulator-core PUBLIC ${GENERIC_INCLUDE_DIR} ${HyperCPU_SOURCE_DIR}/src/Emulator)
target_link_libraries(emulator-core ${LD_FLAGS} fmt ${HCPU_LINK_FLAGS})

add_library(assembler-core STATIC ${SOURCES_assembler-core})
target_compile_options(assembler-core PUBLIC "${HCPU_CXX_FLAGS}")
target_include_directories(assembler-core PUBLIC ${GENERIC_INCLUDE_DIR} ${HyperCPU_SOURCE_DIR}/src/Assembler)
target_link_libraries(assembler-core pog ${HCPU_LINK_FLAGS})

add_executable(hcasm ${SOURCES_assembler-main})
target_compile_options(hcasm PUBLIC "${HCPU_CXX_FLAGS}")
target_include_directories(hcasm PUBLIC ${GENERIC_INCLUDE_DIR} ${HyperCPU_SOURCE_DIR}/src/Assembler)
target_link_libraries(hcasm assembler-core pog ${HCPU_LINK_FLAGS})

add_executable(hcemul ${SOURCES_emulator-main})
target_compile_options(hcemul PUBLIC "${HCPU_CXX_FLAGS}")
target_include_directories(hcemul PUBLIC ${GENERIC_INCLUDE_DIR} ${HyperCPU_SOURCE_DIR}/src/Emulator)
target_link_libraries(hcemul emulator-core assembler-core ${HCPU_LINK_FLAGS})

add_custom_target(default
  DEPENDS
    hcasm
    hcemul
)
