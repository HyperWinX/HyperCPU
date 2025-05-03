#pragma once

#include "pch.hpp"


namespace HyperCPU {
  class CPU;

  [[noreturn]] void ThrowError(CPU* cpu, std::string message);
}
