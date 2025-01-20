#include <core/cpu/instructions/registers.hpp>
#include <core/cpu/instructions/flags.hpp>
#include <core/cpu/version.hpp>

#include <fixtures.hpp>


TEST_F(cpu_test, INSTR_HID_0) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::HID);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::operand_types::NONE);
  cpu.mem_controller->load16(*cpu.xip + 3, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 5, hypercpu::operand_types::NONE);
  *cpu.x0 = 0;

  cpu.run();

  ASSERT_EQ(*cpu.x0, 2);
}

TEST_F(cpu_test, INSTR_HID_1) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::HID);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::operand_types::NONE);
  cpu.mem_controller->load16(*cpu.xip + 3, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 5, hypercpu::operand_types::NONE);
  *cpu.x0 = 1;

  cpu.run();

  ASSERT_TRUE(!std::strcmp(std::bit_cast<char*>(&cpu.data), HID_CPU_NAME));
}

TEST_F(cpu_test, INSTR_HID_2) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::HID);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::operand_types::NONE);
  cpu.mem_controller->load16(*cpu.xip + 3, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 5, hypercpu::operand_types::NONE);
  *cpu.x0 = 2;

  cpu.run();

  ASSERT_EQ(*cpu.x0, 0);
}