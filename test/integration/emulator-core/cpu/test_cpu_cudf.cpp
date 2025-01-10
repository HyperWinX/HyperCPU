#include <core/cpu/instructions/registers.hpp>
#include <core/cpu/instructions/flags.hpp>

#include <fixtures.hpp>


TEST_F(cpu_test, INSTR_CUDF_SET) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::CUDF);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::operand_types::NONE);
  cpu.mem_controller->load16(*cpu.xip + 3, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 5, hypercpu::operand_types::NONE);
  cpu.udf = true;

  cpu.run();

  ASSERT_FALSE(cpu.udf);
}

TEST_F(cpu_test, INSTR_CUDF_NOTSET) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::CUDF);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::operand_types::NONE);
  cpu.mem_controller->load16(*cpu.xip + 3, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 5, hypercpu::operand_types::NONE);
  cpu.udf = false;

  cpu.run();

  ASSERT_FALSE(cpu.udf);
}
