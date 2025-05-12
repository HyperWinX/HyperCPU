#pragma once

#include "Emulator/Misc/bit_cast.hpp"
#include "PCH/CStd.hpp"

namespace HyperCPU {
  template <std::integral T>
  constexpr T byteswap(T val) {
    auto repr = bit_cast_s<std::array<std::byte, sizeof(T)>>(val);
    std::ranges::reverse(repr);
    return bit_cast_s<T>(repr);
  }
} // namespace HyperCPU
