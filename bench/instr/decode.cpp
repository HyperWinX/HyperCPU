#include "Core/CPU/Instructions/Opcodes.hpp"
#include "Core/CPU/Instructions/Registers.hpp"
#include "Core/MemoryController/IMemoryController.hpp"
#include "Core/MemoryController/MemoryControllerST.hpp"
#include <benchmark/benchmark.h>

#include <Core/CPU/Decoders/StdDecoder.hpp>

HyperCPU::IMemoryController* mem_ctlr;
std::uint64_t xip = 0;
HyperCPU::Decoder decoder;

void Setup([[maybe_unused]] const benchmark::State& state) {
  mem_ctlr = dynamic_cast<HyperCPU::IMemoryController*>(new HyperCPU::MemoryControllerST(5 * 1024 * 1024));
  xip = 0;
  decoder = HyperCPU::Decoder{mem_ctlr, &xip, nullptr};

  for (std::uint32_t i = 0; i < 1024 * 1024; ++i) {
    mem_ctlr->Load16(xip, HyperCPU::Opcode::MOV);
    mem_ctlr->Load8(xip + 2, HyperCPU::Mode::b64 << 4 | HyperCPU::OperandTypes::R_R);
    mem_ctlr->Load8(xip + 3, static_cast<std::uint8_t>(HyperCPU::Registers::X0));
    mem_ctlr->Load8(xip + 4, static_cast<std::uint8_t>(HyperCPU::Registers::X1));
    xip += 5;
  }
  xip = 0;
}

void TearDown([[maybe_unused]] const benchmark::State& state) {
  delete mem_ctlr;
}

void decode(benchmark::State& state) {
  while (state.KeepRunning()) {
    [[maybe_unused]] auto instr = decoder.FetchAndDecode();
  }
}

BENCHMARK(decode)->Iterations(1024 * 1024)->Setup(Setup)->Teardown(TearDown);
