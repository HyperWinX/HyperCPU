#pragma once

#include <pch.hpp>

#include <Misc/bit_cast.hpp>

namespace HyperCPU {
  template<std::integral T>
  constexpr T byteswap(T val) {
    auto repr = bit_cast_s<std::array<std::byte, sizeof(T)>>(val);
    std::ranges::reverse(repr);
    return bit_cast_s<T>(repr);
  }
}
