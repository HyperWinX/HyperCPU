#pragma once

#include "Common/Defs.hpp"
#include "PCH/CStd.hpp"

namespace HyperCPU {
  HCPU_ALWAYS_INLINE static void PrintUnsupported(std::string_view /* msg */) {
    std::abort();
  }
} // namespace HyperCPU
