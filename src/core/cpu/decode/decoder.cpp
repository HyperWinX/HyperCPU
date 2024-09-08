#include <cassert>

#include <core/cpu/instructions/opcodes.hpp>
#include <core/cpu/instructions/flags.hpp>
#include <core/cpu/decode/i_decoder.hpp>
#include <core/cpu/decode/decoder.hpp>


hypercpu::i_instruction hypercpu::decoder::fetch_and_decode() {
  std::uint16_t opcode;
  std::uint8_t flags;
  i_instruction instruction;

  // Fetch opcode and check if its valid
  opcode = mem_controller->fetch16(*rip);
  assert(valid_opcode::is_value(opcode));

  // Convert opcode
  instruction.opcode = static_cast<enum opcode>(opcode);

  // Fetch flags, set opcode mode and verify operand types
  flags = mem_controller->fetch8(*rip);
  instruction.opcode_mode = static_cast<enum mode>((flags & 0b11000000) >> 6);

  assert((flags & 0b00001111) <= MAX_OPERAND_TYPE);
  instruction.op_types = static_cast<enum operand_types>(flags & 0b00001111);

  // Fetch operands
  switch (instruction.op_types) {
    case R_R:
      
  }
}