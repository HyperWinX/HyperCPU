#include <Core/CPU/CPU.hpp>

#include <Misc/deref.hpp>
#include <Misc/bit_cast.hpp>
#include <Misc/overflow.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecLOIVT(const IInstruction& instr, void* op1, void* op2) {
  *xivt = HyperCPU::bit_cast_from<std::uint64_t>(op1);
}

#pragma GCC diagnostic pop
