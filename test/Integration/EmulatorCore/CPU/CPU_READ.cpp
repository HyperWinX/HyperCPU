#include <fixtures.hpp>

TEST_F(CPU_TEST, INSTR_READ) {
  cpu.read_io_handlers[1] = []() -> std::uint8_t {
    return 0x55;
  };

  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::READ);
}