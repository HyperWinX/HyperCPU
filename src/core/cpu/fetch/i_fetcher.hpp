#include <cstdint>

#include <core/memory_controller/i_memory_controller.hpp>


namespace hypercpu {
  struct fetched_instruction {
    std::uint16_t instruction;
    std::uint8_t flags;
  };

  class i_fetcher {
  public:
    virtual fetched_instruction fetch() = 0;
  };
}