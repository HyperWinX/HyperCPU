#pragma once

#include <core/cpu/decode/i_decoder.hpp>
#include <core/memory_controller/i_memory_controller.hpp>
#include <core/cpu/instructions/opcodes.hpp>
#include <core/cpu/instructions/flags.hpp>


namespace hypercpu {
  struct instruction {
    opcode op;
    mode op_mode;
  };

  class decoder final : public i_decoder {
  private:
    i_memory_controller* mem_controller;
    std::uint64_t* rip;

  public:
    explicit decoder() = default; // For testing purposes - causes UB if used incorrectly
    explicit decoder(i_memory_controller* mc, std::uint64_t* counter) : mem_controller(mc), rip(counter) {}

    bool check_supported_operand_size(std::uint8_t byte, std::uint8_t mask) override;
    i_instruction fetch_and_decode() override;

    ~decoder() = default;
  };
}