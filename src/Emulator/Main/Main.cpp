#include <filesystem>
#include <print>

#include <Assembler/Core/Compiler.hpp>
#include <Logger/Logger.hpp>
#include <Logger/Colors.hpp>
#include <Assembler/Utils/Extension.hpp>
#include <Emulator/Main/Main.hpp>
#include <Emulator/Core/CPU/CPU.hpp>
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
  program.add_argument("-m", "--memory")
    .default_value(std::string{"8K"})
    .help("max memory to use");

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
  } else if (!std::filesystem::is_regular_file(source)) {
    HCAsm::logger.Log(HyperCPU::LogLevel::ERROR, std::format("Source path \"{}\" is not a regular file!", source));
    std::exit(1);
  }

  std::ifstream file(source);
  
  std::int64_t binarysize = std::filesystem::file_size(source) - sizeof(HyperCPU::GenericHeader);

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
      HCAsm::logger.Log(HyperCPU::LogLevel::ERROR, "Executing object files is not supported, please link it first!");
      std::exit(1);
    default:
      HCAsm::logger.Log(HyperCPU::LogLevel::ERROR, "Invalid type field!");
      std::exit(1);
  }

  std::unique_ptr<char[]> buf(new char[binarysize]);
  file.read(buf.get(), binarysize);

  auto memory = HyperCPU::ParseMemoryString(program.get<std::string>("-m"));
  if (!memory.has_value()) {
    HCAsm::logger.Log(HyperCPU::LogLevel::ERROR, "Failed to parse memory amount argument.");
    std::exit(1);
  }

  HyperCPU::CPU cpu{1, *memory, buf.get(), static_cast<std::uint64_t>(binarysize )};

  cpu.SetEntryPoint(header.entry_point);
  cpu.Run();
}

HyperCPU::GenericHeader ParseHeader(std::ifstream& file) {
  HyperCPU::GenericHeader header;
  file.read(reinterpret_cast<char*>(&header), sizeof(header));

  return header;
}

std::expected<std::uint64_t, HyperCPU::ParseError> HyperCPU::ParseMemoryString(const std::string& str) {
  if (str.empty()) {
    return std::unexpected(ParseError::Empty);
  }

  std::size_t idx = 0;
  // Validate digits
  for (char c : str) {
    if (!std::isdigit(c)) {
      break;
    }
    ++idx;
  }

  if (idx == 0) {
    return std::unexpected(ParseError::Invalid);
  }

  std::string_view numeric_part = std::string_view(str).substr(0, idx);

  char suffix = str[idx];
  ++idx;

  if (idx != str.size()) {
    return std::unexpected(ParseError::Invalid);
  }

  std::uint64_t multiplier;
  switch (suffix) {
    case 'K':
      multiplier = 1024ULL;
      break;
    case 'M':
      multiplier = 1024ULL * 1024;
      break;
    case 'G':
      multiplier = 1024ULL * 1024 * 1024;
      break;
    case 'T':
      multiplier = 1024ULL * 1024 * 1024 * 1024;
      break;
    default:
      return std::unexpected(ParseError::Invalid);
  }

  std::uint64_t result;
  auto [ptr, ec] = std::from_chars(numeric_part.data(), numeric_part.end(), result);
  if (ec != std::errc() || ptr != numeric_part.end()) {
    return std::unexpected(ParseError::Invalid);
  }

  if (multiplier != 0 && result > std::numeric_limits<std::uint64_t>::max() / multiplier) {
    return std::unexpected(ParseError::Invalid);
  }

  return result * multiplier;
}