#pragma once

namespace HyperCPU {
  [[noreturn, gnu::always_inline]] void inline unreachable() {
    __builtin_unreachable();
  }
} // namespace HyperCPU
