#include <pch.hpp>

#include <Core/CPU/Interrupts/ReservedInterrupts.hpp>
#include <Core/CPU/Instructions/AllowedFlags.hpp>
#include <Core/CPU/Instructions/Registers.hpp>
#include <Core/CPU/Instructions/Opcodes.hpp>
#include <Core/CPU/Decoders/StdDecoder.hpp>
#include <Core/CPU/Instructions/Flags.hpp>
#include <Core/CPU/CPU.hpp>
#include <Exit.hpp>


#define dcdr_assert(expr) RaiseException((expr)); if (cpu && cpu->pending_interrupt.has_value()) return {.m_opcode = _CONT, .m_opcode_mode = b64, .m_op_types = NONE, .m_op1 = {}, .m_op2 = {}, .addr_extension_status = HyperCPU::AddrExtensionStatus::Disabled, .extension = 0}

void HyperCPU::Decoder::RaiseException(bool expr) noexcept {
  if (!(expr)) {
    if (cpu == nullptr) {
      std::cerr << "Invalid opcode!\n";
      EXIT(1);
    } else {
      cpu->TriggerInterrupt(HyperCPU::cpu_exceptions::IO);
    }
  }
}

bool HyperCPU::Decoder::CheckSupportedOperandSize(std::uint8_t byte, Mode mode) const noexcept {
  switch (mode) {
    case b8:
      return byte & 0b11000000;
    case b16:
      return byte & 0b00110000;
    case b32:
      return byte & 0b00001100;
    case b64:
      return byte & 0b00000011;
    default:
      UNREACHABLE();
  }
}

bool HyperCPU::Decoder::IsHalted() const noexcept {
  return decoder_halted;
}

HyperCPU::IInstruction HyperCPU::Decoder::FetchAndDecode() {
  std::uint16_t opcode;
  std::uint8_t flags;
  IInstruction instruction;

  // Fetch opcode and check if its valid
  opcode = mem_controller->Fetch16(*xip);
  dcdr_assert(Validator::IsValidOpcode(opcode));

  // Convert opcode
  instruction.m_opcode = static_cast<enum Opcode>(opcode);

  switch (instruction.m_opcode) {
    case IRET:
      return instruction;
    default:
      break;
  }

  // Fetch flags, set opcode Mode and verify operand types
  flags = mem_controller->Fetch8(*xip);
  instruction.m_opcode_mode = static_cast<enum Mode>((flags & 0b00110000) >> 4);

  dcdr_assert((flags & 0b00001111) <= MAX_OPERAND_TYPE);
  instruction.m_op_types = static_cast<enum OperandTypes>(flags & 0b00001111);

  instruction.addr_extension_status = static_cast<AddrExtensionStatus>((flags & 0b11000000) >> 6);
  if (instruction.addr_extension_status != AddrExtensionStatus::Disabled) {
    instruction.extension = mem_controller->Fetch8(*xip);
  }

  // Check if op Mode is valid for this opcode
  dcdr_assert(allowed_op_modes[opcode][static_cast<std::uint8_t>(instruction.m_op_types)]);
  dcdr_assert((allowed_op_modes[opcode][static_cast<std::uint8_t>(instruction.m_op_types)] == SUPPORT_ALL) ||
      CheckSupportedOperandSize(allowed_op_modes[opcode][static_cast<std::uint8_t>(instruction.m_op_types)],
      instruction.m_opcode_mode));

  switch (instruction.m_op_types) {
    case R_R:
    case RM_R:
    case R_RM: {
      std::uint8_t tmp = mem_controller->Fetch8(*xip);
      dcdr_assert(Validator::IsValidRegister(tmp));
      instruction.m_op1 = OperandContainer(HyperCPU::bit_cast<std::uint64_t>(tmp));

      tmp = mem_controller->Fetch8(*xip);
      dcdr_assert(Validator::IsValidRegister(tmp));
      instruction.m_op2 = OperandContainer(HyperCPU::bit_cast<std::uint64_t>(tmp));
      break;
    }

    case RM_M:
    case R_M: {
      std::uint8_t tmp = mem_controller->Fetch8(*xip);
      dcdr_assert(Validator::IsValidRegister(tmp));
      instruction.m_op1 = OperandContainer(HyperCPU::bit_cast<std::uint64_t>(tmp));

      instruction.m_op2 = OperandContainer{mem_controller->Fetch64(*xip)};
      break;
    }

    case RM_IMM:
    case R_IMM: {
      std::uint8_t tmp = mem_controller->Fetch8(*xip);
      dcdr_assert(Validator::IsValidRegister(tmp));
      instruction.m_op1 = OperandContainer(HyperCPU::bit_cast<std::uint64_t>(tmp));

      switch (instruction.m_opcode_mode) {
        case b8: {
          std::uint8_t vtmp = mem_controller->Fetch8(*xip);
         instruction.m_op2 = OperandContainer(HyperCPU::bit_cast<std::uint64_t>(vtmp));
          break;
        }

        case b16: {
          std::uint16_t vtmp = mem_controller->Fetch16(*xip);
          instruction.m_op2 = OperandContainer(HyperCPU::bit_cast<std::uint64_t>(vtmp));
          break;
        }

        case b32: {
          std::uint32_t vtmp = mem_controller->Fetch32(*xip);
          instruction.m_op2 = OperandContainer(HyperCPU::bit_cast<std::uint64_t>(vtmp));
          break;
        }

        case b64: {
          instruction.m_op2 = OperandContainer{mem_controller->Fetch64(*xip)};
          break;
        }
      }
      break;
    }

    case M_R: {
      instruction.m_op1 = OperandContainer{mem_controller->Fetch64(*xip)};

      std::uint8_t tmp = mem_controller->Fetch8(*xip);
      dcdr_assert(Validator::IsValidRegister(tmp));
      instruction.m_op2 = OperandContainer(HyperCPU::bit_cast<std::uint64_t>(tmp));
      break;
    }

    case R: {
      std::uint8_t tmp = mem_controller->Fetch8(*xip);
      dcdr_assert(Validator::IsValidRegister(tmp));
      instruction.m_op1 = OperandContainer(HyperCPU::bit_cast<std::uint64_t>(tmp));
      break;
    }

    case M:
      instruction.m_op1 = OperandContainer{mem_controller->Fetch64(*xip)};
      break;
    
    case IMM:
      switch (instruction.m_opcode_mode) {
        case b8: {
          std::uint8_t vtmp = mem_controller->Fetch8(*xip);
          instruction.m_op1 = OperandContainer(HyperCPU::bit_cast<std::uint64_t>(vtmp));
          break;
        }

        case b16: {
          std::uint16_t vtmp = mem_controller->Fetch16(*xip);
          instruction.m_op1 = OperandContainer(HyperCPU::bit_cast<std::uint64_t>(vtmp));
          break;
        }

        case b32: {
          std::uint32_t vtmp = mem_controller->Fetch32(*xip);
          instruction.m_op1 = OperandContainer(HyperCPU::bit_cast<std::uint64_t>(vtmp));
          break;
        }

        case b64: {
          instruction.m_op1 = OperandContainer{mem_controller->Fetch64(*xip)};
          break;
        }
    }
    break;

    case NONE: break;
  }

  return instruction;
}
