#include <Core/CPU/CPU.hpp>

#include <Misc/deref.hpp>
#include <Misc/bit_cast.hpp>
#include <Misc/overflow.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecDEC(const IInstruction& instr, void* op1, void* op2) {
  switch (instr.m_opcode_mode) {
    case b8: {
      auto& dst = deref<std::uint8_t>(op1);
      udf = (dst == 0);
      --dst;
      break;
    }

    case b16: {
      auto& dst = deref<std::uint16_t>(op1);
      udf = (dst == 0);
      --dst;
      break;
    }

    case b32: {
      auto& dst = deref<std::uint32_t>(op1);
      udf = (dst == 0);
      --dst;
      break;
    }

    case b64: {
      auto& dst = deref<std::uint64_t>(op1);
      udf = (dst == 0);
      --dst;
      break;
    }
  }
}

#pragma GCC diagnostic pop
