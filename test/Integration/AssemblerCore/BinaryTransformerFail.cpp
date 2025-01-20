#include "gtest/gtest.h"
#include <fixtures.hpp>

TEST_F(asm_binary_transformer, ASM_INVALID_INSTRUCTION) {
  std::string data = "miv xlll0, xlll1;";
  EXPECT_EXIT({
    auto state = compiler.transform_to_IR(data);
    auto binary = compiler.transform_to_binary(state);
  }, ::testing::KilledBySignal(SIGABRT), "");
}

