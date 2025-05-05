#include "pch.hpp"

#include <Core/CPU/ALU.hpp>
#include <Core/CPU/CPU.hpp>

#include <Misc/bit_cast.hpp>
#include <Misc/underflow.hpp>

using namespace HyperALU;

void HyperCPU::CPU::ExecSUB(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  switch (instr.m_op_types) {
  case R_R: {
    switch (instr.m_opcode_mode) {
    case b8:
      udf = SubtractionWillUnderflow(op1.deref<std::uint8_t>(), op2.deref<std::uint8_t>());
      op1.deref<std::uint8_t>() = __hcpu_sub(op1.deref<std::uint8_t>(), HyperCPU::bit_cast_from<std::uint8_t>(op2.ptr<std::uint8_t>()));
      break;

    case b16:
      udf = SubtractionWillUnderflow(op1.deref<std::uint16_t>(), op2.deref<std::uint16_t>());
      op1.deref<std::uint16_t>() = __hcpu_sub(op1.deref<std::uint16_t>(), HyperCPU::bit_cast_from<std::uint16_t>(op2.ptr<std::uint16_t>()));
      break;

    case b32:
      udf = SubtractionWillUnderflow(op1.deref<std::uint32_t>(), op2.deref<std::uint32_t>());
      op1.deref<std::uint32_t>() = __hcpu_sub(op1.deref<std::uint32_t>(), HyperCPU::bit_cast_from<std::uint32_t>(op2.ptr<std::uint32_t>()));
      break;

    case b64:
      udf = SubtractionWillUnderflow(op1.deref<std::uint64_t>(), op2.deref<std::uint64_t>());
      op1.deref<std::uint64_t>() = __hcpu_sub(op1.deref<std::uint64_t>(), HyperCPU::bit_cast_from<std::uint64_t>(op2.ptr<std::uint64_t>()));
      break;
    } // TODO: mark defaults as std::unreachable()
    break;
  }

  case R_RM: {
    std::uint64_t ptr = op2.deref<std::uint64_t>();

    switch (instr.m_opcode_mode) {
    case b8: {
      std::uint8_t val = mem_controller->Read8(ptr);
      udf = SubtractionWillUnderflow(op1.deref<std::uint8_t>(), val);
      op1.deref<std::uint8_t>() = __hcpu_sub(op1.deref<std::uint8_t>(), val);
      break;
    }

    case b16: {
      std::uint16_t val = mem_controller->Read16(ptr);
      udf = SubtractionWillUnderflow(op1.deref<std::uint16_t>(), val);
      op1.deref<std::uint16_t>() = __hcpu_sub(op1.deref<std::uint16_t>(), val);
      break;
    }

    case b32: {
      std::uint32_t val = mem_controller->Read32(ptr);
      udf = SubtractionWillUnderflow(op1.deref<std::uint32_t>(), val);
      op1.deref<std::uint32_t>() = __hcpu_sub(op1.deref<std::uint32_t>(), val);
      break;
    }

    case b64: {
      std::uint64_t val = mem_controller->Read64(ptr);
      udf = SubtractionWillUnderflow(op1.deref<std::uint64_t>(), val);
      op1.deref<std::uint64_t>() = __hcpu_sub(op1.deref<std::uint64_t>(), val);
      break;
    }
    }
    break;
  }

  case R_M: {
    std::uint64_t ptr = op2;

    switch (instr.m_opcode_mode) {
    case b8: {
      std::uint8_t val = mem_controller->Read8(ptr);
      udf = SubtractionWillUnderflow(op1.deref<std::uint8_t>(), val);
      op1.deref<std::uint8_t>() = __hcpu_sub(op1.deref<std::uint8_t>(), val);
      break;
    }

    case b16: {
      std::uint16_t val = mem_controller->Read16(ptr);
      udf = SubtractionWillUnderflow(op1.deref<std::uint16_t>(), val);
      op1.deref<std::uint16_t>() = __hcpu_sub(op1.deref<std::uint16_t>(), val);
      break;
    }

    case b32: {
      std::uint32_t val = mem_controller->Read32(ptr);
      udf = SubtractionWillUnderflow(op1.deref<std::uint32_t>(), val);
      op1.deref<std::uint32_t>() = __hcpu_sub(op1.deref<std::uint32_t>(), val);
      break;
    }

    case b64: {
      std::uint64_t val = mem_controller->Read64(ptr);
      udf = SubtractionWillUnderflow(op1.deref<std::uint64_t>(), val);
      op1.deref<std::uint64_t>() = __hcpu_sub(op1.deref<std::uint64_t>(), val);
      break;
    }
    }
    break;
  }

  case R_IMM: {
    switch (instr.m_opcode_mode) {
    case b8: {
      std::uint8_t val = HyperCPU::bit_cast<std::uint8_t>(op2);
      udf = SubtractionWillUnderflow(op1.deref<std::uint8_t>(), val);
      op1.deref<std::uint8_t>() = __hcpu_sub(op1.deref<std::uint8_t>(), val);
      break;
    }

    case b16: {
      std::uint16_t val = HyperCPU::bit_cast<std::uint16_t>(op2);
      udf = SubtractionWillUnderflow(op1.deref<std::uint16_t>(), val);
      op1.deref<std::uint16_t>() = __hcpu_sub(op1.deref<std::uint16_t>(), val);
      break;
    }

    case b32: {
      std::uint32_t val = HyperCPU::bit_cast<std::uint32_t>(op2);
      udf = SubtractionWillUnderflow(op1.deref<std::uint32_t>(), val);
      op1.deref<std::uint32_t>() = __hcpu_sub(op1.deref<std::uint32_t>(), val);
      break;
    }

    case b64: {
      std::uint64_t val = HyperCPU::bit_cast<std::uint64_t>(op2);
      udf = SubtractionWillUnderflow(op1.deref<std::uint64_t>(), val);
      op1.deref<std::uint64_t>() = __hcpu_sub(op1.deref<std::uint64_t>(), val);
      break;
    }
    }
    break;
  }

  default:
    break;
  }
}
