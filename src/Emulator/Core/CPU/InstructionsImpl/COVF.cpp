#include "Emulator/Core/CPU/CPU.hpp"

void HyperCPU::CPU::ExecCOVF(const IInstruction& /* instr */, OperandContainer /* op1 */, OperandContainer /* op2 */) {
  ovf = false;
}
