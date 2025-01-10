#include <core/cpu/instructions/registers.hpp>
#include <core/cpu/instructions/flags.hpp>

#include <fixtures.hpp>


static constexpr std::uint8_t BYTE_DATA1 = 0x60;
static constexpr std::uint8_t BYTE_DATA2 = 0x55;
static constexpr std::uint8_t BYTE_RESULT = BYTE_DATA1 - BYTE_DATA2;
static constexpr std::uint16_t WORD_DATA1 = 0x6060;
static constexpr std::uint16_t WORD_DATA2 = 0x5555;
static constexpr std::uint16_t WORD_RESULT = WORD_DATA1 - WORD_DATA2;
static constexpr std::uint32_t DWORD_DATA1 = 0x60606060;
static constexpr std::uint32_t DWORD_DATA2 = 0x55555555;
static constexpr std::uint32_t DWORD_RESULT = DWORD_DATA1 - DWORD_DATA2;
static constexpr std::uint64_t QWORD_DATA1 = 0x6060606060606060;
static constexpr std::uint64_t QWORD_DATA2 = 0x5555555555555555;
static constexpr std::uint64_t QWORD_RESULT = QWORD_DATA1 - QWORD_DATA2;

static constexpr std::uint8_t BYTE_DATA1_UF = 0x60;
static constexpr std::uint8_t BYTE_DATA2_UF = 0xBA;
static constexpr std::uint8_t BYTE_RESULT_UF = static_cast<std::uint8_t>(BYTE_DATA1_UF - BYTE_DATA2_UF);
static constexpr std::uint16_t WORD_DATA1_UF = 0x6060;
static constexpr std::uint16_t WORD_DATA2_UF = 0xBABA;
static constexpr std::uint16_t WORD_RESULT_UF = static_cast<std::uint16_t>(WORD_DATA1_UF - WORD_DATA2_UF);
static constexpr std::uint32_t DWORD_DATA1_UF = 0x60606060;
static constexpr std::uint32_t DWORD_DATA2_UF = 0xBABABABA;
static constexpr std::uint32_t DWORD_RESULT_UF = static_cast<std::uint32_t>(DWORD_DATA1_UF - DWORD_DATA2_UF);
static constexpr std::uint64_t QWORD_DATA1_UF = 0x6060606060606060;
static constexpr std::uint64_t QWORD_DATA2_UF = 0xBABABABABABABABA;
static constexpr std::uint64_t QWORD_RESULT_UF = QWORD_DATA1_UF - QWORD_DATA2_UF;

TEST_F(cpu_test, INSTR_SUB_R_R_b8) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b8 << 6 | hypercpu::operand_types::R_R);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XLLL0);
  cpu.mem_controller->load8(*cpu.xip + 4, hypercpu::registers::XLLL1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.xlll0 = BYTE_DATA1;
  *cpu.xlll1 = BYTE_DATA2;

  cpu.run();

  ASSERT_EQ(*cpu.xlll0, BYTE_RESULT);
}

TEST_F(cpu_test, INSTR_SUB_R_R_b16) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b16 << 6 | hypercpu::operand_types::R_R);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XLL0);
  cpu.mem_controller->load8(*cpu.xip + 4, hypercpu::registers::XLL1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.xll0 = WORD_DATA1;
  *cpu.xll1 = WORD_DATA2;

  cpu.run();

  ASSERT_EQ(*cpu.xll0, WORD_RESULT);
}

TEST_F(cpu_test, INSTR_SUB_R_R_b32) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b32 << 6 | hypercpu::operand_types::R_R);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XL0);
  cpu.mem_controller->load8(*cpu.xip + 4, hypercpu::registers::XL1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.xl0 = DWORD_DATA1;
  *cpu.xl1 = DWORD_DATA2;

  cpu.run();

  ASSERT_EQ(*cpu.xl0, DWORD_RESULT);
}

TEST_F(cpu_test, INSTR_SUB_R_R_b64) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b64 << 6 | hypercpu::operand_types::R_R);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::X0);
  cpu.mem_controller->load8(*cpu.xip + 4, hypercpu::registers::X1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.x0 = QWORD_DATA1;
  *cpu.x1 = QWORD_DATA2;

  cpu.run();

  ASSERT_EQ(*cpu.x0, QWORD_RESULT);
}

TEST_F(cpu_test, INSTR_SUB_R_RM_b8) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b8 << 6 | hypercpu::operand_types::R_RM);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XLLL0);
  cpu.mem_controller->load8(*cpu.xip + 4, hypercpu::registers::X1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.xlll0 = BYTE_DATA1;
  cpu.mem_controller->load8(1024, BYTE_DATA2);
  *cpu.x1 = 1024;

  cpu.run();

  ASSERT_EQ(*cpu.xlll0, BYTE_RESULT);
}

TEST_F(cpu_test, INSTR_SUB_R_RM_b16) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b16 << 6 | hypercpu::operand_types::R_RM);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XLL0);
  cpu.mem_controller->load8(*cpu.xip + 4, hypercpu::registers::X1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.xll0 = WORD_DATA1;
  cpu.mem_controller->load16(1024, WORD_DATA2);
  *cpu.x1 = 1024;

  cpu.run();

  ASSERT_EQ(*cpu.xll0, WORD_RESULT);
}

TEST_F(cpu_test, INSTR_SUB_R_RM_b32) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b32 << 6 | hypercpu::operand_types::R_RM);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XL0);
  cpu.mem_controller->load8(*cpu.xip + 4, hypercpu::registers::X1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.xl0 = DWORD_DATA1;
  cpu.mem_controller->load32(1024, DWORD_DATA2);
  *cpu.x1 = 1024;

  cpu.run();

  ASSERT_EQ(*cpu.xl0, DWORD_RESULT);
}

TEST_F(cpu_test, INSTR_SUB_R_RM_b64) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b64 << 6 | hypercpu::operand_types::R_RM);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::X0);
  cpu.mem_controller->load8(*cpu.xip + 4, hypercpu::registers::X1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.x0 = QWORD_DATA1;
  cpu.mem_controller->load64(1024, QWORD_DATA2);
  *cpu.x1 = 1024;

  cpu.run();

  ASSERT_EQ(*cpu.x0, QWORD_RESULT);
}

TEST_F(cpu_test, INSTR_SUB_R_M_b8) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b8 << 6 | hypercpu::operand_types::R_M);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XLLL0);
  cpu.mem_controller->load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->load16(*cpu.xip + 12, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 14, hypercpu::operand_types::NONE);
  *cpu.xlll0 = BYTE_DATA1;
  cpu.mem_controller->load8(1024, BYTE_DATA2);

  cpu.run();

  ASSERT_EQ(*cpu.xlll0, BYTE_RESULT);
}

TEST_F(cpu_test, INSTR_SUB_R_M_b16) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b16 << 6 | hypercpu::operand_types::R_M);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XLL0);
  cpu.mem_controller->load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->load16(*cpu.xip + 12, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 14, hypercpu::operand_types::NONE);
  *cpu.xll0 = WORD_DATA1;
  cpu.mem_controller->load16(1024, WORD_DATA2);

  cpu.run();

  ASSERT_EQ(*cpu.xll0, WORD_RESULT);
}

TEST_F(cpu_test, INSTR_SUB_R_M_b32) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b32 << 6 | hypercpu::operand_types::R_M);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XL0);
  cpu.mem_controller->load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->load16(*cpu.xip + 12, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 14, hypercpu::operand_types::NONE);
  *cpu.xl0 = DWORD_DATA1;
  cpu.mem_controller->load32(1024, DWORD_DATA2);

  cpu.run();

  ASSERT_EQ(*cpu.xl0, DWORD_RESULT);
}

TEST_F(cpu_test, INSTR_SUB_R_M_b64) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b64 << 6 | hypercpu::operand_types::R_M);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::X0);
  cpu.mem_controller->load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->load16(*cpu.xip + 12, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 14, hypercpu::operand_types::NONE);
  *cpu.x0 = QWORD_DATA1;
  cpu.mem_controller->load64(1024, QWORD_DATA2);

  cpu.run();

  ASSERT_EQ(*cpu.x0, QWORD_RESULT);
}

TEST_F(cpu_test, INSTR_SUB_R_IMM_b8) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b8 << 6 | hypercpu::operand_types::R_IMM);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XLLL0);
  cpu.mem_controller->load8(*cpu.xip + 4, BYTE_DATA2);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.xlll0 = BYTE_DATA1;

  cpu.run();

  ASSERT_EQ(*cpu.xlll0, BYTE_RESULT);
}

TEST_F(cpu_test, INSTR_SUB_R_IMM_b16) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b16 << 6 | hypercpu::operand_types::R_IMM);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XLL0);
  cpu.mem_controller->load16(*cpu.xip + 4, WORD_DATA2);
  cpu.mem_controller->load16(*cpu.xip + 6, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 8, hypercpu::operand_types::NONE);
  *cpu.xll0 = WORD_DATA1;

  cpu.run();

  ASSERT_EQ(*cpu.xll0, WORD_RESULT);
}

TEST_F(cpu_test, INSTR_SUB_R_IMM_b32) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b32 << 6 | hypercpu::operand_types::R_IMM);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XL0);
  cpu.mem_controller->load32(*cpu.xip + 4, DWORD_DATA2);
  cpu.mem_controller->load16(*cpu.xip + 8, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 10, hypercpu::operand_types::NONE);
  *cpu.xl0 = DWORD_DATA1;

  cpu.run();

  ASSERT_EQ(*cpu.xl0, DWORD_RESULT);
}

TEST_F(cpu_test, INSTR_SUB_R_IMM_b64) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b64 << 6 | hypercpu::operand_types::R_IMM);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::X0);
  cpu.mem_controller->load64(*cpu.xip + 4, QWORD_DATA2);
  cpu.mem_controller->load16(*cpu.xip + 12, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 14, hypercpu::operand_types::NONE);
  *cpu.x0 = QWORD_DATA1;

  cpu.run();

  ASSERT_EQ(*cpu.x0, QWORD_RESULT);
}

TEST_F(cpu_test, INSTR_SUB_R_R_b8_UF) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b8 << 6 | hypercpu::operand_types::R_R);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XLLL0);
  cpu.mem_controller->load8(*cpu.xip + 4, hypercpu::registers::XLLL1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.xlll0 = BYTE_DATA1_UF;
  *cpu.xlll1 = BYTE_DATA2_UF;

  cpu.run();

  ASSERT_EQ(*cpu.xlll0, BYTE_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(cpu_test, INSTR_SUB_R_R_b16_UF) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b16 << 6 | hypercpu::operand_types::R_R);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XLL0);
  cpu.mem_controller->load8(*cpu.xip + 4, hypercpu::registers::XLL1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.xll0 = WORD_DATA1_UF;
  *cpu.xll1 = WORD_DATA2_UF;

  cpu.run();

  ASSERT_EQ(*cpu.xll0, WORD_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(cpu_test, INSTR_SUB_R_R_b32_UF) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b32 << 6 | hypercpu::operand_types::R_R);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XL0);
  cpu.mem_controller->load8(*cpu.xip + 4, hypercpu::registers::XL1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.xl0 = DWORD_DATA1_UF;
  *cpu.xl1 = DWORD_DATA2_UF;

  cpu.run();

  ASSERT_EQ(*cpu.xl0, DWORD_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(cpu_test, INSTR_SUB_R_R_b64_UF) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b64 << 6 | hypercpu::operand_types::R_R);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::X0);
  cpu.mem_controller->load8(*cpu.xip + 4, hypercpu::registers::X1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.x0 = QWORD_DATA1_UF;
  *cpu.x1 = QWORD_DATA2_UF;

  cpu.run();

  ASSERT_EQ(*cpu.x0, QWORD_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(cpu_test, INSTR_SUB_R_RM_b8_UF) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b8 << 6 | hypercpu::operand_types::R_RM);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XLLL0);
  cpu.mem_controller->load8(*cpu.xip + 4, hypercpu::registers::X1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.xlll0 = BYTE_DATA1_UF;
  cpu.mem_controller->load8(1024, BYTE_DATA2_UF);
  *cpu.x1 = 1024;

  cpu.run();

  ASSERT_EQ(*cpu.xlll0, BYTE_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(cpu_test, INSTR_SUB_R_RM_b16_UF) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b16 << 6 | hypercpu::operand_types::R_RM);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XLL0);
  cpu.mem_controller->load8(*cpu.xip + 4, hypercpu::registers::X1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.xll0 = WORD_DATA1_UF;
  cpu.mem_controller->load16(1024, WORD_DATA2_UF);
  *cpu.x1 = 1024;

  cpu.run();

  ASSERT_EQ(*cpu.xll0, WORD_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(cpu_test, INSTR_SUB_R_RM_b32_UF) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b32 << 6 | hypercpu::operand_types::R_RM);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XL0);
  cpu.mem_controller->load8(*cpu.xip + 4, hypercpu::registers::X1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.xl0 = DWORD_DATA1_UF;
  cpu.mem_controller->load32(1024, DWORD_DATA2_UF);
  *cpu.x1 = 1024;

  cpu.run();

  ASSERT_EQ(*cpu.xl0, DWORD_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(cpu_test, INSTR_SUB_R_RM_b64_UF) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b64 << 6 | hypercpu::operand_types::R_RM);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::X0);
  cpu.mem_controller->load8(*cpu.xip + 4, hypercpu::registers::X1);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.x0 = QWORD_DATA1_UF;
  cpu.mem_controller->load64(1024, QWORD_DATA2_UF);
  *cpu.x1 = 1024;

  cpu.run();

  ASSERT_EQ(*cpu.x0, QWORD_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(cpu_test, INSTR_SUB_R_M_b8_UF) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b8 << 6 | hypercpu::operand_types::R_M);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XLLL0);
  cpu.mem_controller->load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->load16(*cpu.xip + 12, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 14, hypercpu::operand_types::NONE);
  *cpu.xlll0 = BYTE_DATA1_UF;
  cpu.mem_controller->load8(1024, BYTE_DATA2_UF);

  cpu.run();

  ASSERT_EQ(*cpu.xlll0, BYTE_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(cpu_test, INSTR_SUB_R_M_b16_UF) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b16 << 6 | hypercpu::operand_types::R_M);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XLL0);
  cpu.mem_controller->load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->load16(*cpu.xip + 12, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 14, hypercpu::operand_types::NONE);
  *cpu.xll0 = WORD_DATA1_UF;
  cpu.mem_controller->load16(1024, WORD_DATA2_UF);

  cpu.run();

  ASSERT_EQ(*cpu.xll0, WORD_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(cpu_test, INSTR_SUB_R_M_b32_UF) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b32 << 6 | hypercpu::operand_types::R_M);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XL0);
  cpu.mem_controller->load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->load16(*cpu.xip + 12, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 14, hypercpu::operand_types::NONE);
  *cpu.xl0 = DWORD_DATA1_UF;
  cpu.mem_controller->load32(1024, DWORD_DATA2_UF);

  cpu.run();

  ASSERT_EQ(*cpu.xl0, DWORD_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(cpu_test, INSTR_SUB_R_M_b64_UF) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b64 << 6 | hypercpu::operand_types::R_M);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::X0);
  cpu.mem_controller->load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->load16(*cpu.xip + 12, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 14, hypercpu::operand_types::NONE);
  *cpu.x0 = QWORD_DATA1_UF;
  cpu.mem_controller->load64(1024, QWORD_DATA2_UF);

  cpu.run();

  ASSERT_EQ(*cpu.x0, QWORD_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(cpu_test, INSTR_SUB_R_IMM_b8_UF) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b8 << 6 | hypercpu::operand_types::R_IMM);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XLLL0);
  cpu.mem_controller->load8(*cpu.xip + 4, BYTE_DATA2_UF);
  cpu.mem_controller->load16(*cpu.xip + 5, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 7, hypercpu::operand_types::NONE);
  *cpu.xlll0 = BYTE_DATA1_UF;

  cpu.run();

  ASSERT_EQ(*cpu.xlll0, BYTE_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(cpu_test, INSTR_SUB_R_IMM_b16_UF) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b16 << 6 | hypercpu::operand_types::R_IMM);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XLL0);
  cpu.mem_controller->load16(*cpu.xip + 4, WORD_DATA2_UF);
  cpu.mem_controller->load16(*cpu.xip + 6, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 8, hypercpu::operand_types::NONE);
  *cpu.xll0 = WORD_DATA1_UF;

  cpu.run();

  ASSERT_EQ(*cpu.xll0, WORD_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(cpu_test, INSTR_SUB_R_IMM_b32_UF) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b32 << 6 | hypercpu::operand_types::R_IMM);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XL0);
  cpu.mem_controller->load32(*cpu.xip + 4, DWORD_DATA2_UF);
  cpu.mem_controller->load16(*cpu.xip + 8, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 10, hypercpu::operand_types::NONE);
  *cpu.xl0 = DWORD_DATA1_UF;

  cpu.run();

  ASSERT_EQ(*cpu.xl0, DWORD_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(cpu_test, INSTR_SUB_R_IMM_b64_UF) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::SUB);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b64 << 6 | hypercpu::operand_types::R_IMM);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::X0);
  cpu.mem_controller->load64(*cpu.xip + 4, QWORD_DATA2_UF);
  cpu.mem_controller->load16(*cpu.xip + 12, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 14, hypercpu::operand_types::NONE);
  *cpu.x0 = QWORD_DATA1_UF;

  cpu.run();

  ASSERT_EQ(*cpu.x0, QWORD_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}
