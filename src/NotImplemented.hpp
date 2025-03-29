#pragma once

#include <Logger/Logger.hpp>

namespace HyperCPU {
  [[gnu::always_inline]]
  static inline void PrintUnsupported(std::string msg) {
    std::cerr << msg << '\n';
    std::exit(1);
  }
}
