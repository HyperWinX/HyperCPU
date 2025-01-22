#include <cassert>
#include <cstring>

#include <Core/CPU/Interrupts/ReservedInterrupts.hpp>
#include <Core/CPU/Instructions/AllowedFlags.hpp>
#include <Core/CPU/Instructions/Registers.hpp>
#include <Core/CPU/Instructions/Opcodes.hpp>
#include <Core/CPU/Instructions/Flags.hpp>
#include <Core/CPU/Decoders/IDecoder.hpp>
#include <Core/CPU/Decoders/StdDecoder.hpp>
#include <Core/CPU/Assert.hpp>
#include <Core/CPU/CPU.hpp>


#define dcdr_assert(expr) RaiseException((expr)); if (decoder_halted) return {}

void HyperCPU::Decoder::RaiseException(bool expr) noexcept {
  if (!(expr)) {
    if (cpu == nullptr) {
      std::cerr << "Invalid opcode!\n";
      std::exit(1);
    } else {
      cpu->TriggerInterrupt(HyperCPU::cpu_exceptions::IO);
      decoder_halted = true;
    }
  }
}

bool HyperCPU::Decoder::CheckSupportedOperandSize(std::uint8_t byte, std::uint8_t mask) const noexcept {
  return ((byte & 0b11) == mask || 
         ((byte >> 2) & 0b11) == mask ||
         ((byte >> 4) & 0b11) == mask ||
         ((byte >> 6) & 0b11) == mask);
}

bool HyperCPU::Decoder::IsHalted() const noexcept {
  return decoder_halted;
}

HyperCPU::IInstruction HyperCPU::Decoder::FetchAndDecode() {
  std::uint16_t opcode;
  std::uint8_t flags;
  IInstruction instruction;

  // Fetch opcode and check if its valid
  opcode = mem_controller->Fetch16(*rip);
  dcdr_assert(Validator::IsValidOpcode(opcode));

  // Convert opcode
  instruction.m_opcode = static_cast<enum Opcode>(opcode);

  // Fetch flags, set opcode Mode and verify operand types
  flags = mem_controller->Fetch8(*rip);
  instruction.m_opcode_mode = static_cast<enum Mode>((flags & 0b11000000) >> 6);

  dcdr_assert((flags & 0b00001111) <= MAX_OPERAND_TYPE);
  instruction.m_op_types = static_cast<enum OperandTypes>(flags & 0b00001111);

  // Check if op Mode is valid for this opcode
  dcdr_assert(allowed_op_modes[opcode][static_cast<std::uint8_t>(instruction.m_op_types)]);
  dcdr_assert((allowed_op_modes[opcode][static_cast<std::uint8_t>(instruction.m_op_types)] == SUPPORT_ALL) ||
      CheckSupportedOperandSize(allowed_op_modes[opcode][static_cast<std::uint8_t>(instruction.m_op_types)],
      static_cast<std::uint8_t>(instruction.m_opcode_mode)));

  switch (instruction.m_op_types) {
    case R_R:
    case RM_R:
    case R_RM: {
      std::uint8_t tmp = mem_controller->Fetch8(*rip);
      dcdr_assert(Validator::IsValidRegister(tmp));
      memcpy(&instruction.m_op1, &tmp, sizeof(std::uint8_t));

      tmp = mem_controller->Fetch8(*rip);
      dcdr_assert(Validator::IsValidRegister(tmp));
      memcpy(&instruction.m_op2, &tmp, sizeof(std::uint8_t));
      break;
    }

    case RM_M:
    case R_M: {
      std::uint8_t tmp = mem_controller->Fetch8(*rip);
      dcdr_assert(Validator::IsValidRegister(tmp));
      memcpy(&instruction.m_op1, &tmp, sizeof(std::uint8_t));

      instruction.m_op2 = mem_controller->Fetch64(*rip);
      break;
    }

    case RM_IMM:
    case R_IMM: {
      std::uint8_t tmp = mem_controller->Fetch8(*rip);
      dcdr_assert(Validator::IsValidRegister(tmp));
      memcpy(&instruction.m_op1, &tmp, sizeof(std::uint8_t));

      switch (instruction.m_opcode_mode) {
        case b8: {
          std::uint8_t vtmp = mem_controller->Fetch8(*rip);
          memcpy(&instruction.m_op2, &vtmp, sizeof(std::uint8_t));
          break;
        }

        case b16: {
          std::uint16_t vtmp = mem_controller->Fetch16(*rip);
          memcpy(&instruction.m_op2, &vtmp, sizeof(std::uint16_t));
          break;
        }

        case b32: {
          std::uint32_t vtmp = mem_controller->Fetch32(*rip);
          memcpy(&instruction.m_op2, &vtmp, sizeof(std::uint32_t));
          break;
        }

        case b64: {
          instruction.m_op2 = mem_controller->Fetch64(*rip);
          break;
        }
      }
      break;
    }

    case M_R: {
      instruction.m_op1 = mem_controller->Fetch64(*rip);

      std::uint8_t tmp = mem_controller->Fetch8(*rip);
      dcdr_assert(Validator::IsValidRegister(tmp));
      memcpy(&instruction.m_op2, &tmp, sizeof(std::uint8_t));
      break;
    }

    case R: {
      std::uint8_t tmp = mem_controller->Fetch8(*rip);
      dcdr_assert(Validator::IsValidRegister(tmp));
      memcpy(&instruction.m_op1, &tmp, sizeof(std::uint8_t));
      break;
    }

    case M:
      instruction.m_op1 = mem_controller->Fetch64(*rip);
      break;
    
    case IMM:
      switch (instruction.m_opcode_mode) {
        case b8: {
          std::uint8_t vtmp = mem_controller->Fetch8(*rip);
          memcpy(&instruction.m_op1, &vtmp, sizeof(std::uint8_t));
          break;
        }

        case b16: {
          std::uint16_t vtmp = mem_controller->Fetch16(*rip);
          memcpy(&instruction.m_op1, &vtmp, sizeof(std::uint16_t));
          break;
        }

        case b32: {
          std::uint32_t vtmp = mem_controller->Fetch32(*rip);
          memcpy(&instruction.m_op1, &vtmp, sizeof(std::uint32_t));
          break;
        }

        case b64: {
          instruction.m_op1 = mem_controller->Fetch64(*rip);
          break;
        }
    }
    break;

    case NONE: break;
  }

  return instruction;
}