#include <iostream>

#include <Core/CPU/Assert.hpp>
#include <Core/CPU/CPU.hpp>

#include <Misc/deref.hpp>
#include <Misc/bit_cast.hpp>
#include <Misc/overflow.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecCALLE(const IInstruction& instr, void* op1, void* op2) {
  if (!(zrf && !crf)) {
    return;
  }
  
  switch (instr.m_op_types) { // Placeholders
    case R:
      StackPush64(*xip);
      *xip = deref<std::uint64_t>(op1);
      break;
    case IMM:
      StackPush64(*xip);
      *xip = HyperCPU::bit_cast<std::uint64_t>(op1);
      break;
    default:
      h_assert(false, {std::cout << "HyperCPU::CPU::ExecCALLE placeholder reached: please report bug\n"; exit(1); });
      break;
  }
}

#pragma GCC diagnostic pop
