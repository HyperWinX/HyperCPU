#include <gtest/gtest.h>

#define private public
#include <core/cpu/cpu.hpp>

static constexpr std::uint64_t FULL_CONST = 0x01020304050607;
static constexpr std::uint32_t CONSTH = 0x07060504;

TEST(cpu_init, REGS_ARE_INITIALIZED) {
  hypercpu::cpu cpu{1, 4096};
  for (std::size_t i = 0; i < 13; ++i)
    cpu.data[i] = FULL_CONST;

  ASSERT_EQ(*cpu.x0, FULL_CONST);
  ASSERT_EQ(*cpu.x1, FULL_CONST);
  ASSERT_EQ(*cpu.x2, FULL_CONST);
  ASSERT_EQ(*cpu.x3, FULL_CONST);
  ASSERT_EQ(*cpu.x4, FULL_CONST);
  ASSERT_EQ(*cpu.x5, FULL_CONST);
  ASSERT_EQ(*cpu.x6, FULL_CONST);
  ASSERT_EQ(*cpu.x7, FULL_CONST);
  ASSERT_EQ(*cpu.xh0, CONSTH);
}