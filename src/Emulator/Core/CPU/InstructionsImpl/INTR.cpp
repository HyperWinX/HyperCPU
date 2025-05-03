#include "pch.hpp"

#include <Core/CPU/Interrupts/ReservedInterrupts.hpp>
#include <Core/CPU/CPU.hpp>

#include <Misc/bit_cast.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecINTR(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  std::uint64_t num = 0;

  switch (instr.m_opcode_mode) {
    case b8:  num = HyperCPU::bit_cast_from<std::uint8_t>(op1.ptr<std::uint8_t>()); break;
    case b16: num = HyperCPU::bit_cast_from<std::uint16_t>(op1.ptr<std::uint16_t>()); break;
    case b32: num = HyperCPU::bit_cast_from<std::uint32_t>(op1.ptr<std::uint32_t>()); break;
    case b64: num = HyperCPU::bit_cast_from<std::uint64_t>(op1.ptr<std::uint64_t>()); break;
  }

  if (num > 255) {
    return;
  }

  TriggerInterrupt(static_cast<HyperCPU::cpu_exceptions>(num));
}

#pragma GCC diagnostic pop
