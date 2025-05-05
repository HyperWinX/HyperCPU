#pragma once

#include "pch.hpp"

#define _MICROOP [[gnu::always_inline]] static constexpr inline

namespace HyperCPU {
  namespace StdALU {
    template <typename T>
    concept UInt = std::is_integral_v<T> && std::is_unsigned_v<T>;

    template <UInt T>
    _MICROOP T __hcpu_add(const T& a, const T& b) {
      return a + b;
    }

    template <UInt T>
    _MICROOP T __hcpu_sub(const T& a, const T& b) {
      return a - b;
    }

    template <UInt T>
    _MICROOP T __hcpu_mul(const T& a, const T& b) {
      return a * b;
    }

    template <UInt T>
    _MICROOP T __hcpu_div(const T& a, const T& b) {
      return a / b;
    }

    template <UInt T>
    _MICROOP T __hcpu_div_remainder(const T& a, const T& b) {
      return a % b;
    }

    template <UInt T>
    _MICROOP T __hcpu_and(const T& a, const T& b) {
      return a & b;
    }

    template <UInt T>
    _MICROOP T __hcpu_not(const T& a) {
      return ~a;
    }

    template <UInt T>
    _MICROOP T __hcpu_or(const T& a, const T& b) {
      return a | b;
    }

    template <UInt T>
    _MICROOP std::int8_t __hcpu_cmp(const T a, const T b) {
      return (a > b) - (a < b);
    }
  } // namespace StdALU
} // namespace HyperCPU

// Simplify switching implementations
namespace HyperALU {
  using namespace HyperCPU::StdALU;
}
