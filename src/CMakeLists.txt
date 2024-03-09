include_directories(${HyperCPU_SOURCE_DIR}/include)

set(CPU_SRCS cpu.cpp
             main.cpp
             opcode_handler.cpp)

add_executable(emulator ${CPU_SRCS})
set_target_properties(emulator PROPERTIES COMPILE_FLAGS "-Wall -Werror -O2")