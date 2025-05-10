#include "Emulator/Core/CPU/CPU.hpp"

void HyperCPU::CPU::ExecLOIVT(const IInstruction& instr, OperandContainer op1, OperandContainer /* op2 */) {
  switch (instr.m_op_types) {
  case OperandTypes::IMM:
    *xivt = HyperCPU::bit_cast<std::uint64_t>(op1);
    break;
  case OperandTypes::R:
    *xivt = HyperCPU::bit_cast_from<std::uint64_t>(op1.ptr<std::uint64_t>());
    break;
  default:
    std::abort();
  }
  ivt_initialized = true;
}
