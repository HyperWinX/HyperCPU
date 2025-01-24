#pragma once

#include <Core/MemoryController/IMemoryController.hpp>
#include <Core/CPU/Instructions/Opcodes.hpp>
#include <Core/CPU/Instructions/Flags.hpp>


namespace HyperCPU {
  struct IInstruction;

  class IDecoder {
  public:
    virtual IInstruction FetchAndDecode() = 0;
    virtual bool IsHalted() const noexcept = 0;
  };
}