#include "Exit.hpp"
#include <Core/CPU/CPU.hpp>

#include <Misc/deref.hpp>
#include <Misc/bit_cast.hpp>
#include <Misc/overflow.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecLOIVT(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  switch (instr.m_op_types) {
    case IMM:
      *xivt = HyperCPU::bit_cast<std::uint64_t>(op1);
      break;
    case R:
      *xivt = HyperCPU::bit_cast_from<std::uint64_t>(op1.ptr<std::uint64_t>());
      break;
    default: ABORT();
  }
  ivt_initialized = true;
}

#pragma GCC diagnostic pop
