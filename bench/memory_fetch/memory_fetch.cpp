#include <hbench.hpp>
#include <core/memory_controller/memory_controller_mt.hpp>
#include <core/memory_controller/memory_controller_st.hpp>

static constexpr std::size_t ITERATIONS = 1024 * 1024 * 32;

extern "C" {

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

void _bench_mc_st_fetch8() {
  std::size_t counter = 0;
  hypercpu::memory_controller_st mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS; ++i)
    mc_st._fetch8(counter);
}

void _bench_mc_st_fetch16() {
  std::size_t counter = 0;
  hypercpu::memory_controller_st mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 2; ++i)
    mc_st._fetch16(counter);
}

void _bench_mc_st_fetch32() {
  std::size_t counter = 0;
  hypercpu::memory_controller_st mc_st{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 4; ++i)
    mc_st._fetch32(counter);
}

void _bench_mc_mt_fetch8() {
  std::size_t counter = 0;
  hypercpu::memory_controller_mt mc_mt{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS; ++i)
    mc_mt._fetch8(counter);
}

void _bench_mc_mt_fetch16() {
  std::size_t counter = 0;
  hypercpu::memory_controller_mt mc_mt{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 2; ++i)
    mc_mt._fetch16(counter);
}

void _bench_mc_mt_fetch32() {
  std::size_t counter = 0;
  hypercpu::memory_controller_mt mc_mt{ITERATIONS};
  for (std::size_t i = 0; i < ITERATIONS / 4; ++i)
    mc_mt._fetch32(counter);
}

}

int main() {
  BENCH_AVG(_bench_mc_st_load8(), 5);
  BENCH_AVG(_bench_mc_st_load16(), 5);
  BENCH_AVG(_bench_mc_st_load32(), 5);

  BENCH_AVG(_bench_mc_mt_load8(), 5);
  BENCH_AVG(_bench_mc_mt_load16(), 5);
  BENCH_AVG(_bench_mc_mt_load32(), 5);

  BENCH_AVG(_bench_mc_st_fetch8(), 5);
  BENCH_AVG(_bench_mc_st_fetch16(), 5);
  BENCH_AVG(_bench_mc_st_fetch32(), 5);

  BENCH_AVG(_bench_mc_mt_fetch8(), 5);
  BENCH_AVG(_bench_mc_mt_fetch16(), 5);
  BENCH_AVG(_bench_mc_mt_fetch32(), 5);
}