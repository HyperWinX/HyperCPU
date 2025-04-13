#pragma once

#include <Emulator/Core/CPU/Util.hpp>
#include <Logger/Logger.hpp>

namespace HyperCPU {
  [[gnu::always_inline]]
  static inline void PrintUnsupported(std::string msg) {
    std::cerr << msg << '\n';
    EXIT(1);
  }
}
