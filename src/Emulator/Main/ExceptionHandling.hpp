#pragma once

#include <string>


namespace HyperCPU {
  class CPU;

  [[noreturn]] void ThrowError(CPU* cpu, std::string message);
}