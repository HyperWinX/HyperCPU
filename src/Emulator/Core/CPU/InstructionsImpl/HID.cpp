#include <Core/CPU/CPU.hpp>
#include <Core/CPU/Version.hpp>

#include <Misc/deref.hpp>
#include <Misc/bit_cast.hpp>
#include <Misc/overflow.hpp>



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecHID(const IInstruction& instr, void* op1, void* op2) {
  switch (*x0) {
    case 0:
      *x0 = 2;
      break;
    case 1:
      std::strncpy(std::bit_cast<char*>(&data), HID_CPU_NAME, sizeof(HID_CPU_NAME));
      break;
    case 2:
      *x0 = 0;
      break;
    default:
      break;
  }
}

#pragma GCC diagnostic pop
