#include <gtest/gtest.h>

#include <cstring>

#include <fixtures.hpp>

TEST_F(decoder_test, HALT_INSTR_R_R_B8) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 3;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_R_R_B16) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b16 << 6) | hypercpu::operand_types::R_R);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_R_R_B32) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b32 << 6) | hypercpu::operand_types::R_R);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_R_R_B64) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b64 << 6) | hypercpu::operand_types::R_R);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_R_RM_B8) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b8 << 6) | hypercpu::operand_types::R_RM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_R_RM_B16) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b16 << 6) | hypercpu::operand_types::R_RM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_R_RM_B32) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b32 << 6) | hypercpu::operand_types::R_RM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_R_RM_B64) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b64 << 6) | hypercpu::operand_types::R_RM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_R_M_B8) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b8 << 6) | hypercpu::operand_types::R_M);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_R_M_B16) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b16 << 6) | hypercpu::operand_types::R_M);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_R_M_B32) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b32 << 6) | hypercpu::operand_types::R_M);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_R_M_B64) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b64 << 6) | hypercpu::operand_types::R_M);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_R_IMM_B8) {
  decoder.mem_controller->load16(counter, hypercpu::opcode::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b8 << 6) | hypercpu::operand_types::R_IMM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, 0x55);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_R_IMM_B16) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b16 << 6) | hypercpu::operand_types::R_IMM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load16(counter, 0x5555);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_R_IMM_B32) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b32 << 6) | hypercpu::operand_types::R_IMM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load32(counter, 0x55555555);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_R_IMM_B64) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b64 << 6) | hypercpu::operand_types::R_IMM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load64(counter, 0x5555555555555555);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_M_R_B8) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b8 << 6) | hypercpu::operand_types::M_R);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter += 8;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_M_R_B16) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b16 << 6) | hypercpu::operand_types::M_R);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter += 8;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_M_R_B32) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b32 << 6) | hypercpu::operand_types::M_R);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter += 8;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_M_R_B64) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b64 << 6) | hypercpu::operand_types::M_R);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter += 8;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_RM_R_B8) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b8 << 6) | hypercpu::operand_types::RM_R);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_RM_R_B16) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b16 << 6) | hypercpu::operand_types::RM_R);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_RM_R_B32) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b32 << 6) | hypercpu::operand_types::RM_R);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_RM_R_B64) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b64 << 6) | hypercpu::operand_types::RM_R);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_RM_M_B8) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b8 << 6) | hypercpu::operand_types::RM_M);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_RM_M_B16) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b16 << 6) | hypercpu::operand_types::RM_M);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_RM_M_B32) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b32 << 6) | hypercpu::operand_types::RM_M);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_RM_M_B64) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b64 << 6) | hypercpu::operand_types::RM_M);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load64(counter, MEM_PTR);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_RM_IMM_B8) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b8 << 6) | hypercpu::operand_types::RM_IMM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, 0x55);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_RM_IMM_B16) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b16 << 6) | hypercpu::operand_types::RM_IMM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load16(counter, 0x5555);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_RM_IMM_B32) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b32 << 6) | hypercpu::operand_types::RM_IMM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load32(counter, 0x55555555);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_RM_IMM_B64) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b64 << 6) | hypercpu::operand_types::RM_IMM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load64(counter, 0x5555555555555555);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_R_B8) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b16 << 6) | hypercpu::operand_types::R);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_R_B16) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b16 << 6) | hypercpu::operand_types::R);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_R_B32) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b32 << 6) | hypercpu::operand_types::R);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_R_B64) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b64 << 6) | hypercpu::operand_types::R);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_M_B8) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b16 << 6) | hypercpu::operand_types::M);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_M_B16) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b16 << 6) | hypercpu::operand_types::M);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_M_B32) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b32 << 6) | hypercpu::operand_types::M);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(decoder_test, HALT_INSTR_M_B64) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, (hypercpu::mode::b64 << 6) | hypercpu::operand_types::M);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}


TEST_F(decoder_test, HALT_INSTR_IMM) {
  decoder.mem_controller->load16(counter, hypercpu::HALT);
  counter += 2;
  decoder.mem_controller->load8(counter, hypercpu::operand_types::IMM);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X3);
  ++counter;
  decoder.mem_controller->load8(counter, hypercpu::registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.fetch_and_decode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}
