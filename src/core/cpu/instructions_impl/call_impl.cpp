#include <core/cpu/instructions_impl/instructions.hpp>
#include <core/cpu/cpu.hpp>

#include <misc/deref.hpp>
#include <misc/bit_cast.hpp>
#include <misc/overflow.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void hypercpu::cpu::exec_call(operand_types op_types, mode md, void* op1, void* op2) {
  switch (op_types) { // Placeholders
    case R:
      break;
    case M:
      break;
    default:
      break;
  }
}

#pragma GCC diagnostic pop
