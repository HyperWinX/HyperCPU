#include <Core/CPU/CPU.hpp>

#include <Misc/deref.hpp>
#include <Misc/bit_cast.hpp>
#include <Misc/overflow.hpp>


void HyperCPU::CPU::ExecSHFL(const IInstruction& instr, void* op1, void* op2) {
  switch (instr.m_op_types) {
    case R_R: {
      switch (instr.m_opcode_mode) {
        case b8:
          deref<std::uint8_t>(op1) <<= HyperCPU::bit_cast_from<std::uint8_t>(op2);
          break;

        case b16:
          deref<std::uint16_t>(op1) <<= HyperCPU::bit_cast_from<std::uint16_t>(op2);
          break;

        case b32:
          deref<std::uint32_t>(op1) <<= HyperCPU::bit_cast_from<std::uint32_t>(op2);
          break;

        case b64:
          deref<std::uint64_t>(op1) <<= HyperCPU::bit_cast_from<std::uint64_t>(op2);
          break;
      }
      break;
    }

    case R_IMM: {
      switch (instr.m_opcode_mode) {
        case b8: {
          std::uint8_t val = HyperCPU::bit_cast<std::uint8_t>(op2);
          deref<std::uint8_t>(op1) <<= val;
          break;
        }
          
        case b16: {
          std::uint16_t val = HyperCPU::bit_cast<std::uint16_t>(op2);
          deref<std::uint16_t>(op1) <<= val;
          break;
        }
        
        case b32: {
          std::uint32_t val = HyperCPU::bit_cast<std::uint32_t>(op2);
          deref<std::uint32_t>(op1) <<= val;
          break;
        }
        
        case b64: {
          std::uint64_t val = HyperCPU::bit_cast<std::uint64_t>(op2);
          deref<std::uint64_t>(op1) <<= val;
          break;
        }
      }
      break;
    }

    default:
      break;
  }
}
