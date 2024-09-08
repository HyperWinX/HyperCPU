#include "gtest/gtest.h"
#include <climits>
#include <gtest/gtest.h>

#define private public
#include <core/memory_controller/memory_controller_mt.hpp>


static constexpr std::size_t MEM_SIZE = 1024;
static constexpr std::uint8_t BYTE = 0x55;
static constexpr std::uint16_t WORD = 0x5555;
static constexpr std::uint32_t DWORD = 0x55555555;
static constexpr std::uint64_t QWORD = 0x5555555555555555;

class mc_mt_test : public testing::Test {
  protected:
    hypercpu::memory_controller_mt mcmt;
    char tmp_buffer[MEM_SIZE];
    std::size_t counter;
    mc_mt_test() : mcmt(MEM_SIZE), counter(0) {
      std::memset(tmp_buffer, BYTE, MEM_SIZE);
    }
};

class mc_mt_fail_test : public testing::Test {
  protected:
    hypercpu::memory_controller_mt mcmt;
    std::size_t counter;
    mc_mt_fail_test() : mcmt(MEM_SIZE), counter(LONG_MAX) {}
};

class mc_mt_near_fail_test : public testing::Test {
  protected:
    hypercpu::memory_controller_mt mcmt;
    std::size_t counter;
    mc_mt_near_fail_test() : mcmt(MEM_SIZE) {}
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
    mcmt._load32(counter, DWORD);

  ASSERT_TRUE(std::memcmp(mcmt.memory, tmp_buffer, MEM_SIZE) == 0);
}

TEST_F(mc_mt_test, LOAD64) {
  for (std::size_t i = 0; i < MEM_SIZE / 8; ++i, counter += 8)
    mcmt._load64(counter, QWORD);

  ASSERT_TRUE(std::memcmp(mcmt.memory, tmp_buffer, MEM_SIZE) == 0);
}

TEST_F(mc_mt_test, FETCH8) {
  mcmt._load64(counter, QWORD);

  for (std::size_t i = 0; i < 8; ++i)
    ASSERT_EQ(mcmt.fetch8(counter), BYTE);
}

TEST_F(mc_mt_test, FETCH16) {
  mcmt._load64(counter, QWORD);

  for (std::size_t i = 0; i < 4; ++i)
    ASSERT_EQ(mcmt.fetch16(counter), WORD);
}

TEST_F(mc_mt_test, FETCH32) {
  mcmt._load64(counter, QWORD);

  for (std::size_t i = 0; i < 2; ++i)
    ASSERT_EQ(mcmt.fetch32(counter), DWORD);
}

TEST_F(mc_mt_test, FETCH64) {
  mcmt._load64(counter, QWORD);

  ASSERT_EQ(mcmt.fetch64(counter), QWORD);
}

TEST_F(mc_mt_fail_test, LOAD8) {
  ASSERT_EXIT(mcmt._load8(counter, BYTE), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_fail_test, LOAD16) {
  ASSERT_EXIT(mcmt._load16(counter, WORD), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_fail_test, LOAD32) {
  ASSERT_EXIT(mcmt._load32(counter, DWORD), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_fail_test, LOAD64) {
  ASSERT_EXIT(mcmt._load64(counter, QWORD), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_fail_test, FETCH8) {
  ASSERT_EXIT(mcmt.fetch8(counter), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_fail_test, FETCH16) {
  ASSERT_EXIT(mcmt.fetch16(counter), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_fail_test, FETCH32) {
  ASSERT_EXIT(mcmt.fetch32(counter), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_fail_test, FETCH64) {
  ASSERT_EXIT(mcmt.fetch64(counter), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_near_fail_test, LOAD8) {
  counter = 1023;
  ASSERT_EXIT({mcmt._load8(counter, BYTE); exit(0); }, ::testing::ExitedWithCode(0), "");
  ++counter;
  ASSERT_EXIT({mcmt._load8(counter, BYTE); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_near_fail_test, LOAD16) {
  counter = 1022;
  ASSERT_EXIT({mcmt._load16(counter, WORD); exit(0); }, ::testing::ExitedWithCode(0), "");
  counter = 1023;
  ASSERT_EXIT({mcmt._load16(counter, WORD); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_near_fail_test, LOAD32) {
  counter = 1020;
  ASSERT_EXIT({mcmt._load32(counter, DWORD); exit(0); }, ::testing::ExitedWithCode(0), "");
  counter = 1021;
  ASSERT_EXIT({mcmt._load32(counter, DWORD); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_near_fail_test, LOAD64) {
  counter = 1016;
  ASSERT_EXIT({mcmt._load64(counter, QWORD); exit(0); }, ::testing::ExitedWithCode(0), "");
  counter = 1017;
  ASSERT_EXIT({mcmt._load64(counter, QWORD); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_near_fail_test, FETCH8) {
  counter = 1023;
  ASSERT_EXIT({mcmt.fetch8(counter); exit(0); }, ::testing::ExitedWithCode(0), "");
  counter = 1024;
  ASSERT_EXIT({mcmt.fetch8(counter); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_near_fail_test, FETCH16) {
  counter = 1022;
  ASSERT_EXIT({mcmt.fetch16(counter); exit(0); }, ::testing::ExitedWithCode(0), "");
  counter = 1023;
  ASSERT_EXIT({mcmt.fetch16(counter); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_near_fail_test, FETCH32) {
  counter = 1020;
  ASSERT_EXIT({mcmt.fetch32(counter); exit(0); }, ::testing::ExitedWithCode(0), "");
  counter = 1021;
  ASSERT_EXIT({mcmt.fetch32(counter); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_near_fail_test, FETCH64) {
  counter = 1016;
  ASSERT_EXIT({mcmt.fetch64(counter); exit(0); }, ::testing::ExitedWithCode(0), "");
  counter = 1017;
  ASSERT_EXIT({mcmt.fetch64(counter); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}