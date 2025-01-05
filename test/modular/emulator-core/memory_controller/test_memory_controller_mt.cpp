#include <climits>
#include <gtest/gtest.h>

#include <fixtures.hpp>

#define private public
#include <core/memory_controller/memory_controller_mt.hpp>


static constexpr std::uint8_t BYTE = 0x55;
static constexpr std::uint16_t WORD = 0x5555;
static constexpr std::uint32_t DWORD = 0x55555555;
static constexpr std::uint64_t QWORD = 0x5555555555555555;

TEST_F(mc_mt_test, LOAD8) {
  for (std::size_t i = 0; i < MEM_FIXTURE_MEM_SIZE; i++, counter++)
    mcmt.load8(counter, BYTE);
    
  ASSERT_TRUE(std::memcmp(mcmt.memory,&tmp_buffer, MEM_FIXTURE_MEM_SIZE) == 0);
}

TEST_F(mc_mt_test, LOAD16) {
  for (std::size_t i = 0; i < MEM_FIXTURE_MEM_SIZE / 2; ++i, counter += 2)
    mcmt.load16(counter, WORD);

  ASSERT_TRUE(std::memcmp(mcmt.memory, tmp_buffer, MEM_FIXTURE_MEM_SIZE) == 0);
}

TEST_F(mc_mt_test, LOAD32) {
  for (std::size_t i = 0; i < MEM_FIXTURE_MEM_SIZE / 4; ++i, counter += 4)
    mcmt.load32(counter, DWORD);

  ASSERT_TRUE(std::memcmp(mcmt.memory, tmp_buffer, MEM_FIXTURE_MEM_SIZE) == 0);
}

TEST_F(mc_mt_test, LOAD64) {
  for (std::size_t i = 0; i < MEM_FIXTURE_MEM_SIZE / 8; ++i, counter += 8)
    mcmt.load64(counter, QWORD);

  ASSERT_TRUE(std::memcmp(mcmt.memory, tmp_buffer, MEM_FIXTURE_MEM_SIZE) == 0);
}

TEST_F(mc_mt_test, FETCH8) {
  mcmt.load64(counter, QWORD);

  for (std::size_t i = 0; i < 8; ++i)
    ASSERT_EQ(mcmt.fetch8(counter), BYTE);
}

TEST_F(mc_mt_test, FETCH16) {
  mcmt.load64(counter, QWORD);

  for (std::size_t i = 0; i < 4; ++i)
    ASSERT_EQ(mcmt.fetch16(counter), WORD);
}

TEST_F(mc_mt_test, FETCH32) {
  mcmt.load64(counter, QWORD);

  for (std::size_t i = 0; i < 2; ++i)
    ASSERT_EQ(mcmt.fetch32(counter), DWORD);
}

TEST_F(mc_mt_test, FETCH64) {
  mcmt.load64(counter, QWORD);

  ASSERT_EQ(mcmt.fetch64(counter), QWORD);
}

TEST_F(mc_mt_test, READ8) {
  mcmt.load64(counter, QWORD);

  for (std::size_t i = 0; i < 8; ++i, ++counter)
    ASSERT_EQ(mcmt.read8(counter), BYTE);
}

TEST_F(mc_mt_test, READ16) {
  mcmt.load64(counter, QWORD);

  for (std::size_t i = 0; i < 4; ++i, counter += 2)
    ASSERT_EQ(mcmt.read16(counter), WORD);
}

TEST_F(mc_mt_test, READ32) {
  mcmt.load64(counter, QWORD);

  for (std::size_t i = 0; i < 2; ++i, counter += 4)
    ASSERT_EQ(mcmt.read32(counter), DWORD);
}

TEST_F(mc_mt_test, READ64) {
  mcmt.load64(counter, QWORD);

  ASSERT_EQ(mcmt.read64(counter), QWORD);
}

TEST_F(mc_mt_fail_test, LOAD8) {
  ASSERT_EXIT(mcmt.load8(counter, BYTE), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_fail_test, LOAD16) {
  ASSERT_EXIT(mcmt.load16(counter, WORD), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_fail_test, LOAD32) {
  ASSERT_EXIT(mcmt.load32(counter, DWORD), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_fail_test, LOAD64) {
  ASSERT_EXIT(mcmt.load64(counter, QWORD), ::testing::KilledBySignal(SIGABRT), "");
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

TEST_F(mc_mt_fail_test, READ8) {
  ASSERT_EXIT(mcmt.read8(counter), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_fail_test, READ16) {
  ASSERT_EXIT(mcmt.read16(counter), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_fail_test, READ32) {
  ASSERT_EXIT(mcmt.read32(counter), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_fail_test, READ64) {
  ASSERT_EXIT(mcmt.read64(counter), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_near_fail_test, LOAD8) {
  counter = 1023;
  ASSERT_EXIT({mcmt.load8(counter, BYTE); exit(0); }, ::testing::ExitedWithCode(0), "");
  ++counter;
  ASSERT_EXIT({mcmt.load8(counter, BYTE); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_near_fail_test, LOAD16) {
  counter = 1022;
  ASSERT_EXIT({mcmt.load16(counter, WORD); exit(0); }, ::testing::ExitedWithCode(0), "");
  counter = 1023;
  ASSERT_EXIT({mcmt.load16(counter, WORD); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_near_fail_test, LOAD32) {
  counter = 1020;
  ASSERT_EXIT({mcmt.load32(counter, DWORD); exit(0); }, ::testing::ExitedWithCode(0), "");
  counter = 1021;
  ASSERT_EXIT({mcmt.load32(counter, DWORD); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_near_fail_test, LOAD64) {
  counter = 1016;
  ASSERT_EXIT({mcmt.load64(counter, QWORD); exit(0); }, ::testing::ExitedWithCode(0), "");
  counter = 1017;
  ASSERT_EXIT({mcmt.load64(counter, QWORD); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
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

TEST_F(mc_mt_near_fail_test, READ8) {
  counter = 1023;
  ASSERT_EXIT({mcmt.read8(counter); exit(0); }, ::testing::ExitedWithCode(0), "");
  counter = 1024;
  ASSERT_EXIT({mcmt.read8(counter); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_near_fail_test, READ16) {
  counter = 1022;
  ASSERT_EXIT({mcmt.read16(counter); exit(0); }, ::testing::ExitedWithCode(0), "");
  counter = 1023;
  ASSERT_EXIT({mcmt.read16(counter); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_near_fail_test, READ32) {
  counter = 1020;
  ASSERT_EXIT({mcmt.read32(counter); exit(0); }, ::testing::ExitedWithCode(0), "");
  counter = 1021;
  ASSERT_EXIT({mcmt.read32(counter); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(mc_mt_near_fail_test, READ64) {
  counter = 1016;
  ASSERT_EXIT({mcmt.read64(counter); exit(0); }, ::testing::ExitedWithCode(0), "");
  counter = 1017;
  ASSERT_EXIT({mcmt.read64(counter); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}