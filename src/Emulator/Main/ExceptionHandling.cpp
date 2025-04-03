#include "Logger/Logger.hpp"
#include <Main/ExceptionHandling.hpp>

#include <Core/CPU/CPU.hpp>
#include <Core/CPU/Util.hpp>

[[noreturn]] void HyperCPU::ThrowError(CPU* cpu, std::string message) {
  cpu->GetLogger().Log(HyperCPU::LogLevel::ERROR, message);
  EXIT(1);
}