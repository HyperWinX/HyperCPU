#include "pch.hpp"

#include <Core/CPU/CPU.hpp>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecCOVF(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  ovf = false;
}

#pragma GCC diagnostic pop
