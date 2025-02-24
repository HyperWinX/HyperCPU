#pragma once

#include <type_traits>

#define _MICROOP [[gnu::always_inline]] static constexpr inline


namespace HyperCPU{
  namespace StdALU {
    template<typename T>
    concept UInt = std::is_integral_v<T> && std::is_unsigned_v<T>;

    template<UInt T>
    _MICROOP T __hcpu_add(const T& a, const T& b) {
      return a + b;
    }
  }
}

// Simplify switching implementations
using HyperALU = HyperCPU::StdALU;
