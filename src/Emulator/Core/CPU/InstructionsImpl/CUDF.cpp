#include "Emulator/Core/CPU/CPU.hpp"


void HyperCPU::CPU::ExecCUDF(const IInstruction& /* instr */, OperandContainer /* op1 */, OperandContainer /* op2 */) {
  udf = false;
}
