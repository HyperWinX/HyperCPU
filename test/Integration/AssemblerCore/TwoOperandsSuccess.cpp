#include "gtest/gtest.h"
#include <cstdint>
#include <fixtures.hpp>

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_R_R) {
  std::string data = "mov x0, x1;"
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_R_RM) {
  std::string data = "mov x0, [x1];";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_R_M) {
  std::string data = "mov x0, [0u];";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_R_IMM) {
  std::string data = "mov x0, 0u;";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}
