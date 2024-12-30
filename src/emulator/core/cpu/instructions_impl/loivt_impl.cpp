#include <core/cpu/instructions_impl/instructions.hpp>
#include <core/cpu/cpu.hpp>

#include <misc/deref.hpp>
#include <misc/bit_cast.hpp>
#include <misc/overflow.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void hypercpu::cpu::exec_loivt(operand_types op_types, mode md, void* op1, void* op2) {
  *xivt = hypercpu::bit_cast_from<std::uint64_t>(op1);
}

#pragma GCC diagnostic pop
