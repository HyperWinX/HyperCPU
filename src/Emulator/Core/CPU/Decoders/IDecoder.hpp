#pragma once

#include <Core/MemoryController/IMemoryController.hpp>
#include <Core/CPU/Instructions/Opcodes.hpp>
#include <Core/CPU/Instructions/Flags.hpp>


namespace hypercpu {
  struct i_instruction {
    opcode m_opcode;
    mode m_opcode_mode;
    operand_types m_op_types;
    std::size_t m_op1, m_op2;
  };

  class i_decoder {
  public:
    virtual i_instruction fetch_and_decode() = 0;
    virtual bool is_halted() const noexcept = 0;
  };
}