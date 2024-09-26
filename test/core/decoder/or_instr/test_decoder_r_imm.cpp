#include <gtest/gtest.h>

#include <cstring>

#include <fixtures.hpp>

TEST_F(decoder_test, OR_INSTR_R_IMM_B8) {
  decoder.mem_controller->load16(counter, hypercpu::opcode::OR);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b8 << 6) | hypercpu::operand_types::R_IMM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, 0x55);
  counter = 0;
  
  hypercpu::registers reg1;
  std::uint8_t data;
  hypercpu::i_instruction instr = decoder.fetch_and_decode();

  ASSERT_EQ(instr.m_opcode, hypercpu::opcode::OR);
  ASSERT_EQ(instr.m_opcode_mode, hypercpu::mode::b8);
  ASSERT_EQ(instr.m_op_types, hypercpu::operand_types::R_IMM);

  memcpy(&reg1, &instr.m_op1, sizeof(hypercpu::registers));
  memcpy(&data, &instr.m_op2, sizeof(std::uint8_t));
  ASSERT_EQ(reg1, hypercpu::registers::X3);
  ASSERT_EQ(data, 0x55);
}

TEST_F(decoder_test, OR_INSTR_R_IMM_B16) {
  decoder.mem_controller->load16(counter, hypercpu::OR);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b16 << 6) | hypercpu::operand_types::R_IMM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load16(counter, 0x5555);
  counter = 0;
  
  hypercpu::registers reg1;
  std::uint16_t data;
  hypercpu::i_instruction instr = decoder.fetch_and_decode();

  ASSERT_EQ(instr.m_opcode, hypercpu::opcode::OR);
  ASSERT_EQ(instr.m_opcode_mode, hypercpu::mode::b16);
  ASSERT_EQ(instr.m_op_types, hypercpu::operand_types::R_IMM);

  memcpy(&reg1, &instr.m_op1, sizeof(hypercpu::registers));
  memcpy(&data, &instr.m_op2, sizeof(std::uint16_t));
  ASSERT_EQ(reg1, hypercpu::registers::X3);
  ASSERT_EQ(data, 0x5555);
}

TEST_F(decoder_test, OR_INSTR_R_IMM_B32) {
  decoder.mem_controller->load16(counter, hypercpu::OR);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b32 << 6) | hypercpu::operand_types::R_IMM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load32(counter, 0x55555555);
  counter = 0;
  
  hypercpu::registers reg1;
  std::uint32_t data;
  hypercpu::i_instruction instr = decoder.fetch_and_decode();

  ASSERT_EQ(instr.m_opcode, hypercpu::opcode::OR);
  ASSERT_EQ(instr.m_opcode_mode, hypercpu::mode::b32);
  ASSERT_EQ(instr.m_op_types, hypercpu::operand_types::R_IMM);

  memcpy(&reg1, &instr.m_op1, sizeof(hypercpu::registers));
  memcpy(&data, &instr.m_op2, sizeof(std::uint32_t));
  ASSERT_EQ(reg1, hypercpu::registers::X3);
  ASSERT_EQ(data, 0x55555555);
}

TEST_F(decoder_test, OR_INSTR_R_IMM_B64) {
  decoder.mem_controller->load16(counter, hypercpu::OR);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b64 << 6) | hypercpu::operand_types::R_IMM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load64(counter, 0x5555555555555555);
  counter = 0;
  
  hypercpu::registers reg1;
  std::uint64_t data;
  hypercpu::i_instruction instr = decoder.fetch_and_decode();

  ASSERT_EQ(instr.m_opcode, hypercpu::opcode::OR);
  ASSERT_EQ(instr.m_opcode_mode, hypercpu::mode::b64);
  ASSERT_EQ(instr.m_op_types, hypercpu::operand_types::R_IMM);

  memcpy(&reg1, &instr.m_op1, sizeof(hypercpu::registers));
  memcpy(&data, &instr.m_op2, sizeof(std::uint64_t));
  ASSERT_EQ(reg1, hypercpu::registers::X3);
  ASSERT_EQ(data, 0x5555555555555555);
}