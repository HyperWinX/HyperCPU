#include <gtest/gtest.h>

#include <cstring>

#include <fixtures.hpp>

TEST_F(decoder_test, MOV_INSTR_M_R_B8) {
  decoder.mem_controller->load16(counter, hypercpu::MOV);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b8 << 6) | hypercpu::operand_types::M_R);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter += 8;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  hypercpu::registers reg2;
  std::size_t mem_ptr;
  hypercpu::i_instruction instr = decoder.fetch_and_decode();

  ASSERT_EQ(instr.m_opcode, hypercpu::opcode::MOV);
  ASSERT_EQ(instr.m_opcode_mode, hypercpu::mode::b8);
  ASSERT_EQ(instr.m_op_types, hypercpu::operand_types::M_R);

  memcpy(&mem_ptr, &instr.m_op1, sizeof(std::size_t));
  memcpy(&reg2, &instr.m_op2, sizeof(hypercpu::registers));
  ASSERT_EQ(mem_ptr, MEM_PTR);
  ASSERT_EQ(reg2, hypercpu::registers::X7);
}

TEST_F(decoder_test, MOV_INSTR_M_R_B16) {
  decoder.mem_controller->load16(counter, hypercpu::MOV);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b16 << 6) | hypercpu::operand_types::M_R);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter += 8;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  hypercpu::registers reg2;
  std::size_t mem_ptr;
  hypercpu::i_instruction instr = decoder.fetch_and_decode();

  ASSERT_EQ(instr.m_opcode, hypercpu::opcode::MOV);
  ASSERT_EQ(instr.m_opcode_mode, hypercpu::mode::b16);
  ASSERT_EQ(instr.m_op_types, hypercpu::operand_types::M_R);

  memcpy(&mem_ptr, &instr.m_op1, sizeof(std::size_t));
  memcpy(&reg2, &instr.m_op2, sizeof(hypercpu::registers));
  ASSERT_EQ(mem_ptr, MEM_PTR);
  ASSERT_EQ(reg2, hypercpu::registers::X7);
}

TEST_F(decoder_test, MOV_INSTR_M_R_B32) {
  decoder.mem_controller->load16(counter, hypercpu::MOV);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b32 << 6) | hypercpu::operand_types::M_R);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter += 8;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  hypercpu::registers reg2;
  std::size_t mem_ptr;
  hypercpu::i_instruction instr = decoder.fetch_and_decode();

  ASSERT_EQ(instr.m_opcode, hypercpu::opcode::MOV);
  ASSERT_EQ(instr.m_opcode_mode, hypercpu::mode::b32);
  ASSERT_EQ(instr.m_op_types, hypercpu::operand_types::M_R);

  memcpy(&mem_ptr, &instr.m_op1, sizeof(std::size_t));
  memcpy(&reg2, &instr.m_op2, sizeof(hypercpu::registers));
  ASSERT_EQ(mem_ptr, MEM_PTR);
  ASSERT_EQ(reg2, hypercpu::registers::X7);
}

TEST_F(decoder_test, MOV_INSTR_M_R_B64) {
  decoder.mem_controller->load16(counter, hypercpu::MOV);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b64 << 6) | hypercpu::operand_types::M_R);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter += 8;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  hypercpu::registers reg2;
  std::size_t mem_ptr;
  hypercpu::i_instruction instr = decoder.fetch_and_decode();

  ASSERT_EQ(instr.m_opcode, hypercpu::opcode::MOV);
  ASSERT_EQ(instr.m_opcode_mode, hypercpu::mode::b64);
  ASSERT_EQ(instr.m_op_types, hypercpu::operand_types::M_R);

  memcpy(&mem_ptr, &instr.m_op1, sizeof(std::size_t));
  memcpy(&reg2, &instr.m_op2, sizeof(hypercpu::registers));
  ASSERT_EQ(mem_ptr, MEM_PTR);
  ASSERT_EQ(reg2, hypercpu::registers::X7);
}