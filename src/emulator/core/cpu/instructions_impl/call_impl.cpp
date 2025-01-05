#include <iostream>

#include "core/cpu/assert.hpp"
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
      stack_push64(*xip);
      *xip = deref<std::uint64_t>(op1);
      break;
    case M:
      stack_push64(*xip);
      *xip = hypercpu::bit_cast<std::uint64_t>(op1);
      break;
    default:
      h_assert(false, {std::cout << "hypercpu::cpu::exec_call placeholder reached: please report bug\n"; exit(1); });
      break;
  }
}

#pragma GCC diagnostic pop
