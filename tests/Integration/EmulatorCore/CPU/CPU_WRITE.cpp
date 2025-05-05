#include "Core/CPU/Instructions/Registers.hpp"
#include "pch.hpp"
#include <cstdint>
#include <fixtures.hpp>

TEST_F(CPU_TEST, INSTR_WRITE) {
  std::uint8_t t = 0;
  cpu.write_io_handlers[1] = [&t](std::uint8_t arg) -> void {
    std::cout << "hehe " << arg << '\n';
    t = arg;
  };

  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::WRITE);
  cpu.mem_controller->Load8(*cpu.xip + 2, (HyperCPU::Mode::b8 << 4) | HyperCPU::OperandTypes::R_IMM);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XLLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, 0x55);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = 1;

  cpu.Run();

  ASSERT_EQ(t, 0x55);
}
