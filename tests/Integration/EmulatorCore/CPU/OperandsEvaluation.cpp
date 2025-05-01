#include <Core/CPU/Decoders/StdDecoder.hpp>
#include <Core/CPU/Instructions/Flags.hpp>

#include <fixtures.hpp>


TEST_F(OPERAND_EVAL_TEST, PROPER_REGISTERS_EVALUATION) {
  HyperCPU::OperandContainer arg = 0;
  HyperCPU::Registers reg;
  
  reg = HyperCPU::Registers::X0;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.x0);

  reg = HyperCPU::Registers::X1;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.x1);

  reg = HyperCPU::Registers::X2;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.x2);

  reg = HyperCPU::Registers::X3;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.x3);

  reg = HyperCPU::Registers::X4;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.x4);

  reg = HyperCPU::Registers::X5;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.x5);

  reg = HyperCPU::Registers::X6;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.x6);

  reg = HyperCPU::Registers::X7;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.x7);

  reg = HyperCPU::Registers::XH0;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xh0);

  reg = HyperCPU::Registers::XH1;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xh1);

  reg = HyperCPU::Registers::XH2;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xh2);

  reg = HyperCPU::Registers::XH3;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xh3);

  reg = HyperCPU::Registers::XH4;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xh4);

  reg = HyperCPU::Registers::XH5;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xh5);

  reg = HyperCPU::Registers::XH6;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xh6);

  reg = HyperCPU::Registers::XH7;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xh7);

  reg = HyperCPU::Registers::XL0;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xl0);

  reg = HyperCPU::Registers::XL1;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xl1);

  reg = HyperCPU::Registers::XL2;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xl2);

  reg = HyperCPU::Registers::XL3;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xl3);

  reg = HyperCPU::Registers::XL4;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xl4);

  reg = HyperCPU::Registers::XL5;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xl5);

  reg = HyperCPU::Registers::XL6;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xl6);

  reg = HyperCPU::Registers::XL7;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xl7);

  reg = HyperCPU::Registers::XLL0;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xll0);

  reg = HyperCPU::Registers::XLL1;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xll1);

  reg = HyperCPU::Registers::XLL2;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xll2);

  reg = HyperCPU::Registers::XLL3;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xll3);

  reg = HyperCPU::Registers::XLLL0;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xlll0);

  reg = HyperCPU::Registers::XLLL1;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xlll1);

  reg = HyperCPU::Registers::XLLL2;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xlll2);

  reg = HyperCPU::Registers::XLLL3;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xlll3);

  reg = HyperCPU::Registers::XLLH0;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xllh0);

  reg = HyperCPU::Registers::XLLH1;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xllh1);

  reg = HyperCPU::Registers::XLLH2;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xllh2);

  reg = HyperCPU::Registers::XLLH3;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xllh3);

  reg = HyperCPU::Registers::XBP;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xbp);

  reg = HyperCPU::Registers::XSP;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xsp);

  reg = HyperCPU::Registers::XIP;
  arg = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg)};
  ASSERT_EQ(cpu.GetRegister(arg), cpu.xip);
}

TEST_F(OPERAND_EVAL_TEST, PROPER_R_R_EVALUATION) {
  HyperCPU::OperandContainer arg1, arg2;
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0, reg2 = HyperCPU::Registers::X1;
  arg1 = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg1)};
  arg2 = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg2)};

  result = cpu.GetOperands(HyperCPU::OperandTypes::R_R, 
    HyperCPU::Mode::b8, arg1, arg2);

  ASSERT_EQ(result.first.ptr<void>(), cpu.x0);
  ASSERT_EQ(result.second.ptr<void>(), cpu.x1);
}

TEST_F(OPERAND_EVAL_TEST, PROPER_R_RM_EVALUATION) {
  HyperCPU::OperandContainer arg1, arg2;
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0, reg2 = HyperCPU::Registers::X1;
  arg1 = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg1)};
  arg2 = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg2)};

  result = cpu.GetOperands(HyperCPU::OperandTypes::R_RM, 
    HyperCPU::Mode::b8, arg1, arg2);

  ASSERT_EQ(result.first.ptr<void>(), cpu.x0);
  ASSERT_EQ(result.second.ptr<void>(), cpu.x1);
}

TEST_F(OPERAND_EVAL_TEST, PROPER_RM_R_EVALUATION) {
  HyperCPU::OperandContainer arg1, arg2;
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0, reg2 = HyperCPU::Registers::X1;
  arg1 = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg1)};
  arg2 = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg2)};

  result = cpu.GetOperands(HyperCPU::OperandTypes::RM_R, 
    HyperCPU::Mode::b8, arg1, arg2);

  ASSERT_EQ(result.first.ptr<void>(), cpu.x0);
  ASSERT_EQ(result.second.ptr<void>(), cpu.x1);
}

TEST_F(OPERAND_EVAL_TEST, PROPER_RM_M_EVALUATION) {
  HyperCPU::OperandContainer arg1, arg2 = HyperCPU::OperandContainer{1024ULL};
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0;
  arg1 = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg1)};

  result = cpu.GetOperands(HyperCPU::OperandTypes::RM_M, 
    HyperCPU::Mode::b8, arg1, arg2);

  ASSERT_EQ(result.first.ptr<void>(), cpu.x0);
  ASSERT_EQ(result.second.ref(), arg2.ref());
}

TEST_F(OPERAND_EVAL_TEST, PROPER_R_M_EVALUATION) {
  HyperCPU::OperandContainer arg1, arg2 = HyperCPU::OperandContainer{1024};
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0;
  arg1 = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg1)};

  result = cpu.GetOperands(HyperCPU::OperandTypes::R_M, 
    HyperCPU::Mode::b8, arg1, arg2);

  ASSERT_EQ(result.first.ptr<void>(), cpu.x0);
  ASSERT_EQ(result.second.ref(), arg2.ref());
}

TEST_F(OPERAND_EVAL_TEST, PROPER_RM_IMM_B8_EVALUATION) {
  HyperCPU::OperandContainer arg1, arg2, arg3 = HyperCPU::OperandContainer{0xFF};
  std::uint8_t imm;
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0;
  arg1 = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg1)};
  arg2 = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(arg3)};

  result = cpu.GetOperands(HyperCPU::OperandTypes::RM_IMM, 
    HyperCPU::Mode::b8, arg1, arg2);

  std::memcpy(&imm, &result.second, sizeof(std::uint8_t));
  ASSERT_EQ(result.first.ptr<void>(), cpu.x0);
  ASSERT_EQ(imm, arg3.ref());
}

TEST_F(OPERAND_EVAL_TEST, PROPER_RM_IMM_B16_EVALUATION) {
  HyperCPU::OperandContainer arg1, arg2, arg3 = HyperCPU::OperandContainer{0xFFFF};
  std::uint16_t imm;
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0;
  arg1 = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg1)};
  arg2 = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(arg3)};
  result = cpu.GetOperands(HyperCPU::OperandTypes::RM_IMM, 
    HyperCPU::Mode::b16, arg1, arg2);

  std::memcpy(&imm, &result.second, sizeof(std::uint16_t));
  ASSERT_EQ(result.first.ptr<void>(), cpu.x0);
  ASSERT_EQ(imm, arg3.ref());
}

TEST_F(OPERAND_EVAL_TEST, PROPER_RM_IMM_B32_EVALUATION) {
  HyperCPU::OperandContainer arg1, arg2, arg3 = HyperCPU::OperandContainer{0xFFFFFFFF};
  std::uint32_t imm;
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0;
  arg1 = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg1)};
  arg2 = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(arg3)};

  result = cpu.GetOperands(HyperCPU::OperandTypes::RM_IMM, 
    HyperCPU::Mode::b32, arg1, arg2);

  std::memcpy(&imm, &result.second, sizeof(std::uint32_t));
  ASSERT_EQ(result.first.ptr<void>(), cpu.x0);
  ASSERT_EQ(imm, arg3.ref());
}

TEST_F(OPERAND_EVAL_TEST, PROPER_RM_IMM_B64_EVALUATION) {
  HyperCPU::OperandContainer arg1, arg2, arg3 = HyperCPU::OperandContainer{0xFFFFFFFFFFFFFFFF};
  std::uint64_t imm;
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0;
  arg1 = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg1)};
  arg2 = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(arg3)};

  result = cpu.GetOperands(HyperCPU::OperandTypes::RM_IMM, 
    HyperCPU::Mode::b64, arg1, arg2);

  std::memcpy(&imm, &result.second, sizeof(std::uint64_t));
  ASSERT_EQ(result.first.ptr<void>(), cpu.x0);
  ASSERT_EQ(imm, arg3.ref());
}

TEST_F(OPERAND_EVAL_TEST, PROPER_R_IMM_B8_EVALUATION) {
  HyperCPU::OperandContainer arg1, arg2, arg3 = HyperCPU::OperandContainer{0xFF};
  std::uint8_t imm;
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0;
  arg1 = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg1)};
  arg2 = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(arg3)};

  result = cpu.GetOperands(HyperCPU::OperandTypes::R_IMM, 
    HyperCPU::Mode::b8, arg1, arg2);

  std::memcpy(&imm, &result.second, sizeof(std::uint8_t));
  ASSERT_EQ(result.first.ptr<void>(), cpu.x0);
  ASSERT_EQ(imm, arg3.ref());
}

TEST_F(OPERAND_EVAL_TEST, PROPER_R_IMM_B16_EVALUATION) {
  HyperCPU::OperandContainer arg1, arg2, arg3 = HyperCPU::OperandContainer{0xFFFF};
  std::uint16_t imm;
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0;
  arg1 = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg1)};
  arg2 = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(arg3)};

  result = cpu.GetOperands(HyperCPU::OperandTypes::R_IMM, 
    HyperCPU::Mode::b16, arg1, arg2);

  std::memcpy(&imm, &result.second, sizeof(std::uint16_t));
  ASSERT_EQ(result.first.ptr<void>(), cpu.x0);
  ASSERT_EQ(imm, arg3.ref());
}

TEST_F(OPERAND_EVAL_TEST, PROPER_R_IMM_B32_EVALUATION) {
  HyperCPU::OperandContainer arg1, arg2, arg3 = HyperCPU::OperandContainer{0xFFFFFFFF};
  std::uint32_t imm;
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0;
  arg1 = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg1)};
  arg2 = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(arg3)};

  result = cpu.GetOperands(HyperCPU::OperandTypes::R_IMM, 
    HyperCPU::Mode::b32, arg1, arg2);

  std::memcpy(&imm, &result.second, sizeof(std::uint32_t));
  ASSERT_EQ(result.first.ptr<void>(), cpu.x0);
  ASSERT_EQ(imm, arg3.ref());
}

TEST_F(OPERAND_EVAL_TEST, PROPER_R_IMM_B64_EVALUATION) {
  HyperCPU::OperandContainer arg1, arg2, arg3 = HyperCPU::OperandContainer{0xFFFFFFFFFFFFFFFF};
  std::uint64_t imm;
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0;
  arg1 = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg1)};
  arg2 = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(arg3)};

  result = cpu.GetOperands(HyperCPU::OperandTypes::R_IMM, 
    HyperCPU::Mode::b64, arg1, arg2);

  std::memcpy(&imm, &result.second, sizeof(std::uint64_t));
  ASSERT_EQ(result.first.ptr<void>(), cpu.x0);
  ASSERT_EQ(imm, arg3.ref());
}

TEST_F(OPERAND_EVAL_TEST, PROPER_M_R_EVALUATION) {
  HyperCPU::OperandContainer arg1 = HyperCPU::OperandContainer{1024}, arg2;
  HyperCPU::Registers reg2 = HyperCPU::Registers::X0;
  arg2 = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg2)};

  result = cpu.GetOperands(HyperCPU::OperandTypes::M_R, 
    HyperCPU::Mode::b8, arg1, arg2);

  ASSERT_EQ(result.first.ref(), arg1.ref());
  ASSERT_EQ(result.second.ptr<void>(), cpu.x0);
}

TEST_F(OPERAND_EVAL_TEST, PROPER_R_EVALUATION) {
  HyperCPU::OperandContainer arg1, arg2;
  HyperCPU::Registers reg1 = HyperCPU::Registers::X0;
  arg1 = HyperCPU::OperandContainer{HyperCPU::bit_cast<std::uint64_t>(reg1)};

  result = cpu.GetOperands(HyperCPU::OperandTypes::R, 
    HyperCPU::Mode::b8, arg1, arg2);

  ASSERT_EQ(result.first.ptr<void>(), cpu.x0);
  ASSERT_EQ(result.second.ptr<void>(), nullptr);
}

TEST_F(OPERAND_EVAL_TEST, PROPER_M_EVALUATION) {
  HyperCPU::OperandContainer arg1 = HyperCPU::OperandContainer{1024}, arg2;

  result = cpu.GetOperands(HyperCPU::OperandTypes::M, 
    HyperCPU::Mode::b8, arg1, arg2);

  ASSERT_EQ(result.first.ref(), arg1.ref());
  ASSERT_EQ(result.second.ptr<void>(), nullptr);
}

TEST_F(OPERAND_EVAL_TEST, PROPER_NONE_EVALUATION) {
  HyperCPU::OperandContainer arg1, arg2;

  result = cpu.GetOperands(HyperCPU::OperandTypes::NONE,
    HyperCPU::Mode::b8, arg1, arg2);

  ASSERT_EQ(result.first.ptr<void>(), nullptr);
  ASSERT_EQ(result.second.ptr<void>(), nullptr);
}