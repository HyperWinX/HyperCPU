#include <Emulator/Core/MemoryController/MemoryControllerMT.hpp>
#include <Emulator/Core/MemoryController/MemoryControllerST.hpp>

#include <benchmark/benchmark.h>

static constexpr std::size_t ITERATIONS = 1024 * 1024 * 32;

class MC_ST : public benchmark::Fixture {
public:
  HyperCPU::MemoryControllerST mc_st;

  MC_ST() : mc_st(ITERATIONS) { }
};

class MC_MT : public benchmark::Fixture {
public:
  HyperCPU::MemoryControllerMT mc_mt;

  MC_MT() : mc_mt(ITERATIONS) { }
};

void _bench_mc_stload8() {

}

void _bench_mc_stload16() {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerST mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 2; ++i, counter += 2)
    mc_st.Load16(counter, 0x55AA);
}

void _bench_mc_stload32() {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerST mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 4; ++i, counter += 4)
    mc_st.Load32(counter, 0x55AA55AA);
}

void _bench_mc_stload64() {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerST mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 8; ++i, counter += 8)
    mc_st.Load64(counter, 0x55AA55AA55AA55AA);
}

void _bench_mc_mtload8() {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerMT mc_mt{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS; ++i, ++counter)
    mc_mt.Load8(counter, 0x55);
}

void _bench_mc_mtload16() {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerMT mc_mt{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 2; ++i, counter += 2)
    mc_mt.Load16(counter, 0x55AA);
}

void _bench_mc_mtload32() {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerMT mc_mt{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 4; ++i, counter += 4)
    mc_mt.Load32(counter, 0x55AA55AA);
}

void _bench_mc_mtload64() {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerMT mc_mt{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 8; ++i, counter += 8)
    mc_mt.Load64(counter, 0x55AA55AA55AA55AA);
}

void _bench_mc_stread8() {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerST mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS; ++i, ++counter)
    mc_st.Read8(counter);
}

void _bench_mc_stread16() {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerST mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 2; ++i, counter += 2)
    mc_st.Load16(counter, 0x55AA);
}

void _bench_mc_stread32() {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerST mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 4; ++i, counter += 4)
    mc_st.Load32(counter, 0x55AA55AA);
}

void _bench_mc_stread64() {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerST mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 8; ++i, counter += 8)
    mc_st.Load64(counter, 0x55AA55AA55AA55AA);
}

void _bench_mc_mtread8() {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerMT mc_mt{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS; ++i, ++counter)
    mc_mt.Load8(counter, 0x55);
}

void _bench_mc_mtread16() {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerMT mc_mt{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 2; ++i, counter += 2)
    mc_mt.Load16(counter, 0x55AA);
}

void _bench_mc_mtread32() {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerMT mc_mt{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 4; ++i, counter += 4)
    mc_mt.Load32(counter, 0x55AA55AA);
}

void _bench_mc_mtread64() {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerMT mc_mt{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 8; ++i, counter += 8)
    mc_mt.Load64(counter, 0x55AA55AA55AA55AA);
}

void _bench_mc_stfetch8() {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerST mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS; ++i)
    mc_st.Fetch8(counter);
}

void _bench_mc_stfetch16() {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerST mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 2; ++i)
    mc_st.Fetch16(counter);
}

void _bench_mc_stfetch32() {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerST mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 4; ++i)
    mc_st.Fetch32(counter);
}

void _bench_mc_stfetch64() {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerST mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 8; ++i)
    mc_st.Fetch64(counter);
}

void _bench_mc_mtfetch8() {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerMT mc_mt{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS; ++i)
    mc_mt.Fetch8(counter);
}

void _bench_mc_mtfetch16() {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerMT mc_mt{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 2; ++i)
    mc_mt.Fetch16(counter);
}

void _bench_mc_mtfetch32() {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerMT mc_mt{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 4; ++i)
    mc_mt.Fetch32(counter);
}

void _bench_mc_mtfetch64() {
  std::size_t counter = 0;
  HyperCPU::MemoryControllerMT mc_mt{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 8; ++i)
    mc_mt.Fetch32(counter);
}

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

BENCHMARK(mc_st_load8)->Iterations(ITERATIONS);
BENCHMARK(mc_st_load16)->Iterations(ITERATIONS / 2);
BENCHMARK(mc_st_load32)->Iterations(ITERATIONS / 4);
BENCHMARK(mc_st_load64)->Iterations(ITERATIONS / 8);
