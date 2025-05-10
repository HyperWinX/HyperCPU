#include "pch.hpp"

#include <cstring>

#include <fixtures.hpp>

TEST_F(DECODER_TEST, BSWAP_INSTR_R_B8) {
  decoder.mem_controller->Load16(counter, HyperCPU::BSWAP);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b8 << 4) | HyperCPU::OperandTypes::R);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X7);
  counter = 0;

  HyperCPU::Registers reg1;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::BSWAP);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b8);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::R);

  memcpy(&reg1, &instr.m_op1, sizeof(HyperCPU::Registers));
  ASSERT_EQ(reg1, HyperCPU::Registers::X3);
}

TEST_F(DECODER_TEST, BSWAP_INSTR_R_B16) {
  decoder.mem_controller->Load16(counter, HyperCPU::BSWAP);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b16 << 4) | HyperCPU::OperandTypes::R);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X7);
  counter = 0;

  HyperCPU::Registers reg1;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::BSWAP);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b16);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::R);

  memcpy(&reg1, &instr.m_op1, sizeof(HyperCPU::Registers));
  ASSERT_EQ(reg1, HyperCPU::Registers::X3);
}

TEST_F(DECODER_TEST, BSWAP_INSTR_R_B32) {
  decoder.mem_controller->Load16(counter, HyperCPU::BSWAP);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b32 << 4) | HyperCPU::OperandTypes::R);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X7);
  counter = 0;

  HyperCPU::Registers reg1;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::BSWAP);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b32);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::R);

  memcpy(&reg1, &instr.m_op1, sizeof(HyperCPU::Registers));
  ASSERT_EQ(reg1, HyperCPU::Registers::X3);
}

TEST_F(DECODER_TEST, BSWAP_INSTR_R_B64) {
  decoder.mem_controller->Load16(counter, HyperCPU::BSWAP);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b64 << 4) | HyperCPU::OperandTypes::R);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X7);
  counter = 0;

  HyperCPU::Registers reg1;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::BSWAP);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b64);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::R);

  memcpy(&reg1, &instr.m_op1, sizeof(HyperCPU::Registers));
  ASSERT_EQ(reg1, HyperCPU::Registers::X3);
}
