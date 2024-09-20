#include <gtest/gtest.h>

#include <cstring>

#include <fixtures.hpp>

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