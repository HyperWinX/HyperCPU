#include <hbench.hpp>
#include <core/memory_controller/MemoryControllerMT.hpp>
#include <core/memory_controller/memory_controller_st.hpp>


static constexpr std::size_t ITERATIONS = 1024 * 1024 * 32;


void _bench_mc_stload8() {
  std::size_t counter = 0;
  HyperCPU::memory_controller_st mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS; ++i, ++counter)
    mc_st.Load8(counter, 0x55);
}

void _bench_mc_stload16() {
  std::size_t counter = 0;
  HyperCPU::memory_controller_st mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 2; ++i, counter += 2)
    mc_st.Load16(counter, 0x55AA);
}

void _bench_mc_stload32() {
  std::size_t counter = 0;
  HyperCPU::memory_controller_st mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 4; ++i, counter += 4)
    mc_st.Load32(counter, 0x55AA55AA);
}

void _bench_mc_stload64() {
  std::size_t counter = 0;
  HyperCPU::memory_controller_st mc_st{ITERATIONS};
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
  HyperCPU::memory_controller_st mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS; ++i, ++counter)
    mc_st.Read8(counter);
}

void _bench_mc_stread16() {
  std::size_t counter = 0;
  HyperCPU::memory_controller_st mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 2; ++i, counter += 2)
    mc_st.Load16(counter, 0x55AA);
}

void _bench_mc_stread32() {
  std::size_t counter = 0;
  HyperCPU::memory_controller_st mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 4; ++i, counter += 4)
    mc_st.Load32(counter, 0x55AA55AA);
}

void _bench_mc_stread64() {
  std::size_t counter = 0;
  HyperCPU::memory_controller_st mc_st{ITERATIONS};
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
  HyperCPU::memory_controller_st mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS; ++i)
    mc_st.Fetch8(counter);
}

void _bench_mc_stfetch16() {
  std::size_t counter = 0;
  HyperCPU::memory_controller_st mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 2; ++i)
    mc_st.Fetch16(counter);
}

void _bench_mc_stfetch32() {
  std::size_t counter = 0;
  HyperCPU::memory_controller_st mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 4; ++i)
    mc_st.Fetch32(counter);
}

void _bench_mc_stfetch64() {
  std::size_t counter = 0;
  HyperCPU::memory_controller_st mc_st{ITERATIONS};
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


int main() {
  BENCH_AVG(_bench_mc_stload8(), 5);
  BENCH_AVG(_bench_mc_stload16(), 5);
  BENCH_AVG(_bench_mc_stload32(), 5);
  BENCH_AVG(_bench_mc_stload64(), 5);

  BENCH_AVG(_bench_mc_mtload8(), 5);
  BENCH_AVG(_bench_mc_mtload16(), 5);
  BENCH_AVG(_bench_mc_mtload32(), 5);
  BENCH_AVG(_bench_mc_mtload64(), 5);

  BENCH_AVG(_bench_mc_stread8(), 5);
  BENCH_AVG(_bench_mc_stread16(), 5);
  BENCH_AVG(_bench_mc_stread32(), 5);
  BENCH_AVG(_bench_mc_stread64(), 5);

  BENCH_AVG(_bench_mc_mtread8(), 5);
  BENCH_AVG(_bench_mc_mtread16(), 5);
  BENCH_AVG(_bench_mc_mtread32(), 5);
  BENCH_AVG(_bench_mc_mtread64(), 5);

  BENCH_AVG(_bench_mc_stfetch8(), 5);
  BENCH_AVG(_bench_mc_stfetch16(), 5);
  BENCH_AVG(_bench_mc_stfetch32(), 5);
  BENCH_AVG(_bench_mc_stfetch64(), 5);

  BENCH_AVG(_bench_mc_mtfetch8(), 5);
  BENCH_AVG(_bench_mc_mtfetch16(), 5);
  BENCH_AVG(_bench_mc_mtfetch32(), 5);
  BENCH_AVG(_bench_mc_mtfetch64(), 5);
}