#include <gtest/gtest.h>

#include <cstring>

#include <fixtures.hpp>

TEST_F(decoder_test, CALL_INSTR_M) {
  decoder.mem_controller->load16(counter, hypercpu::opcode::CALL);
  counter += 2;
  decoder.mem_controller->load8(counter, hypercpu::operand_types::M);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter = 0;
  
  std::uint64_t mem_ptr;
  hypercpu::i_instruction instr = decoder.fetch_and_decode();

  ASSERT_EQ(instr.m_opcode, hypercpu::opcode::CALL);
  ASSERT_EQ(instr.m_op_types, hypercpu::operand_types::M);

  memcpy(&mem_ptr, &instr.m_op1, sizeof(std::uint64_t));
  ASSERT_EQ(mem_ptr, MEM_PTR);
}