#include "Core/CPU/Instructions/Registers.hpp"
#include <fixtures.hpp>

TEST_F(DECODER_TEST, WRITE_INSTR_R_R_B8) {
  decoder.mem_controller->Load16(counter, HyperCPU::Opcode::WRITE);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b8 << 4) | HyperCPU::OperandTypes::R_R);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X1);
  counter = 0;
  
  HyperCPU::Registers reg1;
  HyperCPU::Registers reg2
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::WRITE);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b8);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::R_R);

  memcpy(&reg1, &instr.m_op1, sizeof(HyperCPU::Registers));
  memcpy(&reg2, &instr.m_op2, sizeof(HyperCPU::Registers));
  ASSERT_EQ(reg1, HyperCPU::Registers::X3);
  ASSERT_EQ(data, HyperCPU::Registers::X1);
}

