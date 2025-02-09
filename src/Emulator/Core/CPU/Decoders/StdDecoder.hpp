#pragma once

#include <Core/MemoryController/IMemoryController.hpp>
#include <Core/CPU/Instructions/Opcodes.hpp>
#include <Core/CPU/Instructions/Flags.hpp>
#include <Core/CPU/Decoders/IDecoder.hpp>


namespace HyperCPU {
  enum class AddrExtensionStatus {
    Disabled = 0b00,
    EnabledOp1 = 0b10,
    EnabledOp2 = 0b11
  };

  struct IInstruction {
    Opcode m_opcode;
    Mode m_opcode_mode;
    OperandTypes m_op_types;
    std::size_t m_op1, m_op2;
    AddrExtensionStatus addr_extension_status;
    std::uint8_t extension;
  };

  class CPU;

  class Decoder final : public IDecoder {
  private:
    IMemoryController* mem_controller;
    std::uint64_t* xip;
    class CPU* cpu;
    bool decoder_halted;

    bool CheckSupportedOperandSize(std::uint8_t byte, Mode mode) const noexcept;
    void RaiseException(bool expr) noexcept;

  public:
    explicit Decoder() = default; // For testing purposes - causes UB if used incorrectly
    explicit Decoder(IMemoryController* mc, std::uint64_t* counter, class CPU* cpu) 
      : mem_controller(mc)
      , xip(counter)
      , cpu(cpu)
      , decoder_halted(false) {}

    IInstruction FetchAndDecode() override;
    bool IsHalted() const noexcept override;

    ~Decoder() = default;
  };
}