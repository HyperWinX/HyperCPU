#include <bit>

#include <Core/CPU/CPU.hpp>

#include <Misc/deref.hpp>
#include <Misc/bit_cast.hpp>
#include <Misc/overflow.hpp>
#include <Misc/byteswap.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecBSWAP(const IInstruction& instr, void* op1, void* op2) {
  switch (instr.m_opcode_mode) {
    case b8:
      break;

    case b16: {
      auto& dst = deref<std::uint16_t>(op1);
      dst = HyperCPU::byteswap(dst);
      break;
    }

    case b32: {
      auto& dst = deref<std::uint32_t>(op1);
      dst = HyperCPU::byteswap(dst);
      break;
    }

    case b64: {
      auto& dst = deref<std::uint64_t>(op1);
      dst = HyperCPU::byteswap(dst);
      break;
    }
  }
}

#pragma GCC diagnostic pop
