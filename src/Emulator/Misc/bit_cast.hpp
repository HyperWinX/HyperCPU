#pragma once

#include <cstdlib>
#include <cstring>


namespace HyperCPU {
  template<typename To, typename From>
  constexpr To bit_cast(const From& src) noexcept {
    To dst;
    std::memcpy(&dst, &src, sizeof(To));
    return dst;
  }

  template<typename To, typename From>
  constexpr To bit_cast_from(const From* src) noexcept {
    To dst;
    std::memcpy(&dst, src, sizeof(To));
    return dst;
  }
}