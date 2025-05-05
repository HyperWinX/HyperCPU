#include "pch.hpp"

#include <Core/CPU/CPU.hpp>
#include <Core/CPU/Version.hpp>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecHID(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  switch (*x0) {
  case 0:
    *x0 = 2;
    break;
  case 1:
    std::strcpy(std::bit_cast<char*>(&data), HID_CPU_NAME);
    break;
  case 2:
    *x0 = 0;
    break;
  default:
    break;
  }
}

#pragma GCC diagnostic pop
