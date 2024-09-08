#include <hbench.hpp>
#include <core/memory_controller/memory_controller_mt.hpp>
#include <core/memory_controller/memory_controller_st.hpp>


static constexpr std::size_t ITERATIONS = 1024 * 1024 * 32;


void _bench_mc_st_load8() {
  std::size_t counter = 0;
  hypercpu::memory_controller_st mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS; ++i)
    mc_st._load8(counter, 0x55);
}

void _bench_mc_st_load16() {
  std::size_t counter = 0;
  hypercpu::memory_controller_st mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 2; ++i)
    mc_st._load16(counter, 0x55AA);
}

void _bench_mc_st_load32() {
  std::size_t counter = 0;
  hypercpu::memory_controller_st mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 4; ++i)
    mc_st._load32(counter, 0x55AA55AA);
}

void _bench_mc_st_load64() {
  std::size_t counter = 0;
  hypercpu::memory_controller_st mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 8; ++i)
    mc_st._load64(counter, 0x55AA55AA55AA55AA);
}

void _bench_mc_mt_load8() {
  std::size_t counter = 0;
  hypercpu::memory_controller_mt mc_mt{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS; ++i)
    mc_mt._load8(counter, 0x55);
}

void _bench_mc_mt_load16() {
  std::size_t counter = 0;
  hypercpu::memory_controller_mt mc_mt{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 2; ++i)
    mc_mt._load16(counter, 0x55AA);
}

void _bench_mc_mt_load32() {
  std::size_t counter = 0;
  hypercpu::memory_controller_mt mc_mt{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 4; ++i)
    mc_mt._load32(counter, 0x55AA55AA);
}

void _bench_mc_mt_load64() {
  std::size_t counter = 0;
  hypercpu::memory_controller_mt mc_mt{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 8; ++i)
    mc_mt._load64(counter, 0x55AA55AA55AA55AA);
}

void _bench_mc_stfetch8() {
  std::size_t counter = 0;
  hypercpu::memory_controller_st mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS; ++i)
    mc_st.fetch8(counter);
}

void _bench_mc_stfetch16() {
  std::size_t counter = 0;
  hypercpu::memory_controller_st mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 2; ++i)
    mc_st.fetch16(counter);
}

void _bench_mc_stfetch32() {
  std::size_t counter = 0;
  hypercpu::memory_controller_st mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 4; ++i)
    mc_st.fetch32(counter);
}

void _bench_mc_stfetch64() {
  std::size_t counter = 0;
  hypercpu::memory_controller_st mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 8; ++i)
    mc_st.fetch64(counter);
}

void _bench_mc_mtfetch8() {
  std::size_t counter = 0;
  hypercpu::memory_controller_mt mc_mt{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS; ++i)
    mc_mt.fetch8(counter);
}

void _bench_mc_mtfetch16() {
  std::size_t counter = 0;
  hypercpu::memory_controller_mt mc_mt{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 2; ++i)
    mc_mt.fetch16(counter);
}

void _bench_mc_mtfetch32() {
  std::size_t counter = 0;
  hypercpu::memory_controller_mt mc_mt{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 4; ++i)
    mc_mt.fetch32(counter);
}

void _bench_mc_mtfetch64() {
  std::size_t counter = 0;
  hypercpu::memory_controller_mt mc_mt{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 8; ++i)
    mc_mt.fetch32(counter);
}


int main() {
  BENCH_AVG(_bench_mc_st_load8(), 5);
  BENCH_AVG(_bench_mc_st_load16(), 5);
  BENCH_AVG(_bench_mc_st_load32(), 5);
  BENCH_AVG(_bench_mc_st_load64(), 5);

  BENCH_AVG(_bench_mc_mt_load8(), 5);
  BENCH_AVG(_bench_mc_mt_load16(), 5);
  BENCH_AVG(_bench_mc_mt_load32(), 5);
  BENCH_AVG(_bench_mc_mt_load64(), 5);

  BENCH_AVG(_bench_mc_stfetch8(), 5);
  BENCH_AVG(_bench_mc_stfetch16(), 5);
  BENCH_AVG(_bench_mc_stfetch32(), 5);
  BENCH_AVG(_bench_mc_stfetch64(), 5);

  BENCH_AVG(_bench_mc_mtfetch8(), 5);
  BENCH_AVG(_bench_mc_mtfetch16(), 5);
  BENCH_AVG(_bench_mc_mtfetch32(), 5);
  BENCH_AVG(_bench_mc_mtfetch64(), 5);
}