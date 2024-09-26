#include <functional>

#include <core/cpu/instructions_impl/instructions.hpp>
#include <core/cpu/decode/i_decoder.hpp>
#include <core/cpu/decode/decoder.hpp>
#include <core/cpu/cpu.hpp>

void hypercpu::cpu::run() {
  while (1) {
    if (halted) return;
    
    hypercpu::i_instruction instr = m_decoder->fetch_and_decode();
    std::pair<void*, void*> operands = get_operands(instr.m_op_types, instr.m_opcode_mode, instr.m_op1, instr.m_op2);
    opcode_handler_assoc[static_cast<std::uint16_t>(instr.m_opcode)](instr.m_op_types, instr.m_opcode_mode, operands.first, operands.second);
  }
}