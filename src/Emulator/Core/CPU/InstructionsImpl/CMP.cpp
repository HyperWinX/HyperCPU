#include <pch.hpp>

#include <Core/CPU/CPU.hpp>
#include <Core/CPU/ALU.hpp>

#include <Misc/bit_cast.hpp>


void HyperCPU::CPU::ExecCMP(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  std::int8_t res = 0;
  switch (instr.m_op_types) {
    case R_R: {
      switch (instr.m_opcode_mode) {
        case b8:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint8_t>(op1.ptr<std::uint8_t>()), HyperCPU::bit_cast_from<std::uint8_t>(op2.ptr<std::uint8_t>()));
          break;

        case b16:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint16_t>(op1.ptr<std::uint16_t>()), HyperCPU::bit_cast_from<std::uint16_t>(op2.ptr<std::uint16_t>()));
          break;

        case b32:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint32_t>(op1.ptr<std::uint32_t>()), HyperCPU::bit_cast_from<std::uint32_t>(op2.ptr<std::uint32_t>()));
          break;

        case b64:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint64_t>(op1.ptr<std::uint64_t>()), HyperCPU::bit_cast_from<std::uint64_t>(op2.ptr<std::uint64_t>()));
          break;
      }
      break;
    }

    case R_RM: {
      std::uint64_t ptr;
      std::memcpy(&ptr, op2.ptr<void>(), 8);

      switch (instr.m_opcode_mode) {
        case b8:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint8_t>(op1.ptr<std::uint8_t>()), mem_controller->Read8(ptr));
          break;

        case b16:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint16_t>(op1.ptr<std::uint16_t>()), mem_controller->Read16(ptr));
          break;

        case b32:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint32_t>(op1.ptr<std::uint32_t>()), mem_controller->Read32(ptr));
          break;

        case b64:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint64_t>(op1.ptr<std::uint64_t>()), mem_controller->Read64(ptr));
          break;
      }
      break;
    }

    case R_M: {
      std::uint64_t ptr = op2;

      switch (instr.m_opcode_mode) {
        case b8:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint8_t>(op1.ptr<std::uint8_t>()), mem_controller->Read8(ptr));
          break;

        case b16:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint16_t>(op1.ptr<std::uint16_t>()), mem_controller->Read16(ptr));
          break;
        
        case b32:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint32_t>(op1.ptr<std::uint32_t>()), mem_controller->Read32(ptr));
          break;
        
        case b64:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint64_t>(op1.ptr<std::uint64_t>()), mem_controller->Read64(ptr));
          break;
      }
      break;
    }

    case R_IMM: {
      switch (instr.m_opcode_mode) {
        case b8:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint8_t>(op1.ptr<std::uint8_t>()), HyperCPU::bit_cast<std::uint8_t>(op2));
          break;
          
        case b16:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint16_t>(op1.ptr<std::uint16_t>()), HyperCPU::bit_cast<std::uint16_t>(op2));
          break;
        
        case b32:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint32_t>(op1.ptr<std::uint32_t>()), HyperCPU::bit_cast<std::uint32_t>(op2));
          break;
        
        case b64:
          res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint64_t>(op1.ptr<std::uint64_t>()), HyperCPU::bit_cast<std::uint64_t>(op2));
          break;
      }
      break;
    }

    case RM_M: {
      std::uint64_t ptr1, ptr2 = 0;
      std::memcpy(&ptr1, op1.ptr<void>(), 8);
      ptr2 = HyperCPU::bit_cast<std::uint64_t>(op2);

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
      std::uint64_t ptr = op1.deref<std::uint64_t>();

      switch (instr.m_opcode_mode) {
        case b8:
          res = StdALU::__hcpu_cmp(mem_controller->Read8(ptr), HyperCPU::bit_cast_from<std::uint8_t>(op2.ptr<std::uint8_t>()));
          break;

        case b16: 
          res = StdALU::__hcpu_cmp(mem_controller->Read16(ptr), HyperCPU::bit_cast_from<std::uint16_t>(op2.ptr<std::uint16_t>()));
          break;

        case b32:
          res = StdALU::__hcpu_cmp(mem_controller->Read32(ptr), HyperCPU::bit_cast_from<std::uint32_t>(op2.ptr<std::uint32_t>()));
          break;

        case b64:
          res = StdALU::__hcpu_cmp(mem_controller->Read64(ptr), HyperCPU::bit_cast_from<std::uint64_t>(op2.ptr<std::uint64_t>()));
          break;
      }
      break;
    }

    case RM_IMM: {
      std::uint64_t ptr = op1.deref<std::uint64_t>();

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
          res = StdALU::__hcpu_cmp(mem_controller->Read8(ptr), HyperCPU::bit_cast_from<std::uint8_t>(op2.ptr<std::uint8_t>())); 
          break;

        case b16:
          res = StdALU::__hcpu_cmp(mem_controller->Read16(ptr), HyperCPU::bit_cast_from<std::uint16_t>(op2.ptr<std::uint16_t>())); 
          break;

        case b32:
          res = StdALU::__hcpu_cmp(mem_controller->Read32(ptr), HyperCPU::bit_cast_from<std::uint32_t>(op2.ptr<std::uint32_t>())); 
          break;

        case b64: 
          res = StdALU::__hcpu_cmp(mem_controller->Read64(ptr), HyperCPU::bit_cast_from<std::uint64_t>(op2.ptr<std::uint64_t>()));
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
