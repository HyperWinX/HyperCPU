#pragma once

namespace HyperCPU {
  template <typename T>
  constexpr T& deref(std::uint64_t ptr) {
    return *static_cast<T*>(ptr);
  }
} // namespace HyperCPU