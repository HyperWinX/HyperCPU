#include <core/cpu/instructions_impl/instructions.hpp>
#include <core/cpu/cpu.hpp>

#include <misc/deref.hpp>
#include <misc/bit_cast.hpp>
#include <misc/overflow.hpp>

#include <core/cpu/version.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void hypercpu::cpu::exec_hid(operand_types op_types, mode md, void* op1, void* op2) {
  switch (*x0) {
    case 0:
      *x0 = 2;
      break;
    case 1:
      std::strcpy(std::bit_cast<char*>(&data), HID_CPU_NAME);
      break;
    case 2:
      *x0 = 0;
      break;
    default:
      break;
  }
}

#pragma GCC diagnostic pop
