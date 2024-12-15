#include <core/cpu/instructions/registers.hpp>
#include <core/cpu/instructions/flags.hpp>

#include <fixtures.hpp>


TEST_F(cpu_test, INSTR_CALL_R) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::CALL);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::operand_types::R);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XLLL0);
  cpu.mem_controller->load16(1536, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(1538, hypercpu::operand_types::NONE);
  *cpu.xbp = 512;
  *cpu.xsp = *cpu.xbp;
  *cpu.x0 = 1536;

  cpu.run();

  ASSERT_EQ(*cpu.xip, 1539);
}

TEST_F(cpu_test, INSTR_CALL_M) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::CALL);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::operand_types::M);
  cpu.mem_controller->load64(*cpu.xip + 3, 1536);
  cpu.mem_controller->load16(1536, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(1538, hypercpu::operand_types::NONE);
  *cpu.xbp = 512;
  *cpu.xsp = *cpu.xbp;

  cpu.run();

  ASSERT_EQ(*cpu.xip, 1539);
}
