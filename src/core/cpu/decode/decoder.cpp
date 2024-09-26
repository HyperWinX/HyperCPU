#include <cassert>
#include <cstring>

#include <core/cpu/instructions/allowed_modes.hpp>
#include <core/cpu/instructions/registers.hpp>
#include <core/cpu/instructions/opcodes.hpp>
#include <core/cpu/instructions/flags.hpp>
#include <core/cpu/decode/i_decoder.hpp>
#include <core/cpu/decode/decoder.hpp>
#include <core/cpu/assert.hpp>

bool hypercpu::decoder::check_supported_operand_size(std::uint8_t byte, std::uint8_t mask) {
  return ((byte & 0b11) == mask || 
         ((byte >> 2) & 0b11) == mask ||
         ((byte >> 4) & 0b11) == mask ||
         ((byte >> 6) & 0b11) == mask);
}

hypercpu::i_instruction hypercpu::decoder::fetch_and_decode() {
  std::uint16_t opcode;
  std::uint8_t flags;
  i_instruction instruction;

  // Fetch opcode and check if its valid
  opcode = mem_controller->fetch16(rip);
  h_assert(validator::is_valid_opcode(opcode), "Invalid opcode!");

  // Convert opcode
  instruction.m_opcode = static_cast<enum opcode>(opcode);

  // Fetch flags, set opcode mode and verify operand types
  flags = mem_controller->fetch8(rip);
  instruction.m_opcode_mode = static_cast<enum mode>((flags & 0b11000000) >> 6);

  h_assert((flags & 0b00001111) <= MAX_OPERAND_TYPE, "Invalid operand types!");
  instruction.m_op_types = static_cast<enum operand_types>(flags & 0b00001111);

  // Check if op mode is valid for this opcode
  h_assert(allowed_op_modes[opcode][static_cast<std::uint8_t>(instruction.m_op_types)], "Invalid operation mode for this opcode!");
  h_assert((allowed_op_modes[opcode][static_cast<std::uint8_t>(instruction.m_op_types)] == SUPPORT_ALL) ||
      check_supported_operand_size(allowed_op_modes[opcode][static_cast<std::uint8_t>(instruction.m_op_types)],
      static_cast<std::uint8_t>(instruction.m_opcode_mode)), "Unsupported operand size!");

  switch (instruction.m_op_types) {
    case R_R:
    case RM_R:
    case R_RM: {
      std::uint8_t tmp = mem_controller->fetch8(rip);
      h_assert(validator::is_valid_register(tmp), "Invalid register!");
      memcpy(&instruction.m_op1, &tmp, sizeof(std::uint8_t));

      tmp = mem_controller->fetch8(rip);
      h_assert(validator::is_valid_register(tmp), "Invalid register!");
      memcpy(&instruction.m_op2, &tmp, sizeof(std::uint8_t));
      break;
    }

    case RM_M:
    case R_M: {
      std::uint8_t tmp = mem_controller->fetch8(rip);
      h_assert(validator::is_valid_register(tmp), "Invalid register!");
      memcpy(&instruction.m_op1, &tmp, sizeof(std::uint8_t));

      instruction.m_op2 = mem_controller->fetch64(rip);
      break;
    }

    case RM_IMM:
    case R_IMM: {
      std::uint8_t tmp = mem_controller->fetch8(rip);
      h_assert(validator::is_valid_register(tmp), "Invalid register!");
      memcpy(&instruction.m_op1, &tmp, sizeof(std::uint8_t));

      switch (instruction.m_opcode_mode) {
        case b8: {
          std::uint8_t vtmp = mem_controller->fetch8(rip);
          memcpy(&instruction.m_op2, &vtmp, sizeof(std::uint8_t));
          break;
        }

        case b16: {
          std::uint16_t vtmp = mem_controller->fetch16(rip);
          memcpy(&instruction.m_op2, &vtmp, sizeof(std::uint16_t));
          break;
        }

        case b32: {
          std::uint32_t vtmp = mem_controller->fetch32(rip);
          memcpy(&instruction.m_op2, &vtmp, sizeof(std::uint32_t));
          break;
        }

        case b64: {
          instruction.m_op2 = mem_controller->fetch64(rip);
          break;
        }
      }
      break;
    }

    case M_R: {
      instruction.m_op1 = mem_controller->fetch64(rip);

      std::uint8_t tmp = mem_controller->fetch8(rip);
      h_assert(validator::is_valid_register(tmp), "Invalid register!");
      memcpy(&instruction.m_op2, &tmp, sizeof(std::uint8_t));
      break;
    }

    case R: {
      std::uint8_t tmp = mem_controller->fetch8(rip);
      h_assert(validator::is_valid_register(tmp), "Invalid register!");
      memcpy(&instruction.m_op1, &tmp, sizeof(std::uint8_t));
      break;
    }

    case M:
      instruction.m_op1 = mem_controller->fetch64(rip);
      break;
    
    case IMM:
      switch (instruction.m_opcode_mode) {
        case b8: {
          std::uint8_t vtmp = mem_controller->fetch8(rip);
          memcpy(&instruction.m_op1, &vtmp, sizeof(std::uint8_t));
          break;
        }

        case b16: {
          std::uint16_t vtmp = mem_controller->fetch16(rip);
          memcpy(&instruction.m_op1, &vtmp, sizeof(std::uint16_t));
          break;
        }

        case b32: {
          std::uint32_t vtmp = mem_controller->fetch32(rip);
          memcpy(&instruction.m_op1, &vtmp, sizeof(std::uint32_t));
          break;
        }

        case b64: {
          instruction.m_op1 = mem_controller->fetch64(rip);
          break;
        }
    }
    break;

    case NONE: break;
  }

  return instruction;
}