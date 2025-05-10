#include "Emulator/Core/CPU/CPU.hpp"

void HyperCPU::CPU::ExecDEC(const IInstruction& instr, OperandContainer op1, OperandContainer /* op2 */) {
  switch (instr.m_opcode_mode) {
  case Mode::b8: {
    auto& dst = op1.deref<std::uint8_t>();
    udf = (dst == 0);
    --dst;
    break;
  }

  case Mode::b16: {
    auto& dst = op1.deref<std::uint16_t>();
    udf = (dst == 0);
    --dst;
    break;
  }

  case Mode::b32: {
    auto& dst = op1.deref<std::uint32_t>();
    udf = (dst == 0);
    --dst;
    break;
  }

  case Mode::b64: {
    auto& dst = op1.deref<std::uint64_t>();
    udf = (dst == 0);
    --dst;
    break;
  }
  }
}
