#include "Emulator/Core/CPU/CPU.hpp"


void HyperCPU::CPU::ExecPUSH(const IInstruction& instr, OperandContainer op1, OperandContainer /* op2 */) {
  switch (instr.m_op_types) {
    case OperandTypes::R:
      switch (instr.m_opcode_mode) {
        case HyperCPU::Mode::b8: StackPush8(HyperCPU::bit_cast_from<std::uint8_t>(op1.ptr<std::uint8_t>())); break;
        case HyperCPU::Mode::b16: StackPush16(HyperCPU::bit_cast_from<std::uint16_t>(op1.ptr<std::uint16_t>())); break;
        case HyperCPU::Mode::b32: StackPush32(HyperCPU::bit_cast_from<std::uint32_t>(op1.ptr<std::uint32_t>())); break;
        case HyperCPU::Mode::b64: StackPush64(HyperCPU::bit_cast_from<std::uint64_t>(op1.ptr<std::uint64_t>())); break;
        default: std::abort();
      }
      break;
    case OperandTypes::IMM:
      switch (instr.m_opcode_mode) {
        case HyperCPU::Mode::b8: StackPush8(HyperCPU::bit_cast<std::uint8_t>(op1)); break;
        case HyperCPU::Mode::b16: StackPush16(HyperCPU::bit_cast<std::uint16_t>(op1)); break;
        case HyperCPU::Mode::b32: StackPush32(HyperCPU::bit_cast<std::uint32_t>(op1)); break;
        case HyperCPU::Mode::b64: StackPush64(HyperCPU::bit_cast<std::uint64_t>(op1)); break;
        default: std::abort();
      }
      break;
    default:
      std::abort();
  }
}
