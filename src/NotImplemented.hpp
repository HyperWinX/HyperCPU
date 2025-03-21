#pragma once

#include <Logger/Logger.hpp>

namespace HyperCPU {
  [[gnu::always_inline]]
  static inline void PrintUnsupported(std::string msg) {
    HCAsm::logger.Log(HyperCPU::LogLevel::ERROR, msg);
    std::exit(1);
  }
}
