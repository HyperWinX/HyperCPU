
#include <gtest/gtest.h>

#include <core/cpu/fetch/fetcher.hpp>
#include <core/cpu/instructions/opcodes.hpp>
#include <core/cpu/instructions/flags.hpp>
#include <core/memory_controller/memory_controller_st.hpp>

static constexpr std::size_t MEM_SIZE = 1024;

class fetcher_testing : public testing::Test {
  protected:
    hypercpu::memory_controller_st mem_controller;
    hypercpu::fetcher fetchr;
    std::size_t offset;
    fetcher_testing() : mem_controller(MEM_SIZE), fetchr(&mem_controller, &offset), offset(0) {}
};

TEST_F(fetcher_testing, FETCH_INSTRUCTION) {
  mem_controller._load16(offset, hypercpu::MOV);
  offset += 2;
  mem_controller._load8(offset, hypercpu::b16);
  offset = 0;
  hypercpu::fetched_instruction instr = fetchr.fetch();

  ASSERT_EQ(instr.instruction, hypercpu::MOV);
  ASSERT_EQ(instr.flags, hypercpu::b16);
}