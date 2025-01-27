#include <fixtures.hpp>

TEST_F(DECODER_TEST, READ_INSTR_IMM) {
  decoder.mem_controller->Load16(counter, HyperCPU::WRITE);
  counter += 2;
  decoder.mem_controller->Load8(counter, HyperCPU::OperandTypes::IMM);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X7);
  counter = 0;
  
  ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}
