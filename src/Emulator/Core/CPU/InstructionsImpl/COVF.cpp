#include <Core/CPU/CPU.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecCOVF(const IInstruction& instr, void* op1, void* op2) {
  ovf = false;
}

#pragma GCC diagnostic pop
