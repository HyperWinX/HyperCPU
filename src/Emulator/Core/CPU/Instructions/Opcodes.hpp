#pragma once

#include <pch.hpp>


#define OPCODE_CASE(opcode) case static_cast<std::uint16_t>(opcode):
#define OPCODE_DEFAULT_CASE() default: return false;

namespace HyperCPU {

  enum Opcode : std::uint16_t {
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
    LOIVT = 0x0014,
    INTR  = 0x0015,
    RET   = 0x0016,
    IRET  = 0x0017,
    READ  = 0x0018,
    WRITE = 0x0019,
    JMP   = 0x001A,
    PUSH  = 0x001B,
    POP   = 0x001C,
    CALLE = 0x001D,
    CALLGR= 0x001E,
    CALLL = 0x001F,
    JME   = 0x0020,
    JMGR  = 0x0021,
    JML   = 0x0022,
    CMP   = 0x0023,
    MOV   = 0x007F,
    _CONT = 0x6934
  };

  namespace Validator {
    static constexpr inline bool IsValidOpcode(std::uint16_t op) {
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
        OPCODE_CASE(LOIVT)
        OPCODE_CASE(INTR)
        OPCODE_CASE(READ)
        OPCODE_CASE(WRITE)
        OPCODE_CASE(JMP)
        OPCODE_CASE(IRET)
        OPCODE_CASE(PUSH)
        OPCODE_CASE(POP)
        OPCODE_CASE(CALLE)
        OPCODE_CASE(CALLGR)
        OPCODE_CASE(CALLL)
        OPCODE_CASE(JME)
        OPCODE_CASE(JMGR)
        OPCODE_CASE(JML)
        OPCODE_CASE(CMP)
          return true;
        OPCODE_DEFAULT_CASE()
      }
    }
  }

}

#undef OPCODE_CASE
#undef OPCODE_DEFAULT_CASE
