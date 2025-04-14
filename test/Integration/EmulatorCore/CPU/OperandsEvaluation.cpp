#include <Core/CPU/Instructions/Flags.hpp>

#include <fixtures.hpp>


TEST_F(OPERAND_EVAL_TEST, PROPER_REGISTERS_EVALUATION) {
  std::size_t arg = 0;
  HyperCPU::Registers reg;
  
  reg = HyperCPU::Registers::X0;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.x0);

  reg = HyperCPU::Registers::X1;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.x1);

  reg = HyperCPU::Registers::X2;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.x2);

  reg = HyperCPU::Registers::X3;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.x3);

  reg = HyperCPU::Registers::X4;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.x4);

  reg = HyperCPU::Registers::X5;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.x5);

  reg = HyperCPU::Registers::X6;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.x6);

  reg = HyperCPU::Registers::X7;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.x7);

  reg = HyperCPU::Registers::XH0;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xh0);

  reg = HyperCPU::Registers::XH1;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xh1);

  reg = HyperCPU::Registers::XH2;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xh2);

  reg = HyperCPU::Registers::XH3;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xh3);

  reg = HyperCPU::Registers::XH4;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xh4);

  reg = HyperCPU::Registers::XH5;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xh5);

  reg = HyperCPU::Registers::XH6;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xh6);

  reg = HyperCPU::Registers::XH7;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xh7);

  reg = HyperCPU::Registers::XL0;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xl0);

  reg = HyperCPU::Registers::XL1;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xl1);

  reg = HyperCPU::Registers::XL2;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xl2);

  reg = HyperCPU::Registers::XL3;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xl3);

  reg = HyperCPU::Registers::XL4;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xl4);

  reg = HyperCPU::Registers::XL5;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xl5);

  reg = HyperCPU::Registers::XL6;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xl6);

  reg = HyperCPU::Registers::XL7;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xl7);

  reg = HyperCPU::Registers::XLL0;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xll0);

  reg = HyperCPU::Registers::XLL1;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xll1);

  reg = HyperCPU::Registers::XLL2;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xll2);

  reg = HyperCPU::Registers::XLL3;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xll3);

  reg = HyperCPU::Registers::XLLL0;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xlll0);

  reg = HyperCPU::Registers::XLLL1;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xlll1);

  reg = HyperCPU::Registers::XLLL2;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xlll2);

  reg = HyperCPU::Registers::XLLL3;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xlll3);

  reg = HyperCPU::Registers::XLLH0;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xllh0);

  reg = HyperCPU::Registers::XLLH1;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xllh1);

  reg = HyperCPU::Registers::XLLH2;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xllh2);

  reg = HyperCPU::Registers::XLLH3;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xllh3);

  reg = HyperCPU::Registers::XBP;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xbp);

  reg = HyperCPU::Registers::XSP;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xsp);

  reg = HyperCPU::Registers::XIP;
  std::memcpy(&arg, &reg, sizeof(HyperCPU::Registers));
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xip);
}

TEST_F(OPERAND_EVAL_TEST, PROPER_R_R_EVALUATION) {
  std::size_t arg1, arg2;
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0, reg2 = HyperCPU::Registers::X1;
  std::memcpy(&arg1, &reg1, sizeof(HyperCPU::Registers));
  std::memcpy(&arg2, &reg2, sizeof(HyperCPU::Registers));

  result = cpu.GetOperands(HyperCPU::OperandTypes::R_R, 
    HyperCPU::Mode::b8, arg1, arg2);

  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(result.second, cpu.x1);
}

TEST_F(OPERAND_EVAL_TEST, PROPER_R_RM_EVALUATION) {
  std::size_t arg1, arg2;
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0, reg2 = HyperCPU::Registers::X1;
  std::memcpy(&arg1, &reg1, sizeof(HyperCPU::Registers));
  std::memcpy(&arg2, &reg2, sizeof(HyperCPU::Registers));

  result = cpu.GetOperands(HyperCPU::OperandTypes::R_RM, 
    HyperCPU::Mode::b8, arg1, arg2);

  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(result.second, cpu.x1);
}

TEST_F(OPERAND_EVAL_TEST, PROPER_RM_R_EVALUATION) {
  std::size_t arg1, arg2;
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0, reg2 = HyperCPU::Registers::X1;
  std::memcpy(&arg1, &reg1, sizeof(HyperCPU::Registers));
  std::memcpy(&arg2, &reg2, sizeof(HyperCPU::Registers));

  result = cpu.GetOperands(HyperCPU::OperandTypes::RM_R, 
    HyperCPU::Mode::b8, arg1, arg2);

  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(result.second, cpu.x1);
}

TEST_F(OPERAND_EVAL_TEST, PROPER_RM_M_EVALUATION) {
  std::size_t arg1, arg2 = 1024;
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0;
  std::memcpy(&arg1, &reg1, sizeof(HyperCPU::Registers));

  result = cpu.GetOperands(HyperCPU::OperandTypes::RM_M, 
    HyperCPU::Mode::b8, arg1, arg2);

  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(result.second, reinterpret_cast<std::uint64_t>(arg2));
}

TEST_F(OPERAND_EVAL_TEST, PROPER_R_M_EVALUATION) {
  std::size_t arg1, arg2 = 1024;
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0;
  std::memcpy(&arg1, &reg1, sizeof(HyperCPU::Registers));

  result = cpu.GetOperands(HyperCPU::OperandTypes::R_M, 
    HyperCPU::Mode::b8, arg1, arg2);

  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(result.second, reinterpret_cast<std::uint64_t>(arg2));
}

TEST_F(OPERAND_EVAL_TEST, PROPER_RM_IMM_B8_EVALUATION) {
  std::size_t arg1, arg2, arg3 = 0xFF;
  std::uint8_t imm;
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0;
  std::memcpy(&arg1, &reg1, sizeof(HyperCPU::Registers));
  std::memcpy(&arg2, &arg3, sizeof(std::uint8_t));

  result = cpu.GetOperands(HyperCPU::OperandTypes::RM_IMM, 
    HyperCPU::Mode::b8, arg1, arg2);

  std::memcpy(&imm, &result.second, sizeof(std::uint8_t));
  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(imm, arg3);
}

TEST_F(OPERAND_EVAL_TEST, PROPER_RM_IMM_B16_EVALUATION) {
  std::size_t arg1, arg2, arg3 = 0xFFFF;
  std::uint16_t imm;
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0;
  std::memcpy(&arg1, &reg1, sizeof(HyperCPU::Registers));
  std::memcpy(&arg2, &arg3, sizeof(std::uint16_t));

  result = cpu.GetOperands(HyperCPU::OperandTypes::RM_IMM, 
    HyperCPU::Mode::b16, arg1, arg2);

  std::memcpy(&imm, &result.second, sizeof(std::uint16_t));
  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(imm, arg3);
}

TEST_F(OPERAND_EVAL_TEST, PROPER_RM_IMM_B32_EVALUATION) {
  std::size_t arg1, arg2, arg3 = 0xFFFFFFFF;
  std::uint32_t imm;
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0;
  std::memcpy(&arg1, &reg1, sizeof(HyperCPU::Registers));
  std::memcpy(&arg2, &arg3, sizeof(std::uint32_t));

  result = cpu.GetOperands(HyperCPU::OperandTypes::RM_IMM, 
    HyperCPU::Mode::b32, arg1, arg2);

  std::memcpy(&imm, &result.second, sizeof(std::uint32_t));
  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(imm, arg3);
}

TEST_F(OPERAND_EVAL_TEST, PROPER_RM_IMM_B64_EVALUATION) {
  std::size_t arg1, arg2, arg3 = 0xFFFFFFFFFFFFFFFF;
  std::uint64_t imm;
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0;
  std::memcpy(&arg1, &reg1, sizeof(HyperCPU::Registers));
  std::memcpy(&arg2, &arg3, sizeof(std::uint64_t));

  result = cpu.GetOperands(HyperCPU::OperandTypes::RM_IMM, 
    HyperCPU::Mode::b64, arg1, arg2);

  std::memcpy(&imm, &result.second, sizeof(std::uint64_t));
  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(imm, arg3);
}

TEST_F(OPERAND_EVAL_TEST, PROPER_R_IMM_B8_EVALUATION) {
  std::size_t arg1, arg2, arg3 = 0xFF;
  std::uint8_t imm;
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0;
  std::memcpy(&arg1, &reg1, sizeof(HyperCPU::Registers));
  std::memcpy(&arg2, &arg3, sizeof(std::uint8_t));

  result = cpu.GetOperands(HyperCPU::OperandTypes::R_IMM, 
    HyperCPU::Mode::b8, arg1, arg2);

  std::memcpy(&imm, &result.second, sizeof(std::uint8_t));
  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(imm, arg3);
}

TEST_F(OPERAND_EVAL_TEST, PROPER_R_IMM_B16_EVALUATION) {
  std::size_t arg1, arg2, arg3 = 0xFFFF;
  std::uint16_t imm;
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0;
  std::memcpy(&arg1, &reg1, sizeof(HyperCPU::Registers));
  std::memcpy(&arg2, &arg3, sizeof(std::uint16_t));

  result = cpu.GetOperands(HyperCPU::OperandTypes::R_IMM, 
    HyperCPU::Mode::b16, arg1, arg2);

  std::memcpy(&imm, &result.second, sizeof(std::uint16_t));
  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(imm, arg3);
}

TEST_F(OPERAND_EVAL_TEST, PROPER_R_IMM_B32_EVALUATION) {
  std::size_t arg1, arg2, arg3 = 0xFFFFFFFF;
  std::uint32_t imm;
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0;
  std::memcpy(&arg1, &reg1, sizeof(HyperCPU::Registers));
  std::memcpy(&arg2, &arg3, sizeof(std::uint32_t));

  result = cpu.GetOperands(HyperCPU::OperandTypes::R_IMM, 
    HyperCPU::Mode::b32, arg1, arg2);

  std::memcpy(&imm, &result.second, sizeof(std::uint32_t));
  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(imm, arg3);
}

TEST_F(OPERAND_EVAL_TEST, PROPER_R_IMM_B64_EVALUATION) {
  std::size_t arg1, arg2, arg3 = 0xFFFFFFFFFFFFFFFF;
  std::uint64_t imm;
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0;
  std::memcpy(&arg1, &reg1, sizeof(HyperCPU::Registers));
  std::memcpy(&arg2, &arg3, sizeof(std::uint64_t));

  result = cpu.GetOperands(HyperCPU::OperandTypes::R_IMM, 
    HyperCPU::Mode::b64, arg1, arg2);

  std::memcpy(&imm, &result.second, sizeof(std::uint64_t));
  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(imm, arg3);
}

TEST_F(OPERAND_EVAL_TEST, PROPER_M_R_EVALUATION) {
  std::size_t arg1 = 1024, arg2;
  HyperCPU::Registers reg2 = HyperCPU::Registers::X0;
  std::memcpy(&arg2, &reg2, sizeof(HyperCPU::Registers));

  result = cpu.GetOperands(HyperCPU::OperandTypes::M_R, 
    HyperCPU::Mode::b8, arg1, arg2);

  ASSERT_EQ(result.first, reinterpret_cast<std::uint64_t>(arg1));
  ASSERT_EQ(result.second, cpu.x0);
}

TEST_F(OPERAND_EVAL_TEST, PROPER_R_EVALUATION) {
  std::size_t arg1, arg2;
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0;
  std::memcpy(&arg1, &reg1, sizeof(HyperCPU::Registers));

  result = cpu.GetOperands(HyperCPU::OperandTypes::R, 
    HyperCPU::Mode::b8, arg1, arg2);

  ASSERT_EQ(result.first, cpu.x0);
  ASSERT_EQ(result.second, nullptr);
}

TEST_F(OPERAND_EVAL_TEST, PROPER_M_EVALUATION) {
  std::size_t arg1 = 1024, arg2;

  result = cpu.GetOperands(HyperCPU::OperandTypes::M, 
    HyperCPU::Mode::b8, arg1, arg2);

  ASSERT_EQ(result.first, reinterpret_cast<std::uint64_t>(arg1));
  ASSERT_EQ(result.second, nullptr);
}

TEST_F(OPERAND_EVAL_TEST, PROPER_NONE_EVALUATION) {
  std::size_t arg1, arg2;

  result = cpu.GetOperands(HyperCPU::OperandTypes::NONE,
    HyperCPU::Mode::b8, arg1, arg2);

  ASSERT_EQ(result.first, nullptr);
  ASSERT_EQ(result.second, nullptr);
}