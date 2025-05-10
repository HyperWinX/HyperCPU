#pragma once

#include "PCH/CStd.hpp"

namespace HyperCPU {
  template <typename To, typename From>
  constexpr To bit_cast(const From& src) noexcept {
    To dst;
    std::memcpy(&dst, &src, std::min(sizeof(To), sizeof(From)));
    return dst;
  }

  template <typename To, typename From>
  constexpr To bit_cast_s(const From& src) noexcept {
    static_assert(sizeof(To) == sizeof(From), "Type sizes should be the same");
    To dst;
    std::memcpy(&dst, &src, sizeof(To));
    return dst;
  }

  template <typename To, typename From>
  constexpr To bit_cast_from(const From* src) noexcept {
    To dst;
    std::memcpy(&dst, src, sizeof(To));
    return dst;
  }
} // namespace HyperCPU
