#include <type_traits>

#include <cstdlib>
#include <cstring>

namespace hypercpu {
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