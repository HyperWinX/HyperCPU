#include <core/cpu/instructions/registers.hpp>
#include <core/cpu/instructions/flags.hpp>

#include <fixtures.hpp>


TEST_F(cpu_test, INSTR_LOIVT_R_b64) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::LOIVT);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b64 << 6 | hypercpu::operand_types::R);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::X1);
  cpu.mem_controller->load16(*cpu.xip + 4, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 6, hypercpu::operand_types::NONE);
  *cpu.x1 = 2048;

  cpu.run();

  ASSERT_EQ(*cpu.xivt, 2048);
}
