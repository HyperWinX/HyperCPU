#pragma once

#include <Core/MemoryController/IMemoryController.hpp>
#include <Core/CPU/Instructions/Opcodes.hpp>
#include <Core/CPU/Instructions/Flags.hpp>


namespace HyperCPU {
  struct IInstruction {
    Opcode m_opcode;
    Mode m_opcode_mode;
    OperandTypes m_op_types;
    std::size_t m_op1, m_op2;
  };

  class IDecoder {
  public:
    virtual IInstruction FetchAndDecode() = 0;
    virtual bool IsHalted() const noexcept = 0;
  };
}