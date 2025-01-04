#pragma once

#include <gtest/gtest.h>

#define private public
#include <core/cpu/cpu.hpp>
#include <core/cpu/decode/decoder.hpp>
#include <core/cpu/decode/i_decoder.hpp>
#include <core/cpu/instructions/flags.hpp>
#include <core/cpu/instructions/opcodes.hpp>
#include <core/cpu/instructions/registers.hpp>
#include <core/memory_controller/memory_controller_st.hpp>
#include <core/memory_controller/memory_controller_mt.hpp>

static constexpr std::size_t MEM_SIZE = 4096;
static constexpr std::size_t MEM_FIXTURE_MEM_SIZE = 1024;
static constexpr std::size_t MEM_PTR = 0x0102030405060708;

class mc_mt_test : public testing::Test {
  protected:
    hypercpu::memory_controller_mt mcmt;
    char tmp_buffer[MEM_FIXTURE_MEM_SIZE];
    std::size_t counter;
    mc_mt_test() : mcmt(MEM_FIXTURE_MEM_SIZE), counter(0) {
      std::memset(tmp_buffer, 0x55, MEM_FIXTURE_MEM_SIZE);
    }
};

class mc_mt_fail_test : public testing::Test {
  protected:
    hypercpu::memory_controller_mt mcmt;
    std::size_t counter;
    mc_mt_fail_test() : mcmt(MEM_FIXTURE_MEM_SIZE), counter(LONG_MAX) {}
};

class mc_mt_near_fail_test : public testing::Test {
  protected:
    hypercpu::memory_controller_mt mcmt;
    std::size_t counter;
    mc_mt_near_fail_test() : mcmt(MEM_FIXTURE_MEM_SIZE) {}
};

class mc_st_test : public testing::Test {
  protected:
    hypercpu::memory_controller_st mcmt;
    char tmp_buffer[MEM_FIXTURE_MEM_SIZE];
    std::size_t counter;
    mc_st_test() : mcmt(MEM_FIXTURE_MEM_SIZE), counter(0) {
      std::memset(tmp_buffer, 0x55, MEM_FIXTURE_MEM_SIZE);
    }
};

class mc_st_fail_test : public testing::Test {
  protected:
    hypercpu::memory_controller_st mcmt;
    char tmp_buffer[MEM_FIXTURE_MEM_SIZE];
    std::size_t counter;
    mc_st_fail_test() : mcmt(MEM_FIXTURE_MEM_SIZE), counter(LONG_MAX) {
      std::memset(tmp_buffer, 0x55, MEM_FIXTURE_MEM_SIZE);
    }
};

class mc_st_near_fail_test : public testing::Test {
  protected:
    hypercpu::memory_controller_st mcmt;
    std::size_t counter;
    mc_st_near_fail_test() : mcmt(MEM_FIXTURE_MEM_SIZE) {}
};

class decoder_test : public ::testing::Test {
protected:
  hypercpu::decoder decoder;
  std::size_t counter;

  decoder_test() = default;

  void SetUp() {
    decoder = hypercpu::decoder(new hypercpu::memory_controller_st(MEM_SIZE), &counter, nullptr);
    counter = 0;
    
  }

  void TearDown() {
    delete dynamic_cast<hypercpu::memory_controller_st*>(decoder.mem_controller);
    decoder.~decoder();
  }
};

class cpu_test : public ::testing::Test {
protected:
  hypercpu::cpu cpu;

  cpu_test() : cpu(1, 4096) { }
};

class operand_eval_test : public ::testing::Test {
protected:
  hypercpu::cpu cpu;
  std::pair<void*, void*> result;

  operand_eval_test() : cpu(1, 4096) { }
};

class stack_test : public ::testing::Test {
protected:
  hypercpu::cpu cpu;

  stack_test() : cpu(1, 4096) {
    *cpu.xbp = 1024;
    *cpu.xsp = 1024;
  }
};

class ivt_init_test : public ::testing::Test {
protected:
  hypercpu::cpu cpu;

  ivt_init_test() : cpu(1, 4096) {

  }
};

class exception_test : public ::testing::Test {
protected:
  hypercpu::cpu cpu;

  exception_test() : cpu(1, 4096) { }

  virtual void SetUp() {
    *cpu.xsp = 512;
    *cpu.xbp = 512;
    *cpu.xivt = 2048;
    cpu.mem_controller->load64(2048, 1536);
    cpu.mem_controller->load64(2056, 1536);
    cpu.mem_controller->load64(2064, 1536);
    cpu.mem_controller->load64(1536, hypercpu::opcode::HALT);
    cpu.mem_controller->load64(1538, hypercpu::operand_types::NONE);
  }
};