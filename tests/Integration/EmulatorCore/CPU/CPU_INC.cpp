#include <Core/CPU/Instructions/Flags.hpp>
#include <Core/CPU/Instructions/Registers.hpp>

#include <fixtures.hpp>

static constexpr std::uint8_t BYTE_DATA1 = 0x55;
static constexpr std::uint8_t BYTE_RESULT = BYTE_DATA1 + 1;
static constexpr std::uint16_t WORD_DATA1 = 0x5555;
static constexpr std::uint16_t WORD_RESULT = WORD_DATA1 + 1;
static constexpr std::uint32_t DWORD_DATA1 = 0x55555555;
static constexpr std::uint32_t DWORD_RESULT = DWORD_DATA1 + 1;
static constexpr std::uint64_t QWORD_DATA1 = 0x555555555555555;
static constexpr std::uint64_t QWORD_RESULT = QWORD_DATA1 + 1;

static constexpr std::uint8_t BYTE_DATA1_OF = 0xFF;
static constexpr std::uint16_t WORD_DATA1_OF = 0xFFFF;
static constexpr std::uint32_t DWORD_DATA1_OF = 0xFFFFFFFF;
static constexpr std::uint64_t QWORD_DATA1_OF = 0xFFFFFFFFFFFFFFFF;

TEST_F(CPU_TEST, INSTR_INC_R_b8) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::INC);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b8 << 4 | HyperCPU::OperandTypes::R);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XLLL0);
  cpu.mem_controller->Load16(*cpu.xip + 4, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 6, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = BYTE_DATA1;

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, BYTE_RESULT);
  ASSERT_FALSE(cpu.ovf);
}

TEST_F(CPU_TEST, INSTR_INC_R_b16) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::INC);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b16 << 4 | HyperCPU::OperandTypes::R);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XLL0);
  cpu.mem_controller->Load16(*cpu.xip + 4, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 6, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = WORD_DATA1;

  cpu.Run();

  ASSERT_EQ(*cpu.xll0, WORD_RESULT);
  ASSERT_FALSE(cpu.ovf);
}

TEST_F(CPU_TEST, INSTR_INC_R_b32) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::INC);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b32 << 4 | HyperCPU::OperandTypes::R);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XL0);
  cpu.mem_controller->Load16(*cpu.xip + 4, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 6, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = DWORD_DATA1;

  cpu.Run();

  ASSERT_EQ(*cpu.xl0, DWORD_RESULT);
  ASSERT_FALSE(cpu.ovf);
}

TEST_F(CPU_TEST, INSTR_INC_R_b64) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::INC);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b64 << 4 | HyperCPU::OperandTypes::R);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::X0);
  cpu.mem_controller->Load16(*cpu.xip + 4, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 6, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = QWORD_DATA1;

  cpu.Run();

  ASSERT_EQ(*cpu.x0, QWORD_RESULT);
  ASSERT_FALSE(cpu.ovf);
}

TEST_F(CPU_TEST, INSTR_INC_R_b8_OF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::INC);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b8 << 4 | HyperCPU::OperandTypes::R);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XLLL0);
  cpu.mem_controller->Load16(*cpu.xip + 4, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 6, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = BYTE_DATA1_OF;

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, 0);
  ASSERT_TRUE(cpu.ovf);
}

TEST_F(CPU_TEST, INSTR_INC_R_b16_OF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::INC);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b16 << 4 | HyperCPU::OperandTypes::R);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XLL0);
  cpu.mem_controller->Load16(*cpu.xip + 4, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 6, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = WORD_DATA1_OF;

  cpu.Run();

  ASSERT_EQ(*cpu.xll0, 0);
  ASSERT_TRUE(cpu.ovf);
}

TEST_F(CPU_TEST, INSTR_INC_R_b32_OF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::INC);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b32 << 4 | HyperCPU::OperandTypes::R);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XL0);
  cpu.mem_controller->Load16(*cpu.xip + 4, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 6, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = DWORD_DATA1_OF;

  cpu.Run();

  ASSERT_EQ(*cpu.xl0, 0);
  ASSERT_TRUE(cpu.ovf);
}

TEST_F(CPU_TEST, INSTR_INC_R_b64_OF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::INC);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b64 << 4 | HyperCPU::OperandTypes::R);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::X0);
  cpu.mem_controller->Load16(*cpu.xip + 4, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 6, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = QWORD_DATA1_OF;

  cpu.Run();

  ASSERT_EQ(*cpu.x0, 0);
  ASSERT_TRUE(cpu.ovf);
}