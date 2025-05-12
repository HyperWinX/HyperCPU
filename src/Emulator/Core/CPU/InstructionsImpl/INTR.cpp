#include "Emulator/Core/CPU/CPU.hpp"
#include "Emulator/Core/CPU/Interrupts/ReservedInterrupts.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecINTR(const IInstruction& instr, OperandContainer op1, OperandContainer /* op2 */) {
  std::uint64_t num = 0;

  switch (instr.m_opcode_mode) {
  case Mode::b8:
    num = HyperCPU::bit_cast_from<std::uint8_t>(op1.ptr<std::uint8_t>());
    break;
  case Mode::b16:
    num = HyperCPU::bit_cast_from<std::uint16_t>(op1.ptr<std::uint16_t>());
    break;
  case Mode::b32:
    num = HyperCPU::bit_cast_from<std::uint32_t>(op1.ptr<std::uint32_t>());
    break;
  case Mode::b64:
    num = HyperCPU::bit_cast_from<std::uint64_t>(op1.ptr<std::uint64_t>());
    break;
  }

  if (num > 255) {
    return;
  }

  TriggerInterrupt(static_cast<HyperCPU::cpu_exceptions>(num));
}
