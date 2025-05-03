#include "pch.hpp"

#include <Core/CPU/CPU.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecCUDF(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  udf = false;
}

#pragma GCC diagnostic pop
