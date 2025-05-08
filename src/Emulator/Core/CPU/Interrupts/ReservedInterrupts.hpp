#pragma once

#include "PCH/CStd.hpp"

namespace HyperCPU {
  enum class cpu_exceptions : std::uint_fast8_t {
    IA,
    IO,
    ZRDIV,
    SEGF
  };
}
