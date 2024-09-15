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
static constexpr std::uint64_t MEM_PTR = 0x0102030405060708;

class decoder_test : public ::testing::Test {
  protected:
    hypercpu::decoder decoder;
    std::size_t counter;

    decoder_test() : decoder(new hypercpu::memory_controller_st(MEM_SIZE), &counter), counter(0) {}
};

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