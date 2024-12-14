#include <core/cpu/instructions/flags.hpp>

#include <fixtures.hpp>


TEST_F(operand_eval_test, PROPER_REGISTERS_EVALUATION) {
  std::size_t arg = 0;
  hypercpu::registers reg;
  
  reg = hypercpu::registers::X0;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.x0);

  reg = hypercpu::registers::X1;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.x1);

  reg = hypercpu::registers::X2;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.x2);

  reg = hypercpu::registers::X3;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.x3);

  reg = hypercpu::registers::X4;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.x4);

  reg = hypercpu::registers::X5;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.x5);

  reg = hypercpu::registers::X6;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.x6);

  reg = hypercpu::registers::X7;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.x7);

  reg = hypercpu::registers::XH0;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xh0);

  reg = hypercpu::registers::XH1;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xh1);

  reg = hypercpu::registers::XH2;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xh2);

  reg = hypercpu::registers::XH3;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xh3);

  reg = hypercpu::registers::XH4;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xh4);

  reg = hypercpu::registers::XH5;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xh5);

  reg = hypercpu::registers::XH6;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xh6);

  reg = hypercpu::registers::XH7;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xh7);

  reg = hypercpu::registers::XL0;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xl0);

  reg = hypercpu::registers::XL1;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xl1);

  reg = hypercpu::registers::XL2;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xl2);

  reg = hypercpu::registers::XL3;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xl3);

  reg = hypercpu::registers::XL4;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xl4);

  reg = hypercpu::registers::XL5;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xl5);

  reg = hypercpu::registers::XL6;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xl6);

  reg = hypercpu::registers::XL7;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xl7);

  reg = hypercpu::registers::XLL0;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xll0);

  reg = hypercpu::registers::XLL1;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xll1);

  reg = hypercpu::registers::XLL2;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xll2);

  reg = hypercpu::registers::XLL3;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xll3);

  reg = hypercpu::registers::XLLL0;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xlll0);

  reg = hypercpu::registers::XLLL1;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xlll1);

  reg = hypercpu::registers::XLLL2;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xlll2);

  reg = hypercpu::registers::XLLL3;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xlll3);

  reg = hypercpu::registers::XLLH0;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xllh0);

  reg = hypercpu::registers::XLLH1;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xllh1);

  reg = hypercpu::registers::XLLH2;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xllh2);

  reg = hypercpu::registers::XLLH3;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xllh3);

  reg = hypercpu::registers::XBP;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xbp);

  reg = hypercpu::registers::XSP;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xsp);

  reg = hypercpu::registers::XIP;
  std::memcpy(&arg, &reg, sizeof(hypercpu::registers));
  ASSERT_EQ(cpu.get_register(arg), cpu.xip);
}

TEST_F(operand_eval_test, PROPER_R_R_EVALUATION) {
  std::size_t arg1, arg2;
  hypercpu::registers reg1 = hypercpu::registers::X0, reg2 = hypercpu::registers::X1;
  std::memcpy(&arg1, &reg1, sizeof(hypercpu::registers));
  std::memcpy(&arg2, &reg2, sizeof(hypercpu::registers));

  result = cpu.get_operands(hypercpu::operand_types::R_R, 
    hypercpu::mode::b8, arg1, arg2);

  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(result.second, cpu.x1);
}

TEST_F(operand_eval_test, PROPER_R_RM_EVALUATION) {
  std::size_t arg1, arg2;
  hypercpu::registers reg1 = hypercpu::registers::X0, reg2 = hypercpu::registers::X1;
  std::memcpy(&arg1, &reg1, sizeof(hypercpu::registers));
  std::memcpy(&arg2, &reg2, sizeof(hypercpu::registers));

  result = cpu.get_operands(hypercpu::operand_types::R_RM, 
    hypercpu::mode::b8, arg1, arg2);

  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(result.second, cpu.x1);
}

TEST_F(operand_eval_test, PROPER_RM_R_EVALUATION) {
  std::size_t arg1, arg2;
  hypercpu::registers reg1 = hypercpu::registers::X0, reg2 = hypercpu::registers::X1;
  std::memcpy(&arg1, &reg1, sizeof(hypercpu::registers));
  std::memcpy(&arg2, &reg2, sizeof(hypercpu::registers));

  result = cpu.get_operands(hypercpu::operand_types::RM_R, 
    hypercpu::mode::b8, arg1, arg2);

  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(result.second, cpu.x1);
}

TEST_F(operand_eval_test, PROPER_RM_M_EVALUATION) {
  std::size_t arg1, arg2 = 1024;
  hypercpu::registers reg1 = hypercpu::registers::X0;
  std::memcpy(&arg1, &reg1, sizeof(hypercpu::registers));

  result = cpu.get_operands(hypercpu::operand_types::RM_M, 
    hypercpu::mode::b8, arg1, arg2);

  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(result.second, reinterpret_cast<void*>(arg2));
}

TEST_F(operand_eval_test, PROPER_R_M_EVALUATION) {
  std::size_t arg1, arg2 = 1024;
  hypercpu::registers reg1 = hypercpu::registers::X0;
  std::memcpy(&arg1, &reg1, sizeof(hypercpu::registers));

  result = cpu.get_operands(hypercpu::operand_types::R_M, 
    hypercpu::mode::b8, arg1, arg2);

  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(result.second, reinterpret_cast<void*>(arg2));
}

TEST_F(operand_eval_test, PROPER_RM_IMM_B8_EVALUATION) {
  std::size_t arg1, arg2, arg3 = 0xFF;
  std::uint8_t imm;
  hypercpu::registers reg1 = hypercpu::registers::X0;
  std::memcpy(&arg1, &reg1, sizeof(hypercpu::registers));
  std::memcpy(&arg2, &arg3, sizeof(std::uint8_t));

  result = cpu.get_operands(hypercpu::operand_types::RM_IMM, 
    hypercpu::mode::b8, arg1, arg2);

  std::memcpy(&imm, &result.second, sizeof(std::uint8_t));
  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(imm, arg3);
}

TEST_F(operand_eval_test, PROPER_RM_IMM_B16_EVALUATION) {
  std::size_t arg1, arg2, arg3 = 0xFFFF;
  std::uint16_t imm;
  hypercpu::registers reg1 = hypercpu::registers::X0;
  std::memcpy(&arg1, &reg1, sizeof(hypercpu::registers));
  std::memcpy(&arg2, &arg3, sizeof(std::uint16_t));

  result = cpu.get_operands(hypercpu::operand_types::RM_IMM, 
    hypercpu::mode::b16, arg1, arg2);

  std::memcpy(&imm, &result.second, sizeof(std::uint16_t));
  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(imm, arg3);
}

TEST_F(operand_eval_test, PROPER_RM_IMM_B32_EVALUATION) {
  std::size_t arg1, arg2, arg3 = 0xFFFFFFFF;
  std::uint32_t imm;
  hypercpu::registers reg1 = hypercpu::registers::X0;
  std::memcpy(&arg1, &reg1, sizeof(hypercpu::registers));
  std::memcpy(&arg2, &arg3, sizeof(std::uint32_t));

  result = cpu.get_operands(hypercpu::operand_types::RM_IMM, 
    hypercpu::mode::b32, arg1, arg2);

  std::memcpy(&imm, &result.second, sizeof(std::uint32_t));
  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(imm, arg3);
}

TEST_F(operand_eval_test, PROPER_RM_IMM_B64_EVALUATION) {
  std::size_t arg1, arg2, arg3 = 0xFFFFFFFFFFFFFFFF;
  std::uint64_t imm;
  hypercpu::registers reg1 = hypercpu::registers::X0;
  std::memcpy(&arg1, &reg1, sizeof(hypercpu::registers));
  std::memcpy(&arg2, &arg3, sizeof(std::uint64_t));

  result = cpu.get_operands(hypercpu::operand_types::RM_IMM, 
    hypercpu::mode::b64, arg1, arg2);

  std::memcpy(&imm, &result.second, sizeof(std::uint64_t));
  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(imm, arg3);
}

TEST_F(operand_eval_test, PROPER_R_IMM_B8_EVALUATION) {
  std::size_t arg1, arg2, arg3 = 0xFF;
  std::uint8_t imm;
  hypercpu::registers reg1 = hypercpu::registers::X0;
  std::memcpy(&arg1, &reg1, sizeof(hypercpu::registers));
  std::memcpy(&arg2, &arg3, sizeof(std::uint8_t));

  result = cpu.get_operands(hypercpu::operand_types::R_IMM, 
    hypercpu::mode::b8, arg1, arg2);

  std::memcpy(&imm, &result.second, sizeof(std::uint8_t));
  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(imm, arg3);
}

TEST_F(operand_eval_test, PROPER_R_IMM_B16_EVALUATION) {
  std::size_t arg1, arg2, arg3 = 0xFFFF;
  std::uint16_t imm;
  hypercpu::registers reg1 = hypercpu::registers::X0;
  std::memcpy(&arg1, &reg1, sizeof(hypercpu::registers));
  std::memcpy(&arg2, &arg3, sizeof(std::uint16_t));

  result = cpu.get_operands(hypercpu::operand_types::R_IMM, 
    hypercpu::mode::b16, arg1, arg2);

  std::memcpy(&imm, &result.second, sizeof(std::uint16_t));
  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(imm, arg3);
}

TEST_F(operand_eval_test, PROPER_R_IMM_B32_EVALUATION) {
  std::size_t arg1, arg2, arg3 = 0xFFFFFFFF;
  std::uint32_t imm;
  hypercpu::registers reg1 = hypercpu::registers::X0;
  std::memcpy(&arg1, &reg1, sizeof(hypercpu::registers));
  std::memcpy(&arg2, &arg3, sizeof(std::uint32_t));

  result = cpu.get_operands(hypercpu::operand_types::R_IMM, 
    hypercpu::mode::b32, arg1, arg2);

  std::memcpy(&imm, &result.second, sizeof(std::uint32_t));
  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(imm, arg3);
}

TEST_F(operand_eval_test, PROPER_R_IMM_B64_EVALUATION) {
  std::size_t arg1, arg2, arg3 = 0xFFFFFFFFFFFFFFFF;
  std::uint64_t imm;
  hypercpu::registers reg1 = hypercpu::registers::X0;
  std::memcpy(&arg1, &reg1, sizeof(hypercpu::registers));
  std::memcpy(&arg2, &arg3, sizeof(std::uint64_t));

  result = cpu.get_operands(hypercpu::operand_types::R_IMM, 
    hypercpu::mode::b64, arg1, arg2);

  std::memcpy(&imm, &result.second, sizeof(std::uint64_t));
  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(imm, arg3);
}

TEST_F(operand_eval_test, PROPER_M_R_EVALUATION) {
  std::size_t arg1 = 1024, arg2;
  hypercpu::registers reg2 = hypercpu::registers::X0;
  std::memcpy(&arg2, &reg2, sizeof(hypercpu::registers));

  result = cpu.get_operands(hypercpu::operand_types::M_R, 
    hypercpu::mode::b8, arg1, arg2);

  ASSERT_EQ(result.first, reinterpret_cast<void*>(arg1));
  ASSERT_EQ(result.second, cpu.x0);
}

TEST_F(operand_eval_test, PROPER_R_EVALUATION) {
  std::size_t arg1, arg2;
  hypercpu::registers reg1 = hypercpu::registers::X0;
  std::memcpy(&arg1, &reg1, sizeof(hypercpu::registers));

  result = cpu.get_operands(hypercpu::operand_types::R, 
    hypercpu::mode::b8, arg1, arg2);

  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(result.second, nullptr);
}

TEST_F(operand_eval_test, PROPER_M_EVALUATION) {
  std::size_t arg1 = 1024, arg2;

  result = cpu.get_operands(hypercpu::operand_types::M, 
    hypercpu::mode::b8, arg1, arg2);

  ASSERT_EQ(result.first, reinterpret_cast<void*>(arg1));
  ASSERT_EQ(result.second, nullptr);
}

TEST_F(operand_eval_test, PROPER_NONE_EVALUATION) {
  std::size_t arg1, arg2;

  result = cpu.get_operands(hypercpu::operand_types::NONE,
    hypercpu::mode::b8, arg1, arg2);

  ASSERT_EQ(result.first, nullptr);
  ASSERT_EQ(result.second, nullptr);
}