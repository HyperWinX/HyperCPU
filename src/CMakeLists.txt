set(GENERIC_INCLUDE_DIR 
  ${HyperCPU_SOURCE_DIR}/src)

add_library(emulator-core STATIC ${SOURCES_core})
target_include_directories(emulator-core PUBLIC ${GENERIC_INCLUDE_DIR} ${HyperCPU_SOURCE_DIR}/src/emulator)
set_target_properties(emulator-core PROPERTIES COMPILE_FLAGS ${HCPU_COMPILE_FLAGS})
target_link_libraries(emulator-core ${LD_FLAGS})

add_executable(emulator ${SOURCES_emulator-main})
target_include_directories(emulator PUBLIC ${GENERIC_INCLUDE_DIR})
set_target_properties(emulator PROPERTIES COMPILE_FLAGS ${HCPU_COMPILE_FLAGS})
