#include <cstdint>

#include <core/cpu/instructions/allowed_modes.hpp>

namespace hypercpu {
  const std::uint8_t allowed_op_modes[128][12] = {
    {}, // NULL
    {SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, 0, 0, 0, 0, 0, 0, 0, 0}, // ADC
    {SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, 0, 0, 0, 0, 0, 0, 0, 0}, // ADD
    {SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, 0, 0, 0, 0, 0, 0, 0, 0}, // AND
    {SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, 0, 0, 0, 0, 0, 0, 0, 0}, // ANDN
    {0, 0, 0, 0, 0, 0, 0, 0, SUPPORT_ALL, 0, 0, 0}, // BSWAP
    {0, 0, 0, 0, 0, 0, 0, 0, 0b00000011, SUPPORT_ALL, 0, 0}, // CALL
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, SUPPORT_ALL}, // CCRF
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, SUPPORT_ALL}, // COVF
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, SUPPORT_ALL}, // CUDF
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, SUPPORT_ALL}, // HID
    {0, 0, 0, 0, 0, 0, 0, 0, SUPPORT_ALL, 0, 0, 0}, // INC
    {0, 0, 0, 0, 0, 0, 0, 0, SUPPORT_ALL, 0, 0, 0}, // DEC
    {0, 0, 0, 0, 0, 0, 0, 0, SUPPORT_ALL, 0, SUPPORT_ALL, 0}, // DIV
    {SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, 0, 0, 0, 0, 0, 0, 0, 0}, // MUL
    {SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, 0, 0, 0, 0, 0, 0, 0, 0}, // SUB
    {SUPPORT_ALL, 0, 0, SUPPORT_ALL, 0, 0, 0, 0, 0, 0, 0, 0}, // SHFR
    {SUPPORT_ALL, 0, 0, SUPPORT_ALL, 0, 0, 0, 0, 0, 0, 0, 0}, // SHFL
    {SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, 0, 0, 0, 0, 0, 0, 0, 0}, // OR
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, SUPPORT_ALL}, // HALT
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, 0, 0, 0, 0}, // MOV
  };
}