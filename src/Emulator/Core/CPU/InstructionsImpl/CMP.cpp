#include "Core/CPU/ALU.hpp"
#include <Core/CPU/CPU.hpp>

#include <Misc/bit_cast.hpp>


void HyperCPU::CPU::ExecCMP(const IInstruction& instr, void* op1, void* op2) {
  std::int8_t res = 0;
  switch (instr.m_op_types) {
    case R_R: {
      switch (instr.m_opcode_mode) {
        case b8:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint8_t>(op1), HyperCPU::bit_cast_from<std::uint8_t>(op2));
          break;

        case b16:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint16_t>(op1), HyperCPU::bit_cast_from<std::uint16_t>(op2));
          break;

        case b32:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint32_t>(op1), HyperCPU::bit_cast_from<std::uint32_t>(op2));
          break;

        case b64:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint64_t>(op1), HyperCPU::bit_cast_from<std::uint64_t>(op2));
          break;
      }
      break;
    }

    case R_RM: {
      std::uint64_t ptr;
      std::memcpy(&ptr, op2, 8);

      switch (instr.m_opcode_mode) {
        case b8:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint8_t>(op1), mem_controller->Read8(ptr));
          break;

        case b16:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint16_t>(op1), mem_controller->Read16(ptr));
          break;

        case b32:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint32_t>(op1), mem_controller->Read32(ptr));
          break;

        case b64:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint64_t>(op1), mem_controller->Read64(ptr));
          break;
      }
      break;
    }

    case R_M: {
      std::uint64_t ptr = reinterpret_cast<std::uint64_t>(op2);

      switch (instr.m_opcode_mode) {
        case b8:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint8_t>(op1), mem_controller->Read8(ptr));
          break;

        case b16:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint16_t>(op1), mem_controller->Read16(ptr));
          break;
        
        case b32:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint32_t>(op1), mem_controller->Read32(ptr));
          break;
        
        case b64:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint64_t>(op1), mem_controller->Read64(ptr));
          break;
      }
      break;
    }

    case R_IMM: {
      switch (instr.m_opcode_mode) {
        case b8:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint8_t>(op1), HyperCPU::bit_cast<std::uint8_t>(op2));
          break;
          
        case b16:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint16_t>(op1), HyperCPU::bit_cast<std::uint16_t>(op2));
          break;
        
        case b32:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint32_t>(op1), HyperCPU::bit_cast<std::uint32_t>(op2));
          break;
        
        case b64:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint64_t>(op1), HyperCPU::bit_cast<std::uint64_t>(op2));
          break;
      }
      break;
    }

    case RM_M: {
      std::size_t ptr1, ptr2 = 0;
      std::memcpy(&ptr1, op1, 8);
      ptr2 = HyperCPU::bit_cast<std::size_t>(op2);

      switch (instr.m_opcode_mode) {
        case b8:
          res = StdALU::__hcpu_cmp(mem_controller->Read8(ptr1), mem_controller->Read8(ptr2));
          break;
        
        case b16:
          res = StdALU::__hcpu_cmp(mem_controller->Read16(ptr1), mem_controller->Read16(ptr2));
          break;

        case b32:
          res = StdALU::__hcpu_cmp(mem_controller->Read32(ptr1), mem_controller->Read32(ptr2));
          break;
        
        case b64:
          res = StdALU::__hcpu_cmp(mem_controller->Read64(ptr1), mem_controller->Read64(ptr2));
          break;
      }
      break;
    }

    case RM_R: {
      std::size_t ptr = HyperCPU::bit_cast_from<std::size_t>(op1);

      switch (instr.m_opcode_mode) {
        case b8:
          res = StdALU::__hcpu_cmp(mem_controller->Read8(ptr), HyperCPU::bit_cast_from<std::uint8_t>(op2));
          break;

        case b16: 
          res = StdALU::__hcpu_cmp(mem_controller->Read16(ptr), HyperCPU::bit_cast_from<std::uint16_t>(op2));
          break;

        case b32:
          res = StdALU::__hcpu_cmp(mem_controller->Read32(ptr), HyperCPU::bit_cast_from<std::uint32_t>(op2));
          break;

        case b64:
          res = StdALU::__hcpu_cmp(mem_controller->Read64(ptr), HyperCPU::bit_cast_from<std::uint64_t>(op2));
          break;
      }
      break;
    }

    case RM_IMM: {
      std::size_t ptr = HyperCPU::bit_cast_from<std::size_t>(op1);

      switch (instr.m_opcode_mode) {
        case b8:
          res = StdALU::__hcpu_cmp(mem_controller->Read8(ptr), HyperCPU::bit_cast<std::uint8_t>(op2));
          break;
          
        case b16:
          res = StdALU::__hcpu_cmp(mem_controller->Read16(ptr), HyperCPU::bit_cast<std::uint16_t>(op2));
        break;
        
        case b32:
          res = StdALU::__hcpu_cmp(mem_controller->Read32(ptr), HyperCPU::bit_cast<std::uint32_t>(op2));
        break;
        
        case b64:
          res = StdALU::__hcpu_cmp(mem_controller->Read64(ptr), HyperCPU::bit_cast<std::uint64_t>(op2));
        break;
      }
      break;
    }

    case M_R: {
      std::size_t ptr = HyperCPU::bit_cast<std::size_t>(op1);

      switch (instr.m_opcode_mode) {
        case b8:
          res = StdALU::__hcpu_cmp(mem_controller->Read8(ptr), HyperCPU::bit_cast_from<std::uint8_t>(op2)); 
          break;

        case b16:
          res = StdALU::__hcpu_cmp(mem_controller->Read16(ptr), HyperCPU::bit_cast_from<std::uint16_t>(op2)); 
          break;

        case b32:
          res = StdALU::__hcpu_cmp(mem_controller->Read32(ptr), HyperCPU::bit_cast_from<std::uint32_t>(op2)); 
          break;

        case b64: 
          res = StdALU::__hcpu_cmp(mem_controller->Read64(ptr), HyperCPU::bit_cast_from<std::uint64_t>(op2));
          break;
      }
      break;
    }

    default:
      break;
  }

  switch (res) {
    case -1:
      zrf = 0;
      crf = 1;
      break;
    case 0:
      zrf = 1;
      crf = 0;
      break;
    case 1:
      zrf = 0;
      crf = 0;
      break;
  }
}
