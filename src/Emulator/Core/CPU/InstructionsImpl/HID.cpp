#include "Emulator/Core/CPU/CPU.hpp"
#include "Emulator/Core/CPU/Version.hpp"


void HyperCPU::CPU::ExecHID(const IInstruction& /* instr */, OperandContainer /* op1 */, OperandContainer /* op2 */) {
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
