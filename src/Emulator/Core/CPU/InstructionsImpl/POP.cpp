#include <utility>

#include "Core/CPU/Instructions/Flags.hpp"
#include <Core/CPU/CPU.hpp>

#include <Misc/deref.hpp>
#include <Misc/unreachable.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecPOP(const IInstruction& instr, void* op1, void* op2) {
  switch (instr.m_op_types) {
    case R:
      switch (instr.m_opcode_mode) {
        case HyperCPU::Mode::b8: deref<std::uint8_t>(op1) = StackPop8(); break;
        case HyperCPU::Mode::b16: deref<std::uint16_t>(op1) = StackPop16(); break;
        case HyperCPU::Mode::b32: deref<std::uint32_t>(op1) = StackPop32(); break;
        case HyperCPU::Mode::b64: deref<std::uint64_t>(op1) = StackPop64(); break;
        default: HyperCPU::unreachable();
      }
      break;
    default:
      HyperCPU::unreachable();
  }
}

#pragma GCC diagnostic pop
