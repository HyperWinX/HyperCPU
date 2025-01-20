#include <core/cpu/instructions/registers.hpp>
#include <core/cpu/instructions/flags.hpp>

#include <fixtures.hpp>


TEST_F(exception_test, CPU_EXCEPTION_IO) {
  cpu.mem_controller->load16(*cpu.xip, 8273);

  cpu.run();

  ASSERT_EQ(*cpu.xip, 1539);
}

TEST_F(exception_test, CPU_EXCEPTION_ZRDIV) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::DIV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b8 << 6 | hypercpu::operand_types::R);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XLLL0);
  *cpu.xlll0 = 0x55;
  *cpu.x2 = 0;

  cpu.run();

  ASSERT_EQ(*cpu.xip, 1539);
}
