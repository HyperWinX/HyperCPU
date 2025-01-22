#include <bit>

#include <Core/CPU/CPU.hpp>

#include <Misc/deref.hpp>
#include <Misc/bit_cast.hpp>
#include <Misc/overflow.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecBSWAP(OperandTypes op_types, Mode md, void* op1, void* op2) {
  switch (md) {
    case b8:
      break;

    case b16: {
      auto& dst = deref<std::uint16_t>(op1);
      dst = std::byteswap(dst);
      break;
    }

    case b32: {
      auto& dst = deref<std::uint32_t>(op1);
      dst = std::byteswap(dst);
      break;
    }

    case b64: {
      auto& dst = deref<std::uint64_t>(op1);
      dst = std::byteswap(dst);
      break;
    }
  }
}

#pragma GCC diagnostic pop
