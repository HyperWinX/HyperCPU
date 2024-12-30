#pragma once

namespace hypercpu {
  template<typename T>
  constexpr T& deref(void* ptr) {
    return *static_cast<T*>(ptr);
  }
}