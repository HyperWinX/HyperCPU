#include <gtest/gtest.h>

#include <cstring>

#include <fixtures.hpp>

TEST_F(decoder_test, CALL_INSTR_R) {
  decoder.mem_controller->load16(counter, hypercpu::opcode::CALL);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b64 << 6) | hypercpu::operand_types::R);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  hypercpu::i_instruction instr = decoder.fetch_and_decode();

  ASSERT_EQ(instr.m_opcode, hypercpu::opcode::CALL);
  ASSERT_EQ(instr.m_opcode_mode, hypercpu::mode::b64);
  ASSERT_EQ(instr.m_op_types, hypercpu::operand_types::R);
}