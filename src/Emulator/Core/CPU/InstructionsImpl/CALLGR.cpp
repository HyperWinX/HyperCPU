#include "Emulator/Core/CPU/CPU.hpp"

#include "Emulator/Misc/bit_cast.hpp"

void HyperCPU::CPU::ExecCALLGR(const IInstruction& instr, OperandContainer op1, OperandContainer /* op2 */) {
  if (!(!zrf && !crf)) {
    return;
  }

  switch (instr.m_op_types) { // Placeholders
  case OperandTypes::R:
    StackPush64(*xip);
    *xip = op1.deref<std::uint64_t>();
    break;
  case OperandTypes::IMM:
    StackPush64(*xip);
    *xip = HyperCPU::bit_cast<std::uint64_t>(op1);
    break;
  default:
    std::cerr << "HyperCPU::CPU::ExecCALLE placeholder reached: please report bug\n";
    exit(1);
  }
}
