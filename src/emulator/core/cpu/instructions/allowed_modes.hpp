#pragma once

#include <cstdint>


namespace hypercpu {
  static constexpr std::uint8_t SUPPORT_ALL = 0b00011011;
  
  extern const std::uint8_t allowed_op_modes[128][12];
}