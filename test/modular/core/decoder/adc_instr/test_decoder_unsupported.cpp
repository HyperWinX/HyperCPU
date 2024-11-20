#include <gtest/gtest.h>

#include <cstring>

#include <fixtures.hpp>

TEST_F(decoder_test, ADC_INSTR_M_R_B8) {
  decoder.mem_controller->load16(counter, hypercpu::ADC);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b8 << 6) | hypercpu::operand_types::M_R);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter += 8;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid operation mode for this opcode!");
}

TEST_F(decoder_test, ADC_INSTR_M_R_B16) {
  decoder.mem_controller->load16(counter, hypercpu::ADC);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b16 << 6) | hypercpu::operand_types::M_R);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter += 8;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid operation mode for this opcode!");
}

TEST_F(decoder_test, ADC_INSTR_M_R_B32) {
  decoder.mem_controller->load16(counter, hypercpu::ADC);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b32 << 6) | hypercpu::operand_types::M_R);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter += 8;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid operation mode for this opcode!");
}

TEST_F(decoder_test, ADC_INSTR_M_R_B64) {
  decoder.mem_controller->load16(counter, hypercpu::ADC);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b64 << 6) | hypercpu::operand_types::M_R);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter += 8;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid operation mode for this opcode!");
}

TEST_F(decoder_test, ADC_INSTR_RM_R_B8) {
  decoder.mem_controller->load16(counter, hypercpu::ADC);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b8 << 6) | hypercpu::operand_types::RM_R);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid operation mode for this opcode!");
}

TEST_F(decoder_test, ADC_INSTR_RM_R_B16) {
  decoder.mem_controller->load16(counter, hypercpu::ADC);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b16 << 6) | hypercpu::operand_types::RM_R);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid operation mode for this opcode!");
}

TEST_F(decoder_test, ADC_INSTR_RM_R_B32) {
  decoder.mem_controller->load16(counter, hypercpu::ADC);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b32 << 6) | hypercpu::operand_types::RM_R);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid operation mode for this opcode!");
}

TEST_F(decoder_test, ADC_INSTR_RM_R_B64) {
  decoder.mem_controller->load16(counter, hypercpu::ADC);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b64 << 6) | hypercpu::operand_types::RM_R);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid operation mode for this opcode!");
}

TEST_F(decoder_test, ADC_INSTR_RM_M_B8) {
  decoder.mem_controller->load16(counter, hypercpu::ADC);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b8 << 6) | hypercpu::operand_types::RM_M);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid operation mode for this opcode!");
}

TEST_F(decoder_test, ADC_INSTR_RM_M_B16) {
  decoder.mem_controller->load16(counter, hypercpu::ADC);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b16 << 6) | hypercpu::operand_types::RM_M);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid operation mode for this opcode!");
}

TEST_F(decoder_test, ADC_INSTR_RM_M_B32) {
  decoder.mem_controller->load16(counter, hypercpu::ADC);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b32 << 6) | hypercpu::operand_types::RM_M);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid operation mode for this opcode!");
}

TEST_F(decoder_test, ADC_INSTR_RM_M_B64) {
  decoder.mem_controller->load16(counter, hypercpu::ADC);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b64 << 6) | hypercpu::operand_types::RM_M);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid operation mode for this opcode!");
}

TEST_F(decoder_test, ADC_INSTR_RM_IMM_B8) {
  decoder.mem_controller->load16(counter, hypercpu::ADC);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b8 << 6) | hypercpu::operand_types::RM_IMM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, 0x55);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid operation mode for this opcode!");
}

TEST_F(decoder_test, ADC_INSTR_RM_IMM_B16) {
  decoder.mem_controller->load16(counter, hypercpu::ADC);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b16 << 6) | hypercpu::operand_types::RM_IMM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load16(counter, 0x5555);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid operation mode for this opcode!");
}

TEST_F(decoder_test, ADC_INSTR_RM_IMM_B32) {
  decoder.mem_controller->load16(counter, hypercpu::ADC);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b32 << 6) | hypercpu::operand_types::RM_IMM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load32(counter, 0x55555555);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid operation mode for this opcode!");
}

TEST_F(decoder_test, ADC_INSTR_RM_IMM_B64) {
  decoder.mem_controller->load16(counter, hypercpu::ADC);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b64 << 6) | hypercpu::operand_types::RM_IMM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load64(counter, 0x5555555555555555);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid operation mode for this opcode!");
}

TEST_F(decoder_test, ADC_INSTR_R) {
  decoder.mem_controller->load16(counter, hypercpu::ADC);
  counter += 2;
  decoder.mem_controller->load8(counter, hypercpu::operand_types::R);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid operation mode for this opcode!");
}

TEST_F(decoder_test, ADC_INSTR_M) {
  decoder.mem_controller->load16(counter, hypercpu::ADC);
  counter += 2;
  decoder.mem_controller->load8(counter, hypercpu::operand_types::M);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid operation mode for this opcode!");
}

TEST_F(decoder_test, ADC_INSTR_IMM) {
  decoder.mem_controller->load16(counter, hypercpu::ADC);
  counter += 2;
  decoder.mem_controller->load8(counter, hypercpu::operand_types::IMM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid operation mode for this opcode!");
}

TEST_F(decoder_test, ADC_INSTR_NONE) {
  decoder.mem_controller->load16(counter, hypercpu::ADC);
  counter += 2;
  decoder.mem_controller->load8(counter, hypercpu::operand_types::NONE);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid operation mode for this opcode!");
}