#pragma once

#include <cstdint>


#define OPCODE_CASE(opcode) case static_cast<std::uint16_t>(opcode): return true;
#define OPCODE_DEFAULT_CASE() default: return false;

namespace hypercpu {

  enum opcode : std::uint_fast16_t {
    ADC   = 0x0001,
    ADD   = 0x0002,
    AND   = 0x0003,
    ANDN  = 0x0004,
    BSWAP = 0x0005,
    CALL  = 0x0006,
    CCRF  = 0x0007,
    COVF  = 0x0008,
    CUDF  = 0x0009,
    HID   = 0x000A,
    INC   = 0x000B,
    DEC   = 0x000C,
    DIV   = 0x000D,
    MUL   = 0x000E,
    SUB   = 0x000F,
    SHFR  = 0x0010,
    SHFL  = 0x0011,
    OR    = 0x0012,
    HALT  = 0x0013,
    MOV   = 0x007F
  };

  namespace validator {
    static constexpr inline bool is_valid_opcode(std::uint16_t op) {
      switch (op) {
        OPCODE_CASE(ADC)
        OPCODE_CASE(ADD)
        OPCODE_CASE(AND)
        OPCODE_CASE(ANDN)
        OPCODE_CASE(BSWAP)
        OPCODE_CASE(CALL)
        OPCODE_CASE(CCRF)
        OPCODE_CASE(COVF)
        OPCODE_CASE(CUDF)
        OPCODE_CASE(HID)
        OPCODE_CASE(INC)
        OPCODE_CASE(DEC)
        OPCODE_CASE(DIV)
        OPCODE_CASE(MUL)
        OPCODE_CASE(SUB)
        OPCODE_CASE(SHFR)
        OPCODE_CASE(SHFL)
        OPCODE_CASE(OR)
        OPCODE_CASE(HALT)
        OPCODE_CASE(MOV)
        OPCODE_DEFAULT_CASE()
      }
    }
  }

}

#undef OPCODE_CASE
#undef OPCODE_DEFAULT_CASE