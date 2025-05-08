#include "Emulator/Core/CPU/CPU.hpp"


void HyperCPU::CPU::ExecPOP(const IInstruction& instr, OperandContainer op1, OperandContainer /* op2 */) {
  switch (instr.m_op_types) {
    case OperandTypes::R:
      switch (instr.m_opcode_mode) {
        case Mode::b8: op1.deref<std::uint8_t>() = StackPop8(); break;
        case Mode::b16: op1.deref<std::uint16_t>() = StackPop16(); break;
        case Mode::b32: op1.deref<std::uint32_t>() = StackPop32(); break;
        case Mode::b64: op1.deref<std::uint64_t>() = StackPop64(); break;
        default: std::abort();
      }
      break;
    default:
        std::abort();
  }
}
