#pragma once

#include <cstdint>


namespace HyperCPU {
  enum Mode : std::uint_fast8_t {
    b8  = 0b00,
    b16 = 0b01,
    b32 = 0b10,
    b64 = 0b11
  };

  enum OperandTypes : std::uint_fast8_t {
    R_R     = 0b0000,
    R_RM    = 0b0001,
    R_M     = 0b0010,
    R_IMM   = 0b0011,
    RM_R    = 0b0100,
    RM_M    = 0b0101,
    RM_IMM  = 0b0110,
    M_R     = 0b0111,
    R       = 0b1000,
    M       = 0b1001,
    IMM     = 0b1010,
    NONE    = 0b1011
  };

  static constexpr std::uint_fast8_t MAX_OPERAND_TYPE = NONE;
}