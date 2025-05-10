#include "Emulator/Core/CPU/CPU.hpp"

void HyperCPU::CPU::ExecREAD(const IInstruction& instr, OperandContainer op1, OperandContainer /* op2 */) {
  read_operation_handler* handler = nullptr;
  switch (instr.m_op_types) {
  case OperandTypes::IMM:
    handler = &read_io_handlers[HyperCPU::bit_cast<std::uint8_t>(op1)];
    break;
  case OperandTypes::R:
    handler = &read_io_handlers[HyperCPU::bit_cast_from<std::uint8_t>(op1.ptr<std::uint8_t>())];
    break;
  default:
    std::abort();
  }

  if (handler) {
    *xlll0 = (*handler)();
  }
}
