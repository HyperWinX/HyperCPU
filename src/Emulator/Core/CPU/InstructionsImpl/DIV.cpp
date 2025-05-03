#include "pch.hpp"

#include <Core/CPU/Interrupts/ReservedInterrupts.hpp>
#include <Core/CPU/CPU.hpp>
#include <Core/CPU/ALU.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

using namespace HyperALU;

void HyperCPU::CPU::ExecDIV(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  if (!(*x2)) {
    TriggerInterrupt(cpu_exceptions::ZRDIV);
    return;
  }

  switch (instr.m_opcode_mode) {
    case b8: {
      std::uint8_t& dst = op1.deref<std::uint8_t>();
      *x1 = __hcpu_div_remainder(dst, static_cast<std::uint8_t>(*x2));
      dst = __hcpu_div(dst, static_cast<std::uint8_t>(*x2));
      break;
    }

    case b16: {
      auto& dst = op1.deref<std::uint16_t>();
      *x1 = __hcpu_div_remainder(dst, static_cast<std::uint16_t>(*x2));
      dst = __hcpu_div(dst, static_cast<std::uint16_t>(*x2));
      break;
    }

    case b32: {
      auto& dst = op1.deref<std::uint32_t>();
      *x1 = __hcpu_div_remainder(dst, static_cast<std::uint32_t>(*x2));
      dst = __hcpu_div(dst, static_cast<std::uint32_t>(*x2));
      break;
    }

    case b64: {
      auto& dst = op1.deref<std::uint64_t>();
      *x1 = __hcpu_div_remainder(dst, static_cast<std::uint64_t>(*x2));
      dst = __hcpu_div(dst, static_cast<std::uint64_t>(*x2));
      break;
    }
  }
}

#pragma GCC diagnostic pop
