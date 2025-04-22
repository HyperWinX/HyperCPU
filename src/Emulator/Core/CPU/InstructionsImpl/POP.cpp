#include <Core/CPU/Instructions/Flags.hpp>
#include <Misc/unreachable.hpp>
#include <Core/CPU/CPU.hpp>
#include <Misc/deref.hpp>
#include <Exit.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecPOP(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  switch (instr.m_op_types) {
    case R:
      switch (instr.m_opcode_mode) {
        case HyperCPU::Mode::b8: op1.deref<std::uint8_t>() = StackPop8(); break;
        case HyperCPU::Mode::b16: op1.deref<std::uint16_t>() = StackPop16(); break;
        case HyperCPU::Mode::b32: op1.deref<std::uint32_t>() = StackPop32(); break;
        case HyperCPU::Mode::b64: op1.deref<std::uint64_t>() = StackPop64(); break;
        default: UNREACHABLE();
      }
      break;
    default:
      UNREACHABLE();
  }
}

#pragma GCC diagnostic pop
