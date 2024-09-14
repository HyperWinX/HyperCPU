#include "gtest/gtest.h"
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

class decoder_test : public ::testing::Test {
  protected:
    hypercpu::decoder decoder;
    std::size_t counter;

    decoder_test() : decoder(new hypercpu::memory_controller_st(MEM_SIZE), &counter), counter(0) {}
};

TEST_F(decoder_test, MOV_INSTR_R) {
  decoder.mem_controller->load16(counter, hypercpu::MOV);
  counter += 2;
  decoder.mem_controller->load8(counter, hypercpu::operand_types::R);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid operation mode for this opcode!");
}

TEST_F(decoder_test, MOV_INSTR_M) {
  decoder.mem_controller->load16(counter, hypercpu::MOV);
  counter += 2;
  decoder.mem_controller->load8(counter, hypercpu::operand_types::M);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid operation mode for this opcode!");
}

TEST_F(decoder_test, MOV_INSTR_IMM) {
  decoder.mem_controller->load16(counter, hypercpu::MOV);
  counter += 2;
  decoder.mem_controller->load8(counter, hypercpu::operand_types::IMM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid operation mode for this opcode!");
}

TEST_F(decoder_test, MOV_INSTR_NONE) {
  decoder.mem_controller->load16(counter, hypercpu::MOV);
  counter += 2;
  decoder.mem_controller->load8(counter, hypercpu::operand_types::NONE);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid operation mode for this opcode!");
}