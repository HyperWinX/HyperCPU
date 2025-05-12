#include "Emulator/Core/CPU/CPU.hpp"

void HyperCPU::CPU::ExecWRITE(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  write_operation_handler& handler = write_io_handlers[*static_cast<std::uint8_t*>(op1)];

  if (handler) {
    switch (instr.m_op_types) {
    case OperandTypes::R_R:
      handler(*static_cast<std::uint8_t*>(op2));
      break;
    case OperandTypes::R_IMM:
      handler(HyperCPU::bit_cast<std::uint8_t>(op2));
      break;
    default:
      std::abort();
    }
  }
}
