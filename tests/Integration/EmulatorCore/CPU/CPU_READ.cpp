#include "Core/CPU/Instructions/Flags.hpp"
#include "pch.hpp"
#include <fixtures.hpp>

TEST_F(CPU_TEST, INSTR_READ) {
  cpu.read_io_handlers[1] = []() -> std::uint8_t {
    return 0x55;
  };

  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::READ);
  cpu.mem_controller->Load8(*cpu.xip + 2, (HyperCPU::Mode::b8 << 4) | HyperCPU::OperandTypes::IMM);
  cpu.mem_controller->Load8(*cpu.xip + 3, 1);
  cpu.mem_controller->Load16(*cpu.xip + 4, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 6, HyperCPU::OperandTypes::NONE);

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, 0x55);
}
