#include <Core/CPU/CPU.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecCCRF(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  crf = false;
}

#pragma GCC diagnostic pop
