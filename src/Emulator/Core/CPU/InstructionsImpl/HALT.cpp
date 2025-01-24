#include <Core/CPU/CPU.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecHALT(const IInstruction& instr, void* op1, void* op2) {
  halted = true;
}

#pragma GCC diagnostic pop
