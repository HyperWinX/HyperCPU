#include "Emulator/Core/CPU/ALU.hpp"
#include "Emulator/Core/CPU/CPU.hpp"

using namespace HyperALU;

void HyperCPU::CPU::ExecLODSB(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  switch (instr.m_op_types) {
  case OperandTypes::R_IMM: {
    switch (instr.m_opcode_mode) {
    case Mode::b8: {
      std::uint8_t val = HyperCPU::bit_cast<std::uint8_t>(op2);
      op1.deref<std::uint8_t>() = __hcpu_or(op1.deref<std::uint8_t>(), val);
      break;
    }

    case Mode::b16: {
      std::uint16_t val = HyperCPU::bit_cast<std::uint16_t>(op2);
      op1.deref<std::uint16_t>() = __hcpu_or(op1.deref<std::uint16_t>(), val);
      break;
    }

    case Mode::b32: {
      std::uint32_t val = HyperCPU::bit_cast<std::uint32_t>(op2);
      op1.deref<std::uint32_t>() = __hcpu_or(op1.deref<std::uint32_t>(), val);
      break;
    }

    case Mode::b64: {
      std::uint64_t val = HyperCPU::bit_cast<std::uint64_t>(op2);
      op1.deref<std::uint64_t>() = __hcpu_or(op1.deref<std::uint64_t>(), val);
      break;
    }
    }
    break;
  }

  default:
    break;
  }
}
