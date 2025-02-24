#include <Core/CPU/CPU.hpp>
#include <Core/CPU/ALU.hpp>

#include <Misc/deref.hpp>
#include <Misc/bit_cast.hpp>
#include <Misc/overflow.hpp>

using namespace HyperALU;

void HyperCPU::CPU::ExecAND(const IInstruction& instr, void* op1, void* op2) {
  switch (instr.m_op_types) {
    case R_R: {
      switch (instr.m_opcode_mode) {
        case b8:
          deref<std::uint8_t>(op1) = __hcpu_and(deref<std::uint8_t>(op1), HyperCPU::bit_cast_from<std::uint8_t>(op2));
          break;

        case b16:
          deref<std::uint16_t>(op1) = __hcpu_and(deref<std::uint16_t>(op1), HyperCPU::bit_cast_from<std::uint16_t>(op2));
          break;

        case b32:
          deref<std::uint32_t>(op1) = __hcpu_and(deref<std::uint32_t>(op1), HyperCPU::bit_cast_from<std::uint32_t>(op2));
          break;

        case b64:
          deref<std::uint64_t>(op1) = __hcpu_and(deref<std::uint64_t>(op1), HyperCPU::bit_cast_from<std::uint64_t>(op2));
          break;
      }
      break;
    }

    case R_RM: {
      std::uint64_t ptr = HyperCPU::bit_cast_from<std::uint64_t>(op2);

      switch (instr.m_opcode_mode) {
        case b8: {
          std::uint8_t val = mem_controller->Read8(ptr);
          deref<std::uint8_t>(op1) = __hcpu_and(deref<std::uint8_t>(op1), val);
          break;
        }

        case b16: {
          std::uint16_t val = mem_controller->Read16(ptr);
          deref<std::uint16_t>(op1) = __hcpu_and(deref<std::uint16_t>(op1), val);
          break;
        }

        case b32: {
          std::uint32_t val = mem_controller->Read32(ptr);
          deref<std::uint32_t>(op1) = __hcpu_and(deref<std::uint32_t>(op1), val);
          break;
        }

        case b64: {
          std::uint64_t val = mem_controller->Read64(ptr);
          deref<std::uint64_t>(op1) = __hcpu_and(deref<std::uint64_t>(op1), val);
          break;
        }
      }
      break;
    }

    case R_M: {
      std::uint64_t ptr = HyperCPU::bit_cast<std::uint64_t>(op2);

      switch (instr.m_opcode_mode) {
        case b8: {
          std::uint8_t val = mem_controller->Read8(ptr);
          deref<std::uint8_t>(op1) = __hcpu_and(deref<std::uint8_t>(op1), val);
          break;
        }

        case b16: {
          std::uint16_t val = mem_controller->Read16(ptr);
          deref<std::uint16_t>(op1) = __hcpu_and(deref<std::uint16_t>(op1), val);
          break;
        }

        case b32: {
          std::uint32_t val = mem_controller->Read32(ptr);
          deref<std::uint32_t>(op1) = __hcpu_and(deref<std::uint32_t>(op1), val);
          break;
        }

        case b64: {
          std::uint64_t val = mem_controller->Read64(ptr);
          deref<std::uint64_t>(op1) = __hcpu_and(deref<std::uint64_t>(op1), val);
          break;
        }
      }
      break;
    }

    case R_IMM: {
      switch (instr.m_opcode_mode) {
        case b8: {
          std::uint8_t val = HyperCPU::bit_cast<std::uint8_t>(op2);
          deref<std::uint8_t>(op1) = __hcpu_and(deref<std::uint8_t>(op1), val);
          break;
        }
          
        case b16: {
          std::uint16_t val = HyperCPU::bit_cast<std::uint16_t>(op2);
          deref<std::uint16_t>(op1) = __hcpu_and(deref<std::uint16_t>(op1), val);
          break;
        }
        
        case b32: {
          std::uint32_t val = HyperCPU::bit_cast<std::uint32_t>(op2);
          deref<std::uint32_t>(op1) = __hcpu_and(deref<std::uint32_t>(op1), val);
          break;
        }
        
        case b64: {
          std::uint64_t val = HyperCPU::bit_cast<std::uint64_t>(op2);
          deref<std::uint64_t>(op1) = __hcpu_and(deref<std::uint64_t>(op1), val);
          break;
        }
      }
      break;
    }

    default:
      break;
  }
}
