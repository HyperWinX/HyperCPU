#include <core/memory_controller/i_memory_controller.hpp>
#include <core/cpu/instructions/opcodes.hpp>
#include <core/cpu/instructions/flags.hpp>
#include <core/cpu/fetch/fetcher.hpp>


namespace hypercpu {
  struct instruction {
    opcode op;
    mode op_mode;
  };

  class decoder {
  private:
    i_memory_controller* mem_controller;

  public:
    explicit decoder(i_memory_controller* mc) : mem_controller(mc) {}

    instruction decode(fetched_instruction instr);
  };
}