#include "Emulator/Main/Main.hpp"
#include <filesystem>
#include <print>

#include <Assembler/Core/Compiler.hpp>
#include <Logger/Logger.hpp>
#include <Logger/Colors.hpp>
#include <Assembler/Utils/Extension.hpp>
#include <Main/Main.hpp>
#include <Version.hpp>

#include <argparse/argparse.hpp>

HyperCPU::GenericHeader ParseHeader(std::ifstream& binary);

int main(int argc, char** argv) {
  argparse::ArgumentParser program("hcemul", HCPU_VERSION);
  program.add_argument("binary")
    .help("binary file to execute")
    .required();
  program.add_argument("-v")
    .default_value(std::string{"debug"})
    .help("set verbosity level. possible modes:\n- debug\n- info\n- warning\n- error");

  try {
    program.parse_args(argc, argv);
  } catch (const std::exception& err) {
    std::cerr << err.what() << '\n';
    std::exit(1);
  }

  auto source = program.get<std::string>("binary");
  if (!std::filesystem::exists(source)) {
    HCAsm::logger.Log(HyperCPU::LogLevel::ERROR, std::format("Binary \"{}\" does not exist!", source));
    std::exit(1);
  }

  std::ifstream file(source);

  HyperCPU::GenericHeader header = ParseHeader(file);
  
  // Validate header contents
  if (header.magic != HyperCPU::magic) {
    HCAsm::logger.Log(HyperCPU::LogLevel::ERROR, "Invalid magic!");
    std::exit(1);
  }

  switch (header.version) {
    case HyperCPU::Version::PreRelease:
    case HyperCPU::Version::Release1_0:
      break;
    default:
      HCAsm::logger.Log(HyperCPU::LogLevel::ERROR, "Invalid release field!");
      std::exit(1);
  }

  switch (header.type) {
    case HyperCPU::FileType::Binary:
      break;
    case HyperCPU::FileType::Object:
      HCAsm::logger.Log(HyperCPU::LogLevel::ERROR, "Executing object files is not supported, please link it first.");
      std::exit(1);
    default:
      HCAsm::logger.Log(HyperCPU::LogLevel::ERROR, "Invalid type field!");
      std::exit(1);
  }

  std::println("okay");
}

HyperCPU::GenericHeader ParseHeader(std::ifstream& file) {
  HyperCPU::GenericHeader header;
  file.read(reinterpret_cast<char*>(&header), sizeof(header));

  return header;
}
