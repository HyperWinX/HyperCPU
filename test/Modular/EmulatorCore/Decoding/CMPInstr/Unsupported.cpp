#include "Core/CPU/Instructions/Opcodes.hpp"
#include <gtest/gtest.h>

#include <cstring>

#include <fixtures.hpp>

TEST_F(DECODER_TEST, CMP_INSTR_R) {
  decoder.mem_controller->Load16(counter, HyperCPU::CMP);
  counter += 2;
  decoder.mem_controller->Load8(counter, HyperCPU::OperandTypes::R);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, CMP_INSTR_M) {
  decoder.mem_controller->Load16(counter, HyperCPU::CMP);
  counter += 2;
  decoder.mem_controller->Load8(counter, HyperCPU::OperandTypes::M);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, CMP_INSTR_IMM) {
  decoder.mem_controller->Load16(counter, HyperCPU::CMP);
  counter += 2;
  decoder.mem_controller->Load8(counter, HyperCPU::OperandTypes::IMM);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, CMP_INSTR_NONE) {
  decoder.mem_controller->Load16(counter, HyperCPU::CMP);
  counter += 2;
  decoder.mem_controller->Load8(counter, HyperCPU::OperandTypes::NONE);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}