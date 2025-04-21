#include <Core/CPU/Instructions/Registers.hpp>
#include <Core/CPU/Instructions/Flags.hpp>

#include <fixtures.hpp>


TEST_F(CPU_TEST, INSTR_INTR_R_b64) {
  // Setup stack
  *cpu.xbp = 512;
  *cpu.xsp = 512;
  // Setup IVT
  cpu.mem_controller->Load64(2048, 1536); // First IVT entry
  cpu.mem_controller->Load16(1536, HyperCPU::Opcode::HALT); // Code for interrupt handler
  cpu.mem_controller->Load16(1538, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::LOIVT);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b64 << 4 | HyperCPU::OperandTypes::R);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::X0);
  cpu.mem_controller->Load16(*cpu.xip + 4, HyperCPU::Opcode::INTR);
  cpu.mem_controller->Load8(*cpu.xip + 6, HyperCPU::Mode::b64 << 4 | HyperCPU::OperandTypes::R);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::Registers::X1);
  *cpu.x0 = 2048;
  *cpu.x1 = 0;

  cpu.Run();

  ASSERT_EQ(*cpu.xip, 1539);
}
