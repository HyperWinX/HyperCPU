#pragma once

#include <cstdint>


namespace hypercpu {
  enum class cpu_exceptions : std::int_fast8_t {
    IA,
    IO,
    ZRDIV
  };
}