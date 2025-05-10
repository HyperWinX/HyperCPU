#include <spdlog/spdlog.h>

#include "PCH/CStd.hpp"
#include "Emulator/Core/CPU/CPU.hpp"
#include "Common/LanguageSpec/Opcodes.hpp"
#include "Emulator/Core/CPU/Interrupts/ReservedInterrupts.hpp"

void HyperCPU::CPU::TriggerInterrupt(HyperCPU::cpu_exceptions exception) {
  if (!ivt_initialized || pending_interrupt.has_value()) {
    spdlog::error("Interrupt was triggered, but failed to execute handler! XIP: {}", *xip);
    std::abort();
  }

  pending_interrupt = std::make_optional(mem_controller->Read64((*xivt) + (8 * static_cast<std::uint8_t>(exception))));

  /*
  StackPush64(*xip);
  *xip = code_ptr;
  RunInterruptSubroutine();
  if (!halted) {
    *xip = StackPop64();
  }
  */
}

void HyperCPU::CPU::RunInterruptSubroutine() {
  while (1) {
    if (halted)
      return;

    HyperCPU::IInstruction instr = m_decoder->FetchAndDecode();
    if (instr.m_opcode == Opcode::IRET) {
      return;
    }
    std::pair<OperandContainer, OperandContainer> operands = GetOperands(instr.m_op_types, instr.m_opcode_mode, instr.m_op1, instr.m_op2);
    opcode_handler_assoc[static_cast<std::uint16_t>(instr.m_opcode)](instr, operands.first, operands.second);
  }
}
