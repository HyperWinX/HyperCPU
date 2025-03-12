#pragma once

#include <cstdlib>
#include <cstring>

#include <algorithm>


namespace HyperCPU {
  template<typename To, typename From>
  constexpr To bit_cast(const From& src) noexcept {
    To dst;
    std::memcpy(&dst, &src, std::min(sizeof(To), sizeof(From)));
    return dst;
  }

  template<typename To, typename From>
  constexpr To bit_cast_from(const From* src) noexcept {
    To dst;
    std::memcpy(&dst, src, sizeof(To));
    return dst;
  }
}