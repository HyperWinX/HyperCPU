set(FAST_COMPILE_FLAGS "-Wall -Wextra -Wno-pointer-arith -O3 -Wno-unused-const-variable")
set(DEBUG_COMPILE_FLAGS "-Wall -Wextra -Werror -Wno-pointer-arith -O0 -ggdb3 -Wno-unused-const-variable -fno-sanitize-recover=all -fsanitize=address,undefined")

set(GENERIC_INCLUDE_DIR 
  ${HyperCPU_SOURCE_DIR}/src)

add_library(core STATIC ${SOURCES_core})
target_include_directories(core PUBLIC ${GENERIC_INCLUDE_DIR})
set_target_properties(core PROPERTIES COMPILE_FLAGS ${HCPU_COMPILE_FLAGS})

add_executable(emulator ${SOURCES_main})
target_include_directories(emulator PUBLIC ${GENERIC_INCLUDE_DIR})
set_target_properties(emulator PROPERTIES COMPILE_FLAGS ${HCPU_COMPILE_FLAGS})
