#include <cstdint>

namespace hypercpu {
  enum mode : std::uint_fast8_t {
    b8  = 0b00,
    b16 = 0b01,
    b32 = 0b10,
    b64 = 0b11
  };

  
}