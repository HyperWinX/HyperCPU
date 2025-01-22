#include <Core/CPU/CPU.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecHALT(OperandTypes op_types, Mode md, void* op1, void* op2) {
  halted = true;
}

#pragma GCC diagnostic pop
