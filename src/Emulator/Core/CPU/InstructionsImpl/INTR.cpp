#include <Core/CPU/Interrupts/ReservedInterrupts.hpp>
#include <Core/CPU/CPU.hpp>

#include <Misc/deref.hpp>
#include <Misc/bit_cast.hpp>
#include <Misc/overflow.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecINTR(const IInstruction& instr, void* op1, void* op2) {
  std::uint64_t num = 0;

  switch (instr.m_opcode_mode) {
    case b8:  num = HyperCPU::bit_cast_from<std::uint8_t>(op1); break;
    case b16: num = HyperCPU::bit_cast_from<std::uint16_t>(op1); break;
    case b32: num = HyperCPU::bit_cast_from<std::uint32_t>(op1); break;
    case b64: num = HyperCPU::bit_cast_from<std::uint64_t>(op1); break;
  }

  if (num > 255) {
    return;
  }

  TriggerInterrupt(static_cast<HyperCPU::cpu_exceptions>(num));
}

#pragma GCC diagnostic pop
