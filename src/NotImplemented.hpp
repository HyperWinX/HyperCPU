#pragma once

#include <Logger/Logger.hpp>

namespace HyperCPU {
  static inline constexpr void PrintUnsupported(std::string msg) {
    HCAsm::logger.Log(HyperCPU::LogLevel::ERROR, msg);
    std::exit(1);
  }
}
