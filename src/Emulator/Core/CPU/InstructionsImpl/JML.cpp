#include <iostream>

#include <Core/CPU/Assert.hpp>
#include <Core/CPU/CPU.hpp>

#include <Misc/deref.hpp>
#include <Misc/bit_cast.hpp>
#include <Misc/overflow.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecJML(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  if (!(!zrf && crf)) {
    return;
  }

  switch (instr.m_op_types) { // Placeholders
    case R:
      *xip = op1.deref<std::uint64_t>();
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
