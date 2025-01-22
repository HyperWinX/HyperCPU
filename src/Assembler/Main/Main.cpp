#include <filesystem>
#include <print>

#include <Core/Compiler.hpp>
#include <Logger/Logger.hpp>
#include <Logger/Colors.hpp>
#include <Utils/Extension.hpp>

#include <argparse/argparse.hpp>


int main(int argc, char** argv) {
  argparse::ArgumentParser program("hcemul", "0.0.0");
  program.add_argument("-f")
    .help("binary file to execute")
    .required();
  program.add_argument("-v")
    .help("set verbosity level. possible modes:\n- debug\n- info\n- warning\n- error");

  try {
    program.parse_args(argc, argv);
  } catch (const std::exception& err) {
    std::cerr << err.what() << '\n';
    std::exit(1);
  }

  auto source = program.get<std::string>("-f");
  if (!std::filesystem::exists(source)) {
    std::println(stderr, "{}[!] {}File \"{}\" does not exist!{}", B_RED, RED, source, RESET);
    std::exit(1);
  }

  std::string result_object_file = HCAsm::CreateObjectFilename(source);
  if (result_object_file == source) {
    result_object_file += ".o";
  }
  HCAsm::HCAsmCompiler compiler{HyperCPU::LogLevel::DEBUG};
  compiler.Compile(source, result_object_file);
}

std::string HCAsm::CreateObjectFilename(std::string str) {
  std::size_t lastDotPos = str.rfind('.');
  if (lastDotPos != std::string::npos) {
    str.replace(lastDotPos + 1, str.length() - lastDotPos - 1, "o");
  }
  return str;
}