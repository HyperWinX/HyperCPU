#pragma once

namespace HyperCPU {
  template <typename T>
  constexpr bool SubtractionWillUnderflow(T& a, T& b) {
    return b > a;
  }
} // namespace HyperCPU