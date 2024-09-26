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

static constexpr std::size_t MEM_SIZE = 4096;
static constexpr std::size_t MEM_PTR = 0x0102030405060708;

class decoder_test : public ::testing::Test {
protected:
  hypercpu::decoder decoder;
  std::size_t counter;

  decoder_test() = default;

  void SetUp() {
    decoder = hypercpu::decoder(new hypercpu::memory_controller_st(MEM_SIZE), &counter);
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