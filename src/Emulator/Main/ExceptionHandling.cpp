#include "pch.hpp"

#include <Main/ExceptionHandling.hpp>
#include <Logger/Logger.hpp>

#include <Core/CPU/Util.hpp>
#include <Core/CPU/CPU.hpp>


[[noreturn]] void HyperCPU::ThrowError(CPU* cpu, std::string message) {
  cpu->GetLogger().Log(HyperCPU::LogLevel::ERROR, message);
  EXIT(1);
}
