#include <gtest/gtest.h>

#include <cstring>

#include <core/cpu/decode/i_decoder.hpp>
#include <core/cpu/instructions/flags.hpp>
#include <core/cpu/instructions/opcodes.hpp>
#include <core/cpu/instructions/registers.hpp>
#include <core/memory_controller/memory_controller_st.hpp>

#define private public
#include <core/cpu/decode/decoder.hpp>
#undef private

static constexpr std::size_t MEM_SIZE = 4096;
static constexpr std::size_t MEM_PTR = 0x0102030405060708;

class decoder_test : public ::testing::Test {
  protected:
    hypercpu::decoder decoder;
    std::size_t counter;

    decoder_test() : decoder(new hypercpu::memory_controller_st(MEM_SIZE), &counter), counter(0) {}
};

TEST_F(decoder_test, MOV_INSTR_RM_M_B8) {
  decoder.mem_controller->load16(counter, hypercpu::MOV);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b8 << 6) | hypercpu::operand_types::RM_M);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter = 0;
  
  hypercpu::registers reg1;
  std::size_t mem_ptr;
  hypercpu::i_instruction instr = decoder.fetch_and_decode();

  ASSERT_EQ(instr.m_opcode, hypercpu::opcode::MOV);
  ASSERT_EQ(instr.m_opcode_mode, hypercpu::mode::b8);
  ASSERT_EQ(instr.m_op_types, hypercpu::operand_types::RM_M);

  memcpy(&reg1, &instr.m_op1, sizeof(hypercpu::registers));
  memcpy(&mem_ptr, &instr.m_op2, sizeof(std::size_t));
  ASSERT_EQ(reg1, hypercpu::registers::X3);
  ASSERT_EQ(mem_ptr, MEM_PTR);
}

TEST_F(decoder_test, MOV_INSTR_RM_M_B16) {
  decoder.mem_controller->load16(counter, hypercpu::MOV);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b16 << 6) | hypercpu::operand_types::RM_M);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter = 0;
  
  hypercpu::registers reg1;
  std::size_t mem_ptr;
  hypercpu::i_instruction instr = decoder.fetch_and_decode();

  ASSERT_EQ(instr.m_opcode, hypercpu::opcode::MOV);
  ASSERT_EQ(instr.m_opcode_mode, hypercpu::mode::b16);
  ASSERT_EQ(instr.m_op_types, hypercpu::operand_types::RM_M);

  memcpy(&reg1, &instr.m_op1, sizeof(hypercpu::registers));
  memcpy(&mem_ptr, &instr.m_op2, sizeof(std::size_t));
  ASSERT_EQ(reg1, hypercpu::registers::X3);
  ASSERT_EQ(mem_ptr, MEM_PTR);
}

TEST_F(decoder_test, MOV_INSTR_RM_M_B32) {
  decoder.mem_controller->load16(counter, hypercpu::MOV);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b32 << 6) | hypercpu::operand_types::RM_M);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter = 0;
  
  hypercpu::registers reg1;
  std::size_t mem_ptr;
  hypercpu::i_instruction instr = decoder.fetch_and_decode();

  ASSERT_EQ(instr.m_opcode, hypercpu::opcode::MOV);
  ASSERT_EQ(instr.m_opcode_mode, hypercpu::mode::b32);
  ASSERT_EQ(instr.m_op_types, hypercpu::operand_types::RM_M);

  memcpy(&reg1, &instr.m_op1, sizeof(hypercpu::registers));
  memcpy(&mem_ptr, &instr.m_op2, sizeof(std::size_t));
  ASSERT_EQ(reg1, hypercpu::registers::X3);
  ASSERT_EQ(mem_ptr, MEM_PTR);
}

TEST_F(decoder_test, MOV_INSTR_RM_M_B64) {
  decoder.mem_controller->load16(counter, hypercpu::MOV);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b64 << 6) | hypercpu::operand_types::RM_M);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter = 0;
  
  hypercpu::registers reg1;
  std::size_t mem_ptr;
  hypercpu::i_instruction instr = decoder.fetch_and_decode();

  ASSERT_EQ(instr.m_opcode, hypercpu::opcode::MOV);
  ASSERT_EQ(instr.m_opcode_mode, hypercpu::mode::b64);
  ASSERT_EQ(instr.m_op_types, hypercpu::operand_types::RM_M);

  memcpy(&reg1, &instr.m_op1, sizeof(hypercpu::registers));
  memcpy(&mem_ptr, &instr.m_op2, sizeof(std::size_t));
  ASSERT_EQ(reg1, hypercpu::registers::X3);
  ASSERT_EQ(mem_ptr, MEM_PTR);
}