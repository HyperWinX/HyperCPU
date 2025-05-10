#include "Emulator/Core/CPU/CPU.hpp"

void HyperCPU::CPU::ExecCCRF(const IInstruction& /* instr8 */, OperandContainer /* op1 */, OperandContainer /* op2 */) {
  crf = false;
}
