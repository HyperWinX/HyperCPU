#include <pch.hpp>

#include <Core/CPU/CPU.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecHALT(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  halted = true;
}

#pragma GCC diagnostic pop
