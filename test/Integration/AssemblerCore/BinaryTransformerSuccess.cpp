#include "core/cpu/instructions/flags.hpp"
#include "core/cpu/instructions/opcodes.hpp"
#include "core/cpu/instructions/registers.hpp"
#include "misc/bit_cast.hpp"
#include <fixtures.hpp>

TEST_F(asm_binary_transformer, ASM_R_R_b8) {
  std::string data = "mov xlll0, xlll1;";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t reg1;
  std::uint8_t reg2;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg1, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&reg2, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b8);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::R_R);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg1), hypercpu::registers::XLLL0);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg2), hypercpu::registers::XLLL1);
}

TEST_F(asm_binary_transformer, ASM_R_R_b16) {
  std::string data = "mov xll0, xll1;";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t reg1;
  std::uint8_t reg2;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg1, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&reg2, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b16);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::R_R);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg1), hypercpu::registers::XLL0);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg2), hypercpu::registers::XLL1);
}

TEST_F(asm_binary_transformer, ASM_R_R_b32) {
  std::string data = "mov xl0, xl1;";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t reg1;
  std::uint8_t reg2;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg1, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&reg2, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b32);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::R_R);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg1), hypercpu::registers::XL0);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg2), hypercpu::registers::XL1);
}

TEST_F(asm_binary_transformer, ASM_R_R_b64) {
  std::string data = "mov x0, x1;";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t reg1;
  std::uint8_t reg2;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg1, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&reg2, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b64);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::R_R);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg1), hypercpu::registers::X0);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg2), hypercpu::registers::X1);
}

TEST_F(asm_binary_transformer, ASM_R_RM_b8) {
  std::string data = "mov xlll0, [x1];";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t reg1;
  std::uint8_t reg2;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg1, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&reg2, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b8);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::R_RM);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg1), hypercpu::registers::XLLL0);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg2), hypercpu::registers::X1);
}

TEST_F(asm_binary_transformer, ASM_R_RM_b16) {
  std::string data = "mov xll0, [x1];";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t reg1;
  std::uint8_t reg2;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg1, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&reg2, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b16);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::R_RM);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg1), hypercpu::registers::XLL0);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg2), hypercpu::registers::X1);
}

TEST_F(asm_binary_transformer, ASM_R_RM_b32) {
  std::string data = "mov xl0, [x1];";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t reg1;
  std::uint8_t reg2;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg1, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&reg2, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b32);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::R_RM);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg1), hypercpu::registers::XL0);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg2), hypercpu::registers::X1);
}

TEST_F(asm_binary_transformer, ASM_R_RM_b64) {
  std::string data = "mov x0, [x1];";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t reg1;
  std::uint8_t reg2;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg1, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&reg2, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b64);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::R_RM);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg1), hypercpu::registers::X0);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg2), hypercpu::registers::X1);
}

TEST_F(asm_binary_transformer, ASM_R_M_b8) {
  std::string data = "mov xlll0, [0h];";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t addr;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&addr, binary.binary + 4, sizeof(std::uint64_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b8);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::R_M);
  EXPECT_EQ(addr, 0);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg), hypercpu::registers::XLLL0);
}

TEST_F(asm_binary_transformer, ASM_R_M_b16) {
  std::string data = "mov xll0, [0h];";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t addr;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&addr, binary.binary + 4, sizeof(std::uint64_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b16);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::R_M);
  EXPECT_EQ(addr, 0);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg), hypercpu::registers::XLL0);
}

TEST_F(asm_binary_transformer, ASM_R_M_b32) {
  std::string data = "mov xl0, [0h];";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t addr;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&addr, binary.binary + 4, sizeof(std::uint64_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b32);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::R_M);
  EXPECT_EQ(addr, 0);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg), hypercpu::registers::XL0);
}

TEST_F(asm_binary_transformer, ASM_R_M_b64) {
  std::string data = "mov x0, [0h];";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t addr;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&addr, binary.binary + 4, sizeof(std::uint64_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b64);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::R_M);
  EXPECT_EQ(addr, 0);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg), hypercpu::registers::X0);
}

TEST_F(asm_binary_transformer, ASM_R_IMM_b8) {
  std::string data = "mov xlll0, 16u;";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t num;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&num, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b8);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::R_IMM);
  EXPECT_EQ(num, 16);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg), hypercpu::registers::XLLL0);
}

TEST_F(asm_binary_transformer, ASM_R_IMM_b16) {
  std::string data = "mov xll0, 16u;";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint16_t num;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&num, binary.binary + 4, sizeof(std::uint16_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b16);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::R_IMM);
  EXPECT_EQ(num, 16);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg), hypercpu::registers::XLL0);
}

TEST_F(asm_binary_transformer, ASM_R_IMM_b32) {
  std::string data = "mov xl0, 16u;";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint32_t num;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&num, binary.binary + 4, sizeof(std::uint32_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b32);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::R_IMM);
  EXPECT_EQ(num, 16);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg), hypercpu::registers::XL0);
}

TEST_F(asm_binary_transformer, ASM_R_IMM_b64) {
  std::string data = "mov x0, 16u;";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t num;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&num, binary.binary + 4, sizeof(std::uint64_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b64);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::R_IMM);
  EXPECT_EQ(num, 16);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg), hypercpu::registers::X0);
}

TEST_F(asm_binary_transformer, ASM_RM_R_b8) {
  std::string data = "mov [x0], xlll1;";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t reg1;
  std::uint8_t reg2;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg1, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&reg2, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b8);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::RM_R);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg1), hypercpu::registers::X0);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg2), hypercpu::registers::XLLL1);
}

TEST_F(asm_binary_transformer, ASM_RM_R_b16) {
  std::string data = "mov [x0], xll1;";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t reg1;
  std::uint8_t reg2;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg1, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&reg2, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b16);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::RM_R);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg1), hypercpu::registers::X0);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg2), hypercpu::registers::XLL1);
}

TEST_F(asm_binary_transformer, ASM_RM_R_b32) {
  std::string data = "mov [x0], xl1;";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t reg1;
  std::uint8_t reg2;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg1, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&reg2, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b32);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::RM_R);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg1), hypercpu::registers::X0);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg2), hypercpu::registers::XL1);
}

TEST_F(asm_binary_transformer, ASM_RM_R_b64) {
  std::string data = "mov [x0], x1;";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t reg1;
  std::uint8_t reg2;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg1, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&reg2, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b64);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::RM_R);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg1), hypercpu::registers::X0);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg2), hypercpu::registers::X1);
}

TEST_F(asm_binary_transformer, ASM_RM_M_b8) {
  std::string data = "mov b8 ptr [x0], [0h];";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t addr;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&addr, binary.binary + 4, sizeof(std::uint64_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b8);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::RM_M);
  EXPECT_EQ(addr, 0);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg), hypercpu::registers::X0);
}

TEST_F(asm_binary_transformer, ASM_RM_M_b16) {
  std::string data = "mov b16 ptr [x0], [0h];";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t addr;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&addr, binary.binary + 4, sizeof(std::uint64_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b16);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::RM_M);
  EXPECT_EQ(addr, 0);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg), hypercpu::registers::X0);
}

TEST_F(asm_binary_transformer, ASM_RM_M_b32) {
  std::string data = "mov b32 ptr [x0], [0h];";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t addr;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&addr, binary.binary + 4, sizeof(std::uint64_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b32);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::RM_M);
  EXPECT_EQ(addr, 0);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg), hypercpu::registers::X0);
}

TEST_F(asm_binary_transformer, ASM_RM_M_b64) {
  std::string data = "mov b64 ptr [x0], [0h];";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t addr;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&addr, binary.binary + 4, sizeof(std::uint64_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b64);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::RM_M);
  EXPECT_EQ(addr, 0);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg), hypercpu::registers::X0);
}

TEST_F(asm_binary_transformer, ASM_RM_IMM_b8) {
  std::string data = "mov b8 ptr [x0], 16u;";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t num;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&num, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b8);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::RM_IMM);
  EXPECT_EQ(num, 16);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg), hypercpu::registers::X0);
}

TEST_F(asm_binary_transformer, ASM_RM_IMM_b16) {
  std::string data = "mov b16 ptr [x0], 16u;";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint16_t num;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&num, binary.binary + 4, sizeof(std::uint16_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b16);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::RM_IMM);
  EXPECT_EQ(num, 16);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg), hypercpu::registers::X0);
}

TEST_F(asm_binary_transformer, ASM_RM_IMM_b32) {
  std::string data = "mov b32 ptr [x0], 16u;";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint32_t num;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&num, binary.binary + 4, sizeof(std::uint32_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b32);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::RM_IMM);
  EXPECT_EQ(num, 16);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg), hypercpu::registers::X0);
}

TEST_F(asm_binary_transformer, ASM_RM_IMM_b64) {
  std::string data = "mov b64 ptr [x0], 16u;";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t num;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&num, binary.binary + 4, sizeof(std::uint64_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b64);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::RM_IMM);
  EXPECT_EQ(num, 16);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg), hypercpu::registers::X0);
}

TEST_F(asm_binary_transformer, ASM_M_R_b8) {
  std::string data = "mov [0h], xlll1;";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t addr;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&addr, binary.binary + 3, sizeof(std::uint64_t));
  std::memcpy(&reg,  binary.binary + 11, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b8);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::M_R);
  EXPECT_EQ(addr, 0);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg), hypercpu::registers::XLLL1);
}

TEST_F(asm_binary_transformer, ASM_M_R_b16) {
  std::string data = "mov [0h], xll1;";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t addr;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&addr, binary.binary + 3, sizeof(std::uint64_t));
  std::memcpy(&reg,  binary.binary + 11, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b16);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::M_R);
  EXPECT_EQ(addr, 0);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg), hypercpu::registers::XLL1);
}

TEST_F(asm_binary_transformer, ASM_M_R_b32) {
  std::string data = "mov [0h], xl1;";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t addr;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&addr, binary.binary + 3, sizeof(std::uint64_t));
  std::memcpy(&reg,  binary.binary + 11, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b32);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::M_R);
  EXPECT_EQ(addr, 0);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg), hypercpu::registers::XL1);
}

TEST_F(asm_binary_transformer, ASM_M_R_b64) {
  std::string data = "mov [0h], x1;";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t addr;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&addr, binary.binary + 3, sizeof(std::uint64_t));
  std::memcpy(&reg,  binary.binary + 11, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::MOV);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b64);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::M_R);
  EXPECT_EQ(addr, 0);
  EXPECT_EQ(static_cast<hypercpu::registers>(reg), hypercpu::registers::X1);
}

TEST_F(asm_binary_transformer, ASM_IMM) {
  std::string data = "call 16h;";

  auto state = compiler.transform_to_IR(data);

  auto binary = compiler.transform_to_binary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t addr;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&addr, binary.binary + 3, sizeof(std::uint64_t));

  EXPECT_EQ(static_cast<hypercpu::opcode>(opcode), hypercpu::opcode::CALL);
  
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<hypercpu::mode>((flags & 0b00110000) >> 4), hypercpu::mode::b64);
  EXPECT_EQ(static_cast<hypercpu::operand_types>(flags & 0b00001111), hypercpu::operand_types::IMM);
  EXPECT_EQ(addr, 0x16);
}