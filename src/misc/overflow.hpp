#include <limits>

namespace hypercpu {
  template <typename T>
  constexpr bool addition_will_overflow(T& a, T& b) {
    return (b > 0 && a > std::numeric_limits<T>::max() - b);
  }
}