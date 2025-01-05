#include "core/cpu/interrupts/reserved_interrupts.hpp"
#include <core/cpu/instructions_impl/instructions.hpp>
#include <core/cpu/cpu.hpp>

#include <misc/deref.hpp>
#include <misc/bit_cast.hpp>
#include <misc/overflow.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void hypercpu::cpu::exec_intr(operand_types op_types, mode md, void* op1, void* op2) {
  std::uint64_t num;

  switch (md) {
    case b8:  num = hypercpu::bit_cast_from<std::uint8_t>(op1); break;
    case b16: num = hypercpu::bit_cast_from<std::uint16_t>(op1); break;
    case b32: num = hypercpu::bit_cast_from<std::uint32_t>(op1); break;
    case b64: num = hypercpu::bit_cast_from<std::uint64_t>(op1); break;
  }

  if (num > 255) {
    return;
  }

  trigger_interrupt(static_cast<hypercpu::cpu_exceptions>(num));
}

#pragma GCC diagnostic pop
