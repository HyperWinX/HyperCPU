#include <core/cpu/decode/i_decoder.hpp>
#include <core/memory_controller/i_memory_controller.hpp>
#include <core/cpu/instructions/opcodes.hpp>
#include <core/cpu/instructions/flags.hpp>


namespace hypercpu {
  struct instruction {
    opcode op;
    mode op_mode;
  };

  class decoder : i_decoder {
  private:
    i_memory_controller* mem_controller;
    std::size_t* rip;

  public:
    explicit decoder(i_memory_controller* mc, std::size_t* counter) : mem_controller(mc), rip(counter) {}

    bool check_supported_operand_size(std::uint8_t byte, std::uint8_t mask) override;
    i_instruction fetch_and_decode() override;
  };
}