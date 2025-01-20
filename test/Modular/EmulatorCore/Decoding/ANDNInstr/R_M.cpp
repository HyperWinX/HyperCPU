#include <gtest/gtest.h>

#include <cstring>

#include <fixtures.hpp>

TEST_F(decoder_test, ANDN_INSTR_R_M_B8) {
  decoder.mem_controller->load16(counter, hypercpu::ANDN);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b8 << 6) | hypercpu::operand_types::R_M);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter = 0;
  
  hypercpu::registers reg1;
  std::size_t mem_ptr;
  hypercpu::i_instruction instr = decoder.fetch_and_decode();

  ASSERT_EQ(instr.m_opcode, hypercpu::opcode::ANDN);
  ASSERT_EQ(instr.m_opcode_mode, hypercpu::mode::b8);
  ASSERT_EQ(instr.m_op_types, hypercpu::operand_types::R_M);

  memcpy(&reg1, &instr.m_op1, sizeof(hypercpu::registers));
  memcpy(&mem_ptr, &instr.m_op2, sizeof(std::size_t));
  ASSERT_EQ(reg1, hypercpu::registers::X3);
  ASSERT_EQ(mem_ptr, MEM_PTR);
}

TEST_F(decoder_test, ANDN_INSTR_R_M_B16) {
  decoder.mem_controller->load16(counter, hypercpu::ANDN);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b16 << 6) | hypercpu::operand_types::R_M);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter = 0;
  
  hypercpu::registers reg1;
  std::size_t mem_ptr;
  hypercpu::i_instruction instr = decoder.fetch_and_decode();

  ASSERT_EQ(instr.m_opcode, hypercpu::opcode::ANDN);
  ASSERT_EQ(instr.m_opcode_mode, hypercpu::mode::b16);
  ASSERT_EQ(instr.m_op_types, hypercpu::operand_types::R_M);

  memcpy(&reg1, &instr.m_op1, sizeof(hypercpu::registers));
  memcpy(&mem_ptr, &instr.m_op2, sizeof(std::size_t));
  ASSERT_EQ(reg1, hypercpu::registers::X3);
  ASSERT_EQ(mem_ptr, MEM_PTR);
}

TEST_F(decoder_test, ANDN_INSTR_R_M_B32) {
  decoder.mem_controller->load16(counter, hypercpu::ANDN);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b32 << 6) | hypercpu::operand_types::R_M);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter = 0;
  
  hypercpu::registers reg1;
  std::size_t mem_ptr;
  hypercpu::i_instruction instr = decoder.fetch_and_decode();

  ASSERT_EQ(instr.m_opcode, hypercpu::opcode::ANDN);
  ASSERT_EQ(instr.m_opcode_mode, hypercpu::mode::b32);
  ASSERT_EQ(instr.m_op_types, hypercpu::operand_types::R_M);

  memcpy(&reg1, &instr.m_op1, sizeof(hypercpu::registers));
  memcpy(&mem_ptr, &instr.m_op2, sizeof(std::size_t));
  ASSERT_EQ(reg1, hypercpu::registers::X3);
  ASSERT_EQ(mem_ptr, MEM_PTR);
}

TEST_F(decoder_test, ANDN_INSTR_R_M_B64) {
  decoder.mem_controller->load16(counter, hypercpu::ANDN);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b64 << 6) | hypercpu::operand_types::R_M);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter = 0;
  
  hypercpu::registers reg1;
  std::size_t mem_ptr;
  hypercpu::i_instruction instr = decoder.fetch_and_decode();

  ASSERT_EQ(instr.m_opcode, hypercpu::opcode::ANDN);
  ASSERT_EQ(instr.m_opcode_mode, hypercpu::mode::b64);
  ASSERT_EQ(instr.m_op_types, hypercpu::operand_types::R_M);

  memcpy(&reg1, &instr.m_op1, sizeof(hypercpu::registers));
  memcpy(&mem_ptr, &instr.m_op2, sizeof(std::size_t));
  ASSERT_EQ(reg1, hypercpu::registers::X3);
  ASSERT_EQ(mem_ptr, MEM_PTR);
}