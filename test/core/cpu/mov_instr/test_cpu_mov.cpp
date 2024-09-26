#include "core/cpu/instructions/flags.hpp"
#include <fixtures.hpp>

TEST_F(cpu_test, INSTR_MOV_R_R_b8) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 1, hypercpu::mode::b8 << 4 | hypercpu::operand_types::R_R);
  cpu.mem_controller->load16(*cpu.xip + 3, hypercpu::registers::XLLL0 << 8 | hypercpu::registers::XLLL1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.x1 = 0x0102030405060708;

  cpu.run();

  ASSERT_EQ(*cpu.xlll0, *cpu.xlll1);
}

TEST_F(cpu_test, INSTR_MOV_R_R_b16) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 1, hypercpu::mode::b16 << 4 | hypercpu::operand_types::R_R);
  cpu.mem_controller->load16(*cpu.xip + 3, hypercpu::registers::XLL0 << 8 | hypercpu::registers::XLL1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.x1 = 0x0102030405060708;

  cpu.run();

  ASSERT_EQ(*cpu.xll0, *cpu.xll1);
}

TEST_F(cpu_test, INSTR_MOV_R_R_b32) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 1, hypercpu::mode::b32 << 4 | hypercpu::operand_types::R_R);
  cpu.mem_controller->load16(*cpu.xip + 3, hypercpu::registers::XL0 << 8 | hypercpu::registers::XL1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.x1 = 0x0102030405060708;

  cpu.run();

  ASSERT_EQ(*cpu.xl0, *cpu.xl1);
}

TEST_F(cpu_test, INSTR_MOV_R_R_b64) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 1, hypercpu::mode::b64 << 4 | hypercpu::operand_types::R_R);
  cpu.mem_controller->load16(*cpu.xip + 3, hypercpu::registers::X0 << 8 | hypercpu::registers::X1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.x1 = 0x0102030405060708;

  cpu.run();

  ASSERT_EQ(*cpu.x0, *cpu.x1);
}