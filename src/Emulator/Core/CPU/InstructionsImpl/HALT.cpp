#include <Core/CPU/CPU.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void hypercpu::cpu::exec_halt(operand_types op_types, mode md, void* op1, void* op2) {
  halted = true;
}

#pragma GCC diagnostic pop
