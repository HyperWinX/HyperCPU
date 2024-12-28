#pragma once

#include <core/memory_controller/i_memory_controller.hpp>
#include <core/cpu/instructions/opcodes.hpp>
#include <core/cpu/instructions/flags.hpp>
#include <core/cpu/decode/i_decoder.hpp>


namespace hypercpu {
  struct instruction {
    opcode op;
    mode op_mode;
  };

  class cpu;

  class decoder final : public i_decoder {
  private:
    i_memory_controller* mem_controller;
    std::uint64_t* rip;
    cpu* cpu;

    bool check_supported_operand_size(std::uint8_t byte, std::uint8_t mask) const noexcept;
    void raise_exception(bool expr) const noexcept;

  public:
    explicit decoder() = default; // For testing purposes - causes UB if used incorrectly
    explicit decoder(i_memory_controller* mc, std::uint64_t* counter, class cpu* cpu) : mem_controller(mc), rip(counter), cpu(cpu) {}

    i_instruction fetch_and_decode() override;

    ~decoder() = default;
  };
}