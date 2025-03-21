#include <utility>

#include "Core/CPU/Instructions/Flags.hpp"
#include <Core/CPU/CPU.hpp>

#include <Misc/bit_cast.hpp>
#include <Misc/unreachable.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecPUSH(const IInstruction& instr, void* op1, void* op2) {
  switch (instr.m_op_types) {
    case R:
      switch (instr.m_opcode_mode) {
        case HyperCPU::Mode::b8: StackPush8(HyperCPU::bit_cast_from<std::uint8_t>(op1)); break;
        case HyperCPU::Mode::b16: StackPush16(HyperCPU::bit_cast_from<std::uint16_t>(op1)); break;
        case HyperCPU::Mode::b32: StackPush32(HyperCPU::bit_cast_from<std::uint32_t>(op1)); break;
        case HyperCPU::Mode::b64: StackPush64(HyperCPU::bit_cast_from<std::uint64_t>(op1)); break;
        default: HyperCPU::unreachable();
      }
      break;
    case IMM:
      switch (instr.m_opcode_mode) {
        case HyperCPU::Mode::b8: StackPush8(HyperCPU::bit_cast<std::uint8_t>(op1)); break;
        case HyperCPU::Mode::b16: StackPush16(HyperCPU::bit_cast<std::uint16_t>(op1)); break;
        case HyperCPU::Mode::b32: StackPush32(HyperCPU::bit_cast<std::uint32_t>(op1)); break;
        case HyperCPU::Mode::b64: StackPush64(HyperCPU::bit_cast<std::uint64_t>(op1)); break;
        default: HyperCPU::unreachable();
      }
      break;
    default:
      HyperCPU::unreachable();
  }
}

#pragma GCC diagnostic pop
