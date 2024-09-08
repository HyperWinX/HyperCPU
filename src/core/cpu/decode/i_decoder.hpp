#pragma once

#include <core/memory_controller/i_memory_controller.hpp>
#include <core/cpu/instructions/opcodes.hpp>
#include <core/cpu/instructions/flags.hpp>


namespace hypercpu {
  struct i_instruction {
    opcode opcode;
    mode opcode_mode;
    operand_types op_types;
    std::size_t op1, op2;
  };

  class i_decoder {
  public:
    virtual i_instruction fetch_and_decode() = 0;
  };
}