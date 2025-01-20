#include <core/cpu/instructions/registers.hpp>
#include <core/cpu/instructions/flags.hpp>

#include <fixtures.hpp>


static constexpr std::uint8_t BYTE_DATA1 = 0x55;
static constexpr std::uint8_t BYTE_DIVIDER = 0x5;
static constexpr std::uint8_t BYTE_RESULT = BYTE_DATA1 / BYTE_DIVIDER;
static constexpr std::uint8_t BYTE_REMAINDER = BYTE_DATA1 % BYTE_DIVIDER;

static constexpr std::uint16_t WORD_DATA1 = 0x5555;
static constexpr std::uint16_t WORD_DIVIDER = 0x2F;
static constexpr std::uint16_t WORD_RESULT = WORD_DATA1 / WORD_DIVIDER;
static constexpr std::uint16_t WORD_REMAINDER = WORD_DATA1 % WORD_DIVIDER;

static constexpr std::uint32_t DWORD_DATA1 = 0x55555555;
static constexpr std::uint32_t DWORD_DIVIDER = 0x682;
static constexpr std::uint32_t DWORD_RESULT = DWORD_DATA1 / DWORD_DIVIDER;
static constexpr std::uint32_t DWORD_REMAINDER = DWORD_DATA1 % DWORD_DIVIDER;

static constexpr std::uint64_t QWORD_DATA1 = 0x55555555;
static constexpr std::uint64_t QWORD_DIVIDER = 0x682;
static constexpr std::uint64_t QWORD_RESULT = DWORD_DATA1 / DWORD_DIVIDER;
static constexpr std::uint64_t QWORD_REMAINDER = DWORD_DATA1 % DWORD_DIVIDER;

TEST_F(cpu_test, INSTR_DIV_R_b8) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::DIV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b8 << 6 | hypercpu::operand_types::R);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XLLL0);
  cpu.mem_controller->load16(*cpu.xip + 4, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 6, hypercpu::operand_types::NONE);
  *cpu.xlll0 = BYTE_DATA1;
  *cpu.x2 = BYTE_DIVIDER;

  cpu.run();

  ASSERT_EQ(*cpu.xlll0, BYTE_RESULT);
  ASSERT_EQ(*cpu.x1, BYTE_REMAINDER);
}

TEST_F(cpu_test, INSTR_DIV_R_b16) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::DIV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b16 << 6 | hypercpu::operand_types::R);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XLL0);
  cpu.mem_controller->load16(*cpu.xip + 4, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 6, hypercpu::operand_types::NONE);
  *cpu.xll0 = WORD_DATA1;
  *cpu.x2 = WORD_DIVIDER;

  cpu.run();

  ASSERT_EQ(*cpu.xll0, WORD_RESULT);
  ASSERT_EQ(*cpu.x1, WORD_REMAINDER);
}

TEST_F(cpu_test, INSTR_DIV_R_b32) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::DIV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b32 << 6 | hypercpu::operand_types::R);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::XL0);
  cpu.mem_controller->load16(*cpu.xip + 4, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 6, hypercpu::operand_types::NONE);
  *cpu.xl0 = DWORD_DATA1;
  *cpu.x2 = DWORD_DIVIDER;

  cpu.run();

  ASSERT_EQ(*cpu.xl0, DWORD_RESULT);
  ASSERT_EQ(*cpu.x1, DWORD_REMAINDER);
}

TEST_F(cpu_test, INSTR_DIV_R_b64) {
  cpu.mem_controller->load16(*cpu.xip, hypercpu::opcode::DIV);
  cpu.mem_controller->load8(*cpu.xip + 2, hypercpu::mode::b64 << 6 | hypercpu::operand_types::R);
  cpu.mem_controller->load8(*cpu.xip + 3, hypercpu::registers::X0);
  cpu.mem_controller->load16(*cpu.xip + 4, hypercpu::opcode::HALT);
  cpu.mem_controller->load8(*cpu.xip + 6, hypercpu::operand_types::NONE);
  *cpu.x0 = QWORD_DATA1;
  *cpu.x2 = QWORD_DIVIDER;

  cpu.run();

  ASSERT_EQ(*cpu.x0, QWORD_RESULT);
  ASSERT_EQ(*cpu.x1, QWORD_REMAINDER);
}
