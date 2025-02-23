#include <iostream>

#include <Core/CPU/Assert.hpp>
#include <Core/CPU/CPU.hpp>

#include <Misc/deref.hpp>
#include <Misc/bit_cast.hpp>
#include <Misc/overflow.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecJMP(const IInstruction& instr, void* op1, void* op2) {
  switch (instr.m_op_types) { // Placeholders
    case R:
      *xip = deref<std::uint64_t>(op1);
      break;
    case IMM:
      *xip = HyperCPU::bit_cast<std::uint64_t>(op1);
      break;
    default:
      h_assert(false, {std::cout << "HyperCPU::CPU::ExecJMP placeholder reached: please report bug\n"; exit(1); });
      break;
  }
}

#pragma GCC diagnostic pop
