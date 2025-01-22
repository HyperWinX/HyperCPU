#include <Core/CPU/Interrupts/ReservedInterrupts.hpp>
#include <Core/CPU/CPU.hpp>

#include <Misc/deref.hpp>
#include <Misc/bit_cast.hpp>
#include <Misc/overflow.hpp>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecDIV(OperandTypes op_types, Mode md, void* op1, void* op2) {
  if (!(*x2)) {
    TriggerInterrupt(cpu_exceptions::ZRDIV);
    return;
  }

  switch (md) {
    case b8: {
      auto& dst = deref<std::uint8_t>(op1);
      *x1 = dst % *x2;
      dst /= *x2;
      break;
    }
    
    case b16: {
      auto& dst = deref<std::uint16_t>(op1);
      *x1 = dst % *x2;
      dst /= *x2;
      break;
    }

    case b32: {
      auto& dst = deref<std::uint32_t>(op1);
      *x1 = dst % *x2;
      dst /= *x2;
      break;
    }

    case b64: {
      auto& dst = deref<std::uint64_t>(op1);
      *x1 = dst % *x2;
      dst /= *x2;
      break;
    }
  }
}

#pragma GCC diagnostic pop
