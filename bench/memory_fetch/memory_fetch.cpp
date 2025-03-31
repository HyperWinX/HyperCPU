#include <Emulator/Core/MemoryController/MemoryControllerMT.hpp>
#include <Emulator/Core/MemoryController/MemoryControllerST.hpp>

#include <benchmark/benchmark.h>

static constexpr std::size_t ITERATIONS = 1024 * 1024 * 32;

class MC_ST : public benchmark::Fixture {
public:
  HyperCPU::MemoryControllerST mc_st;

  MC_ST() : mc_st(ITERATIONS) { }
};

void mc_st_load8([[maybe_unused]] benchmark::State& state) {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerST mc_st{ITERATIONS};
  while (state.KeepRunning()) {
    mc_st.Load8(counter, 0x55);
  }
}

void mc_st_load16([[maybe_unused]] benchmark::State& state) {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerST mc_st{ITERATIONS};
  while (state.KeepRunning()) {
    mc_st.Load16(counter, 0x55);
  }
}

void mc_st_load32([[maybe_unused]] benchmark::State& state) {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerST mc_st{ITERATIONS};
  while (state.KeepRunning()) {
    mc_st.Load32(counter, 0x55);
  }
}

void mc_st_load64([[maybe_unused]] benchmark::State& state) {
  std::size_t counter = 0;                                          HyperCPU::MemoryControllerST mc_st{ITERATIONS};
  while (state.KeepRunning()) {
    mc_st.Load64(counter, 0x55);
  }
}

void mc_st_read8([[maybe_unused]] benchmark::State& state) {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerST mc_st{ITERATIONS};
  while (state.KeepRunning()) {
    [[maybe_unused]] auto t = mc_st.Read8(counter);
    counter += 1;
  }
}

void mc_st_read16([[maybe_unused]] benchmark::State& state) {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerST mc_st{ITERATIONS};
  while (state.KeepRunning()) {
    [[maybe_unused]] auto t = mc_st.Read16(counter);
    counter += 2;
  }
}

void mc_st_read32([[maybe_unused]] benchmark::State& state) {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerST mc_st{ITERATIONS};
  while (state.KeepRunning()) {
    [[maybe_unused]] auto t = mc_st.Read32(counter);
    counter += 4;
  }
}

void mc_st_read64([[maybe_unused]] benchmark::State& state) {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerST mc_st{ITERATIONS};
  while (state.KeepRunning()) {
    [[maybe_unused]] auto t = mc_st.Read64(counter);
    counter += 8;
  }
}

void mc_st_fetch8([[maybe_unused]] benchmark::State& state) {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerST mc_st{ITERATIONS};
  while (state.KeepRunning()) {
    [[maybe_unused]] auto t = mc_st.Fetch8(counter);
  }
}

void mc_st_fetch16([[maybe_unused]] benchmark::State& state) {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerST mc_st{ITERATIONS};
  while (state.KeepRunning()) {
    [[maybe_unused]] auto t = mc_st.Fetch16(counter);                }
}

void mc_st_fetch32([[maybe_unused]] benchmark::State& state) {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerST mc_st{ITERATIONS};
  while (state.KeepRunning()) {
    [[maybe_unused]] auto t = mc_st.Fetch32(counter);                }
}

void mc_st_fetch64([[maybe_unused]] benchmark::State& state) {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerST mc_st{ITERATIONS};
  while (state.KeepRunning()) {
    [[maybe_unused]] auto t = mc_st.Fetch64(counter);                }
}

BENCHMARK(mc_st_load8)->Iterations(ITERATIONS);
BENCHMARK(mc_st_load16)->Iterations(ITERATIONS / 2);
BENCHMARK(mc_st_load32)->Iterations(ITERATIONS / 4);
BENCHMARK(mc_st_load64)->Iterations(ITERATIONS / 8);
BENCHMARK(mc_st_read8)->Iterations(ITERATIONS);
BENCHMARK(mc_st_read16)->Iterations(ITERATIONS / 2);
BENCHMARK(mc_st_read32)->Iterations(ITERATIONS / 4);
BENCHMARK(mc_st_read64)->Iterations(ITERATIONS / 8);
BENCHMARK(mc_st_fetch8)->Iterations(ITERATIONS);
BENCHMARK(mc_st_fetch16)->Iterations(ITERATIONS / 2);
BENCHMARK(mc_st_fetch32)->Iterations(ITERATIONS / 4);
BENCHMARK(mc_st_fetch64)->Iterations(ITERATIONS / 8);
