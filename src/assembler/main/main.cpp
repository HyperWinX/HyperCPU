#include "logger/logger.hpp"
#include <filesystem>
#include <print>

#include <argparse/argparse.hpp>

#include <core/compiler.hpp>
#include <logger/colors.hpp>
#include <utils/extension.hpp>


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

  std::string result_object_file = hcasm::create_object_file_name(source);
  if (result_object_file == source) {
    result_object_file += ".o";
  }
  hcasm::hcasm_compiler compiler{hypercpu::loglevel::DEBUG};
  compiler.compile(source, result_object_file);
}

std::string hcasm::create_object_file_name(std::string str) {
  std::size_t lastDotPos = str.rfind('.');
  if (lastDotPos != std::string::npos) {
    str.replace(lastDotPos + 1, str.length() - lastDotPos - 1, "o");
  }
  return str;
}