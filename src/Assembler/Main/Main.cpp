#include <filesystem>
#include <print>

#include <Assembler/Core/Compiler.hpp>
#include <Logger/Logger.hpp>
#include <Logger/Colors.hpp>
#include <Assembler/Utils/Extension.hpp>

#include <argparse/argparse.hpp>

#include <mapbox/eternal.hpp>


constexpr const inline auto loglevel_assoc = mapbox::eternal::map<mapbox::eternal::string, HyperCPU::LogLevel>({
  {"debug", HyperCPU::LogLevel::DEBUG},
  {"info", HyperCPU::LogLevel::INFO},
  {"warning", HyperCPU::LogLevel::WARNING},
  {"error", HyperCPU::LogLevel::ERROR},
});

int main(int argc, char** argv) {
  argparse::ArgumentParser program("hcasm", "0.0.0");
  program.add_argument("source")
    .help("source file to be assembled")
    .required();
  program.add_argument("-o")
    .help("name of the binary file");
  program.add_argument("-v")
    .default_value(std::string{"warning"})
    .help("set verbosity level. possible modes:\n- debug\n- info\n- warning\n- error");

  try {
    program.parse_args(argc, argv);
  } catch (const std::exception& err) {
    std::cerr << err.what() << '\n';
    std::exit(1);
  }

  auto source = program.get<std::string>("source");
  std::string result;
  if (program.present("-o")) {
    result = program.get<std::string>("-o");
  } else {
    result = HCAsm::CreateObjectFilename(source);
    if (result == source) {
      result += ".o";
    }
  }

  HCAsm::HCAsmCompiler compiler{ loglevel_assoc.at(program.get<std::string>("-v").c_str()) };

  compiler.Compile(source, result);
}

std::string HCAsm::CreateObjectFilename(std::string str) {
  std::size_t lastDotPos = str.rfind('.');
  if (lastDotPos != std::string::npos) {
    str.replace(lastDotPos + 1, str.length() - lastDotPos - 1, "o");
  }
  return str;
}