#include "pch.hpp"

#include <Core/CPU/CPU.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecDEC(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  switch (instr.m_opcode_mode) {
    case b8: {
      auto& dst = op1.deref<std::uint8_t>();
      udf = (dst == 0);
      --dst;
      break;
    }

    case b16: {
      auto& dst = op1.deref<std::uint16_t>();
      udf = (dst == 0);
      --dst;
      break;
    }

    case b32: {
      auto& dst = op1.deref<std::uint32_t>();
      udf = (dst == 0);
      --dst;
      break;
    }

    case b64: {
      auto& dst = op1.deref<std::uint64_t>();
      udf = (dst == 0);
      --dst;
      break;
    }
  }
}

#pragma GCC diagnostic pop
