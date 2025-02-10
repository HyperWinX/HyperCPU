#include <Core/CPU/Decoders/StdDecoder.hpp>
#include <Core/CPU/CPU.hpp>

#include <Misc/bit_cast.hpp>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecWRITE(const IInstruction& instr, void* op1, void* op2) {
  write_operation_handler& handler = write_io_handlers[*static_cast<std::uint8_t*>(op1)];

  if (handler) {
    switch (instr.m_op_types) {
      case R_R:
        handler(*static_cast<std::uint8_t*>(op2));
        break;
      case R_IMM:
        handler(HyperCPU::bit_cast<std::uint8_t>(op2));
        break;
      default:
        std::unreachable();
    }
  }
}

#pragma GCC diagnostic pop
