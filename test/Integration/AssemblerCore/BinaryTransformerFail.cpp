#include <gtest/gtest.h>

#include <fixtures.hpp>

TEST_F(ASM_BINARY_TRANSFORMER, ASM_INVALID_INSTRUCTION) {
  std::string data = "miv xlll0, xlll1;";
  EXPECT_EXIT({
    auto state(compiler.TransformToIR(data));
    auto binary = compiler.TransformToBinary(state);
  }, ::testing::ExitedWithCode(1), "");
}

