#include "Emulator/Core/CPU/CPU.hpp"


void HyperCPU::CPU::ExecHALT(const IInstruction& /* instr */, OperandContainer /* op1 */, OperandContainer /* op2 */) {
  halted = true;
}
