#include <bit>

#include <Core/CPU/Instructions/Flags.hpp>
#include <Core/CPU/Instructions/Registers.hpp>
#include <Misc/byteswap.hpp>

#include <fixtures.hpp>

static constexpr std::uint8_t BYTE_DATA1 = 0x12;
static constexpr std::uint8_t BYTE_RESULT = BYTE_DATA1;
static constexpr std::uint16_t WORD_DATA1 = 0x1234;
static std::uint16_t WORD_RESULT = HyperCPU::byteswap(WORD_DATA1);
static constexpr std::uint32_t DWORD_DATA1 = 0x12345678;
static std::uint32_t DWORD_RESULT = HyperCPU::byteswap(DWORD_DATA1);
static constexpr std::uint64_t QWORD_DATA1 = 0x1234567812345678;
static std::uint64_t QWORD_RESULT = HyperCPU::byteswap(QWORD_DATA1);

TEST_F(CPU_TEST, INSTR_BSWAP_R_b8) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::BSWAP);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b8 << 4 | HyperCPU::OperandTypes::R);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XLLL0);
  cpu.mem_controller->Load16(*cpu.xip + 4, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 6, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = BYTE_DATA1;

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, BYTE_RESULT);
}

TEST_F(CPU_TEST, INSTR_BSWAP_R_b16) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::BSWAP);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b16 << 4 | HyperCPU::OperandTypes::R);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XLL0);
  cpu.mem_controller->Load16(*cpu.xip + 4, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 6, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = WORD_DATA1;

  cpu.Run();

  ASSERT_EQ(*cpu.xll0, WORD_RESULT);
}

TEST_F(CPU_TEST, INSTR_BSWAP_R_b32) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::BSWAP);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b32 << 4 | HyperCPU::OperandTypes::R);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XL0);
  cpu.mem_controller->Load16(*cpu.xip + 4, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 6, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = DWORD_DATA1;

  cpu.Run();

  ASSERT_EQ(*cpu.xl0, DWORD_RESULT);
}

TEST_F(CPU_TEST, INSTR_BSWAP_R_b64) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::BSWAP);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b64 << 4 | HyperCPU::OperandTypes::R);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::X0);
  cpu.mem_controller->Load16(*cpu.xip + 4, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 6, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = QWORD_DATA1;

  cpu.Run();

  ASSERT_EQ(*cpu.x0, QWORD_RESULT);
}
