#pragma once

namespace HyperCPU {
  struct IInstruction;

  class IDecoder {
  public:
    virtual IInstruction FetchAndDecode() = 0;
    virtual bool IsHalted() const noexcept = 0;
  };
}