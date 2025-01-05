#include <core/cpu/instructions/registers.hpp>
#include <core/cpu/instructions/flags.hpp>

#include <fixtures.hpp>


TEST_F(cpu_test, INSTR_INTR_R_b64) {
  // Setup stack
  *cpu.xbp = 512;
  *cpu.xsp = 512;
  // Setup IVT
  cpu.mem_controller->load64(2048, 1536); // First IVT entry
  cpu.mem_controller->load16(1536, hypercpu::opcode::HALT); // Code for interrupt handler
  cpu.mem_controller->load16(1538, hypercpu::operand_types::NONE);
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::LOIVT);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b64 << 6 | hypercpu::operand_types::R);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::X0);
  cpu.mem_controller->load16(*cpu.xip + 4, hypercpu::opcode::INTR);
  cpu.mem_controller->load8(*cpu.xip + 6, hypercpu::mode::b64 << 6 | hypercpu::operand_types::R);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::registers::X1);
  *cpu.x0 = 2048;
  *cpu.x1 = 0;

  cpu.run();

  ASSERT_EQ(*cpu.xip, 1539);
}
