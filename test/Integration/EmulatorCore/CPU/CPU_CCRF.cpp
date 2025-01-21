#include <Core/CPU/Instructions/Registers.hpp>
#include <Core/CPU/Instructions/Flags.hpp>

#include <fixtures.hpp>


TEST_F(cpu_test, INSTR_CCRF_SET) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::CCRF);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::operand_types::NONE);
  cpu.mem_controller->load16(*cpu.xip + 3, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 5, hypercpu::operand_types::NONE);
  cpu.crf = true;

  cpu.run();

  ASSERT_FALSE(cpu.crf);
}

TEST_F(cpu_test, INSTR_CCRF_NOTSET) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::CCRF);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::operand_types::NONE);
  cpu.mem_controller->load16(*cpu.xip + 3, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 5, hypercpu::operand_types::NONE);
  cpu.crf = false;

  cpu.run();

  ASSERT_FALSE(cpu.crf);
}
