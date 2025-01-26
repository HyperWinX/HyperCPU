#include <Core/CPU/Decoders/StdDecoder.hpp>
#include <Core/CPU/CPU.hpp>

#include <Misc/bit_cast.hpp>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void HyperCPU::CPU::ExecREAD(const IInstruction& instr, void* op1, void* op2) {
  read_operation_handler& handler = read_io_handlers[HyperCPU::bit_cast<std::uint8_t>(op1)];

  if (handler) {
    *xlll0 = handler();
  }
}

#pragma GCC diagnostic pop