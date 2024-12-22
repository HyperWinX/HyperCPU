#include "core/cpu/instructions/opcodes.hpp"
#include <core/cpu/cpu.hpp>

void hypercpu::cpu::trigger_interrupt(std::uint8_t num) {
  std::uint64_t code_ptr = mem_controller->read64(*xivt) + (8 * num);

  if (!code_ptr) {
    return;
  }

  stack_push64(*xip);
  *xip = code_ptr;
  run_interrupt_subroutine();
  if (!halted) {
    *xip = stack_pop64();
  }
}

void hypercpu::cpu::run_interrupt_subroutine() {
  while (1) {
    if (halted) return;
    
    hypercpu::i_instruction instr = m_decoder->fetch_and_decode();
    if (instr.m_opcode == opcode::IRET) {
      return;
    }
    std::pair<void*, void*> operands = get_operands(instr.m_op_types, instr.m_opcode_mode, instr.m_op1, instr.m_op2);
    opcode_handler_assoc[static_cast<std::uint16_t>(instr.m_opcode)](instr.m_op_types, instr.m_opcode_mode, operands.first, operands.second);
  }
}