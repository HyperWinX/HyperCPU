#include <gtest/gtest.h>

#define private public
#include <core/memory_controller/memory_controller_mt.hpp>


static constexpr std::size_t MEM_SIZE = 1024;
static constexpr std::uint8_t BYTE = 0x55;
static constexpr std::uint16_t WORD = 0x5555;
static constexpr std::uint32_t QWORD = 0x55555555;

class mc_mt_test : public testing::Test {
  protected:
    hypercpu::memory_controller_mt mcmt;
    char tmp_buffer[MEM_SIZE];
    std::size_t counter;
    mc_mt_test() : mcmt(MEM_SIZE), counter(0) {
      std::memset(tmp_buffer, BYTE, MEM_SIZE);
    }
};


TEST_F(mc_mt_test, LOAD8) {
  for (std::size_t i = 0; i < MEM_SIZE; ++i, ++counter)
    mcmt._load8(counter, BYTE);

  ASSERT_TRUE(std::memcmp(mcmt.memory,&tmp_buffer, MEM_SIZE) == 0);
}

TEST_F(mc_mt_test, LOAD16) {
  for (std::size_t i = 0; i < MEM_SIZE / 2; ++i, counter += 2)
    mcmt._load16(counter, WORD);

  ASSERT_TRUE(std::memcmp(mcmt.memory, tmp_buffer, MEM_SIZE) == 0);
}

TEST_F(mc_mt_test, LOAD32) {
  for (std::size_t i = 0; i < MEM_SIZE / 4; ++i, counter += 4)
    mcmt._load32(counter, QWORD);

  ASSERT_TRUE(std::memcmp(mcmt.memory, tmp_buffer, MEM_SIZE) == 0);
}