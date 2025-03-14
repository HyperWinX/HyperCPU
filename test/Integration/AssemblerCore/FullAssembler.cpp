#include <fixtures.hpp>
#include "Main/Main.hpp"
#include "Misc/bit_cast.hpp"
#include <gtest/gtest.h>

TEST_F(FULL_ASSEMBLER, MULTUPLE_INSTRUCTIONS) {
  std::string data = "_start:\n\tmov x0, 0u1;\n\tmov x1, 0u2;\n\tadd x0, x1;";
  std::uint32_t code_size;
  auto binary = compiler.Compile(data, code_size);
  
  {
    std::ofstream file("test", std::ios::binary);

    HCAsm::WriteResultFile(HyperCPU::FileType::Binary, binary, file, code_size, 0);
  }

  std::ifstream input("test");

  HyperCPU::GenericHeader hdr;
  input.read(reinterpret_cast<char*>(&hdr), sizeof(hdr));
  ASSERT_EQ(hdr.magic, HyperCPU::magic);
  ASSERT_EQ(hdr.code_size, code_size);
  ASSERT_EQ(hdr.type, HyperCPU::FileType::Binary);
  ASSERT_EQ(hdr.version, HyperCPU::Version::PreRelease);
  ASSERT_EQ(std::filesystem::file_size("test"), code_size + sizeof(HyperCPU::GenericHeader));

  auto buf = new char[code_size];
  input.read(buf, code_size);

  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Opcode>(buf), HyperCPU::Opcode::MOV);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint8_t>(buf + 2), (HyperCPU::Mode::b64 << 4) | HyperCPU::OperandTypes::R_IMM);
  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Registers>(buf + 3), HyperCPU::Registers::X0);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint64_t>(buf + 4), 1);

  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Opcode>(buf + 12), HyperCPU::Opcode::MOV);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint8_t>(buf + 14), (HyperCPU::Mode::b64 << 4) | HyperCPU::OperandTypes::R_IMM);
  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Registers>(buf + 15), HyperCPU::Registers::X1);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint64_t>(buf + 16), 2);

  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Opcode>(buf + 24), HyperCPU::Opcode::ADD);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint8_t>(buf + 26), (HyperCPU::Mode::b64 << 4) | HyperCPU::OperandTypes::R_R);
  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Registers>(buf + 27), HyperCPU::Registers::X0);
  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Registers>(buf + 28), HyperCPU::Registers::X1);

  delete[] buf;
}

TEST_F(FULL_ASSEMBLER, IRET) {
  std::string data = "mov xbp, 0u512; mov xsp, xbp; push b64 hlt; iret; hlt: halt;";
  std::uint32_t code_size;
  auto binary = compiler.Compile(data, code_size);
  
  {
    std::ofstream file("test", std::ios::binary);

    HCAsm::WriteResultFile(HyperCPU::FileType::Binary, binary, file, code_size, 0);
  }

  std::ifstream input("test");

  HyperCPU::GenericHeader hdr;
  input.read(reinterpret_cast<char*>(&hdr), sizeof(hdr));
  ASSERT_EQ(hdr.magic, HyperCPU::magic);
  ASSERT_EQ(hdr.code_size, code_size);
  ASSERT_EQ(hdr.type, HyperCPU::FileType::Binary);
  ASSERT_EQ(hdr.version, HyperCPU::Version::PreRelease);
  ASSERT_EQ(std::filesystem::file_size("test"), code_size + sizeof(HyperCPU::GenericHeader));

  auto buf = new char[code_size];
  input.read(buf, code_size);

  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Opcode>(buf), HyperCPU::Opcode::MOV);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint8_t>(buf + 2), (HyperCPU::Mode::b64 << 4) | HyperCPU::OperandTypes::R_IMM);
<<<<<<< HEAD
  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Registers>(buf + 3), HyperCPU::Registers::X0);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint64_t>(buf + 4), 1);

  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Opcode>(buf + 12), HyperCPU::Opcode::MOV);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint8_t>(buf + 14), (HyperCPU::Mode::b64 << 4) | HyperCPU::OperandTypes::R_R);
  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Registers>(buf + 15), HyperCPU::Registers::X1);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint64_t>(buf + 16), 2);
=======
  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Registers>(buf + 3), HyperCPU::Registers::XBP);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint64_t>(buf + 4), 512);

  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Opcode>(buf + 12), HyperCPU::Opcode::MOV);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint8_t>(buf + 14), (HyperCPU::Mode::b64 << 4) | HyperCPU::OperandTypes::R_R);
  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Registers>(buf + 15), HyperCPU::Registers::XSP);
  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Registers>(buf + 16), HyperCPU::Registers::XBP);
>>>>>>> implement-push-pop

  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Opcode>(buf + 17), HyperCPU::Opcode::PUSH);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint8_t>(buf + 19), (HyperCPU::Mode::b64 << 4) | HyperCPU::OperandTypes::IMM);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint64_t>(buf + 20), 29);

  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Opcode>(buf + 28), HyperCPU::Opcode::IRET);

  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Opcode>(buf + 30), HyperCPU::Opcode::HALT);

  delete[] buf;
}
