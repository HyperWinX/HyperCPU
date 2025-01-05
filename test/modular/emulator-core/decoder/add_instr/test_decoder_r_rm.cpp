#include <gtest/gtest.h>

#include <cstring>

#include <fixtures.hpp>

TEST_F(decoder_test, ADD_INSTR_R_RM_B8) {
  decoder.mem_controller->load16(counter, hypercpu::ADD);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b8 << 6) | hypercpu::operand_types::R_RM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  hypercpu::registers reg1, reg2;
  hypercpu::i_instruction instr = decoder.fetch_and_decode();

  ASSERT_EQ(instr.m_opcode, hypercpu::opcode::ADD);
  ASSERT_EQ(instr.m_opcode_mode, hypercpu::mode::b8);
  ASSERT_EQ(instr.m_op_types, hypercpu::operand_types::R_RM);

  memcpy(&reg1, &instr.m_op1, sizeof(hypercpu::registers));
  memcpy(&reg2, &instr.m_op2, sizeof(hypercpu::registers));
  ASSERT_EQ(reg1, hypercpu::registers::X3);
  ASSERT_EQ(reg2, hypercpu::registers::X7);
}

TEST_F(decoder_test, ADD_INSTR_R_RM_B16) {
  decoder.mem_controller->load16(counter, hypercpu::ADD);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b16 << 6) | hypercpu::operand_types::R_RM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  hypercpu::registers reg1, reg2;
  hypercpu::i_instruction instr = decoder.fetch_and_decode();

  ASSERT_EQ(instr.m_opcode, hypercpu::opcode::ADD);
  ASSERT_EQ(instr.m_opcode_mode, hypercpu::mode::b16);
  ASSERT_EQ(instr.m_op_types, hypercpu::operand_types::R_RM);

  memcpy(&reg1, &instr.m_op1, sizeof(hypercpu::registers));
  memcpy(&reg2, &instr.m_op2, sizeof(hypercpu::registers));
  ASSERT_EQ(reg1, hypercpu::registers::X3);
  ASSERT_EQ(reg2, hypercpu::registers::X7);
}

TEST_F(decoder_test, ADD_INSTR_R_RM_B32) {
  decoder.mem_controller->load16(counter, hypercpu::ADD);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b32 << 6) | hypercpu::operand_types::R_RM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  hypercpu::registers reg1, reg2;
  hypercpu::i_instruction instr = decoder.fetch_and_decode();

  ASSERT_EQ(instr.m_opcode, hypercpu::opcode::ADD);
  ASSERT_EQ(instr.m_opcode_mode, hypercpu::mode::b32);
  ASSERT_EQ(instr.m_op_types, hypercpu::operand_types::R_RM);

  memcpy(&reg1, &instr.m_op1, sizeof(hypercpu::registers));
  memcpy(&reg2, &instr.m_op2, sizeof(hypercpu::registers));
  ASSERT_EQ(reg1, hypercpu::registers::X3);
  ASSERT_EQ(reg2, hypercpu::registers::X7);
}

TEST_F(decoder_test, ADD_INSTR_R_RM_B64) {
  decoder.mem_controller->load16(counter, hypercpu::ADD);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b64 << 6) | hypercpu::operand_types::R_RM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  hypercpu::registers reg1, reg2;
  hypercpu::i_instruction instr = decoder.fetch_and_decode();

  ASSERT_EQ(instr.m_opcode, hypercpu::opcode::ADD);
  ASSERT_EQ(instr.m_opcode_mode, hypercpu::mode::b64);
  ASSERT_EQ(instr.m_op_types, hypercpu::operand_types::R_RM);

  memcpy(&reg1, &instr.m_op1, sizeof(hypercpu::registers));
  memcpy(&reg2, &instr.m_op2, sizeof(hypercpu::registers));
  ASSERT_EQ(reg1, hypercpu::registers::X3);
  ASSERT_EQ(reg2, hypercpu::registers::X7);
}