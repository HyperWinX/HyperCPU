#include "core/cpu/instructions/flags.hpp"
#include "core/cpu/instructions/registers.hpp"
#include <fixtures.hpp>

static constexpr std::uint8_t BYTE_DATA = 0x55;
static constexpr std::uint16_t WORD_DATA = 0x5555;
static constexpr std::uint32_t DWORD_DATA = 0x55555555;
static constexpr std::uint64_t QWORD_DATA = 0x5555555555555555;
static constexpr std::uint64_t RND_QWORD_DATA = 0x0102030405060708;

TEST_F(cpu_test, INSTR_MOV_R_R_b8) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b8 << 6 | hypercpu::operand_types::R_R);
  cpu.mem_controller->load16(*cpu.xip + 3, hypercpu::registers::XLLL0 << 8 | hypercpu::registers::XLLL1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.x1 = RND_QWORD_DATA;

  cpu.run();

  ASSERT_EQ(*cpu.xlll0, *cpu.xlll1);
}

TEST_F(cpu_test, INSTR_MOV_R_R_b16) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b16 << 6 | hypercpu::operand_types::R_R);
  cpu.mem_controller->load16(*cpu.xip + 3, hypercpu::registers::XLL0 << 8 | hypercpu::registers::XLL1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.x1 = RND_QWORD_DATA;

  cpu.run();

  ASSERT_EQ(*cpu.xll0, *cpu.xll1);
}

TEST_F(cpu_test, INSTR_MOV_R_R_b32) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b32 << 6 | hypercpu::operand_types::R_R);
  cpu.mem_controller->load16(*cpu.xip + 3, hypercpu::registers::XL0 << 8 | hypercpu::registers::XL1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.x1 = RND_QWORD_DATA;

  cpu.run();

  ASSERT_EQ(*cpu.xl0, *cpu.xl1);
}

TEST_F(cpu_test, INSTR_MOV_R_R_b64) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b64 << 6 | hypercpu::operand_types::R_R);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::X0);
  cpu.mem_controller->load8(*cpu.xip + 4, hypercpu::registers::X1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.x1 = RND_QWORD_DATA;

  cpu.run();

  ASSERT_EQ(*cpu.x0, *cpu.x1);
}

TEST_F(cpu_test, INSTR_MOV_R_RM_b8) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b8 << 6 | hypercpu::operand_types::R_RM);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XLLL0);
  cpu.mem_controller->load8(*cpu.xip + 4, hypercpu::registers::X1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  cpu.mem_controller->load8(*cpu.xip + 1024, BYTE_DATA);
  *cpu.x1 = 1024;

  cpu.run();

  ASSERT_EQ(*cpu.xlll0, BYTE_DATA);
}

TEST_F(cpu_test, INSTR_MOV_R_RM_b16) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b16 << 6 | hypercpu::operand_types::R_RM);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XLL0);
  cpu.mem_controller->load8(*cpu.xip + 4, hypercpu::registers::X1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  cpu.mem_controller->load16(*cpu.xip + 1024, WORD_DATA);
  *cpu.x1 = 1024;

  cpu.run();

  ASSERT_EQ(*cpu.xll0, WORD_DATA);
}

TEST_F(cpu_test, INSTR_MOV_R_RM_b32) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b32 << 6 | hypercpu::operand_types::R_RM);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XL0);
  cpu.mem_controller->load8(*cpu.xip + 4, hypercpu::registers::X1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  cpu.mem_controller->load32(*cpu.xip + 1024, DWORD_DATA);
  *cpu.x1 = 1024;

  cpu.run();

  ASSERT_EQ(*cpu.xl0, DWORD_DATA);
}

TEST_F(cpu_test, INSTR_MOV_R_RM_b64) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b64 << 6 | hypercpu::operand_types::R_RM);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::X0);
  cpu.mem_controller->load8(*cpu.xip + 4, hypercpu::registers::X1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  cpu.mem_controller->load64(*cpu.xip + 1024, QWORD_DATA);
  *cpu.x1 = 1024;

  cpu.run();

  ASSERT_EQ(*cpu.x0, QWORD_DATA);
}

TEST_F(cpu_test, INSTR_MOV_R_M_b8) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b8 << 6 | hypercpu::operand_types::R_M);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XLLL0);
  cpu.mem_controller->load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->load16(*cpu.xip + 12, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 14, hypercpu::operand_types::NONE);
  cpu.mem_controller->load8(*cpu.xip + 1024, BYTE_DATA);
  *cpu.x1 = 1024;

  cpu.run();

  ASSERT_EQ(*cpu.xlll0, BYTE_DATA);
}

TEST_F(cpu_test, INSTR_MOV_R_M_b16) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b16 << 6 | hypercpu::operand_types::R_M);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XLL0);
  cpu.mem_controller->load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->load16(*cpu.xip + 12, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 14, hypercpu::operand_types::NONE);
  cpu.mem_controller->load16(*cpu.xip + 1024, WORD_DATA);
  *cpu.x1 = 1024;

  cpu.run();

  ASSERT_EQ(*cpu.xll0, WORD_DATA);
}

TEST_F(cpu_test, INSTR_MOV_R_M_b32) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b32 << 6 | hypercpu::operand_types::R_M);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XL0);
  cpu.mem_controller->load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->load16(*cpu.xip + 12, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 14, hypercpu::operand_types::NONE);
  cpu.mem_controller->load32(*cpu.xip + 1024, DWORD_DATA);
  *cpu.x1 = 1024;

  cpu.run();

  ASSERT_EQ(*cpu.xl0, DWORD_DATA);
}

TEST_F(cpu_test, INSTR_MOV_R_M_b64) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b64 << 6 | hypercpu::operand_types::R_M);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::X0);
  cpu.mem_controller->load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->load16(*cpu.xip + 12, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 14, hypercpu::operand_types::NONE);
  cpu.mem_controller->load64(*cpu.xip + 1024, QWORD_DATA);
  *cpu.x1 = 1024;

  cpu.run();

  ASSERT_EQ(*cpu.x0, QWORD_DATA);
}

TEST_F(cpu_test, INSTR_MOV_R_IMM_b8) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b8 << 6 | hypercpu::operand_types::R_IMM);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XLLL0);
  cpu.mem_controller->load8(*cpu.xip + 4, BYTE_DATA);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);

  cpu.run();

  ASSERT_EQ(*cpu.xlll0, BYTE_DATA);
}

TEST_F(cpu_test, INSTR_MOV_R_IMM_b16) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b16 << 6 | hypercpu::operand_types::R_IMM);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XLL0);
  cpu.mem_controller->load16(*cpu.xip + 4, WORD_DATA);
  cpu.mem_controller->load16(*cpu.xip + 6, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 8, hypercpu::operand_types::NONE);

  cpu.run();

  ASSERT_EQ(*cpu.xll0, WORD_DATA);
}

TEST_F(cpu_test, INSTR_MOV_R_IMM_b32) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b32 << 6 | hypercpu::operand_types::R_IMM);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XL0);
  cpu.mem_controller->load32(*cpu.xip + 4, DWORD_DATA);
  cpu.mem_controller->load16(*cpu.xip + 8, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 10, hypercpu::operand_types::NONE);

  cpu.run();

  ASSERT_EQ(*cpu.xl0, DWORD_DATA);
}

TEST_F(cpu_test, INSTR_MOV_R_IMM_b64) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b64 << 6 | hypercpu::operand_types::R_IMM);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::X0);
  cpu.mem_controller->load64(*cpu.xip + 4, QWORD_DATA);
  cpu.mem_controller->load16(*cpu.xip + 12, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 14, hypercpu::operand_types::NONE);

  cpu.run();

  ASSERT_EQ(*cpu.x0, QWORD_DATA);
}

TEST_F(cpu_test, INSTR_MOV_RM_R_b8) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b8 << 6 | hypercpu::operand_types::RM_R);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::X0);
  cpu.mem_controller->load8(*cpu.xip + 4, hypercpu::registers::XLLL1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.x0 = 1024;
  *cpu.xlll1 = BYTE_DATA;

  cpu.run();

  ASSERT_EQ(cpu.mem_controller->read8(1024), BYTE_DATA);
}

TEST_F(cpu_test, INSTR_MOV_RM_R_b16) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b16 << 6 | hypercpu::operand_types::RM_R);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::X0);
  cpu.mem_controller->load8(*cpu.xip + 4, hypercpu::registers::XLL1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.x0 = 1024;
  *cpu.xll1 = WORD_DATA;

  cpu.run();

  ASSERT_EQ(cpu.mem_controller->read16(1024), WORD_DATA);
}

TEST_F(cpu_test, INSTR_MOV_RM_R_b32) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b32 << 6 | hypercpu::operand_types::RM_R);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::X0);
  cpu.mem_controller->load8(*cpu.xip + 4, hypercpu::registers::XL1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.x0 = 1024;
  *cpu.xl1 = DWORD_DATA;

  cpu.run();

  ASSERT_EQ(cpu.mem_controller->read32(1024), DWORD_DATA);
}

TEST_F(cpu_test, INSTR_MOV_RM_R_b64) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b64 << 6 | hypercpu::operand_types::RM_R);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::X0);
  cpu.mem_controller->load8(*cpu.xip + 4, hypercpu::registers::X1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.x0 = 1024;
  *cpu.x1 = QWORD_DATA;

  cpu.run();

  ASSERT_EQ(cpu.mem_controller->read64(1024), QWORD_DATA);
}

TEST_F(cpu_test, INSTR_MOV_RM_M_b8) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b8 << 6 | hypercpu::operand_types::RM_M);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::X0);
  cpu.mem_controller->load64(*cpu.xip + 4, 1536);
  cpu.mem_controller->load16(*cpu.xip + 12, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 14, hypercpu::operand_types::NONE);
  cpu.mem_controller->load8(1536, BYTE_DATA);
  *cpu.x0 = 1024;

  cpu.run();

  ASSERT_EQ(cpu.mem_controller->read8(1024), BYTE_DATA);
}

TEST_F(cpu_test, INSTR_MOV_RM_M_b16) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b16 << 6 | hypercpu::operand_types::RM_M);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::X0);
  cpu.mem_controller->load64(*cpu.xip + 4, 1536);
  cpu.mem_controller->load16(*cpu.xip + 12, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 14, hypercpu::operand_types::NONE);
  cpu.mem_controller->load16(1536, WORD_DATA);
  *cpu.x0 = 1024;

  cpu.run();

  ASSERT_EQ(cpu.mem_controller->read16(1024), WORD_DATA);
}

TEST_F(cpu_test, INSTR_MOV_RM_M_b32) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b32 << 6 | hypercpu::operand_types::RM_M);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::X0);
  cpu.mem_controller->load64(*cpu.xip + 4, 1536);
  cpu.mem_controller->load16(*cpu.xip + 12, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 14, hypercpu::operand_types::NONE);
  cpu.mem_controller->load32(1536, DWORD_DATA);
  *cpu.x0 = 1024;

  cpu.run();

  ASSERT_EQ(cpu.mem_controller->read32(1024), DWORD_DATA);
}

TEST_F(cpu_test, INSTR_MOV_RM_M_b64) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b64 << 6 | hypercpu::operand_types::RM_M);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::X0);
  cpu.mem_controller->load64(*cpu.xip + 4, 1536);
  cpu.mem_controller->load16(*cpu.xip + 12, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 14, hypercpu::operand_types::NONE);
  cpu.mem_controller->load64(1536,  QWORD_DATA);
  *cpu.x0 = 1024;

  cpu.run();

  ASSERT_EQ(cpu.mem_controller->read64(1024), QWORD_DATA);
}

TEST_F(cpu_test, INSTR_MOV_M_R_b8) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b8 << 6 | hypercpu::operand_types::M_R);
  cpu.mem_controller->load64(*cpu.xip + 3, 1024);
  cpu.mem_controller->load8(*cpu.xip + 11, hypercpu::registers::XLLL0);
  cpu.mem_controller->load16(*cpu.xip + 12, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 14, hypercpu::operand_types::NONE);
  *cpu.xlll0 = BYTE_DATA;

  cpu.run();

  ASSERT_EQ(cpu.mem_controller->read8(1024), BYTE_DATA);
}

TEST_F(cpu_test, INSTR_MOV_M_R_b16) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b16 << 6 | hypercpu::operand_types::M_R);
  cpu.mem_controller->load64(*cpu.xip + 3, 1024);
  cpu.mem_controller->load8(*cpu.xip + 11, hypercpu::registers::XLL0);
  cpu.mem_controller->load16(*cpu.xip + 12, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 14, hypercpu::operand_types::NONE);
  *cpu.xll0 = WORD_DATA;

  cpu.run();

  ASSERT_EQ(cpu.mem_controller->read16(1024), WORD_DATA);
}

TEST_F(cpu_test, INSTR_MOV_M_R_b32) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b32 << 6 | hypercpu::operand_types::M_R);
  cpu.mem_controller->load64(*cpu.xip + 3, 1024);
  cpu.mem_controller->load8(*cpu.xip + 11, hypercpu::registers::XL0);
  cpu.mem_controller->load16(*cpu.xip + 12, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 14, hypercpu::operand_types::NONE);
  *cpu.xl0 = DWORD_DATA;

  cpu.run();

  ASSERT_EQ(cpu.mem_controller->read32(1024), DWORD_DATA);
}

TEST_F(cpu_test, INSTR_MOV_M_R_b64) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::MOV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b64 << 6 | hypercpu::operand_types::M_R);
  cpu.mem_controller->load64(*cpu.xip + 3, 1024);
  cpu.mem_controller->load8(*cpu.xip + 11, hypercpu::registers::X0);
  cpu.mem_controller->load16(*cpu.xip + 12, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 14, hypercpu::operand_types::NONE);
  *cpu.x0 = QWORD_DATA;

  cpu.run();

  ASSERT_EQ(cpu.mem_controller->read64(1024), QWORD_DATA);
}
