#include "pch.hpp"

#include <iostream>

#include <Core/CPU/Assert.hpp>
#include <Core/CPU/CPU.hpp>

#include <Misc/bit_cast.hpp>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecCALLE(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  if (!(zrf && !crf)) {
    return;
  }

  switch (instr.m_op_types) { // Placeholders
  case R:
    StackPush64(*xip);
    *xip = op1.deref<std::uint64_t>();
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
