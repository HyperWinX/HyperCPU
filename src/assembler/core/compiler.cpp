#include <print>
#include <string>
#include <fstream>

#include <pog/pog.h>

#include <core/compiler.hpp>
#include <logger/logger.hpp>


using hypercpu::loglevel;

hcasm::hcasm_compiler::hcasm_compiler(loglevel lvl) : logger(lvl) {
  // Setup tokens
  parser.token("\\s+")
    .symbol("string");
  parser.token("+")
    .symbol("+");
  parser.token("-")
    .symbol("-");
  parser.token(",")
    .symbol(",");
  parser.token("[")
    .symbol("[");
  parser.token("]")
    .symbol("]");
  parser.token("[a-zA-Z_][a-zA-Z0-9_]*")
    .symbol("ident");
  parser.token("#use")
    .symbol("use");
  parser.token(R"("[^"]*")")
    .symbol("string")
    .action(tokenize_str);
  parser.token("s[0-9]+")
    .symbol("sint")
    .action(tokenize_sint);
  parser.token("u[0-9]+")
    .symbol("uint")
    .action(tokenize_uint);
  parser.token("^(h)[0-9a-fA-F]+$")
    .symbol("hex")
    .action(tokenize_hex);
  parser.token("^(b)[01]+$")
    .symbol("binary")
    .action(tokenize_binary);
  logger.log(hypercpu::loglevel::DEBUG, "Tokens configured");

  // Setup parser rules
  parser.set_start_symbol("statement");
  parser.rule("statement")
    .production("ident", "operand", ",", "operand", [](auto&& args) -> value {
      return {};
    });

  parser.rule("operand")
    .production("[", "hex", "]", parse_operand1)
    .production("[", "ident", "+", "uint", "]", parse_operand2)
    .production("[", "ident", "-", "uint", "]", parse_operand3)
    .production("[", "ident", "+", "hex", "]", parse_operand2)
    .production("[", "ident", "-", "hex", "]", parse_operand3)
    .production("[", "ident", "+", "binary", "]", parse_operand2)
    .production("[", "ident", "-", "binary", "]", parse_operand3)
    .production("hex", parse_operand5)
    .production("binary", parse_operand5)
    .production("sint", parse_operand4)
    .production("uint", parse_operand5)
    .production("ident", parse_operand6);

}

void hcasm::hcasm_compiler::compile(std::string& source, std::string& destination) {
  // Verify that files are available
  std::ifstream src(source);
  std::ofstream dst(destination);
  if (!src.is_open() || !dst.is_open()) {
    logger.log(loglevel::ERROR, "Failed to open source file!");
    std::exit(1);
  }
  logger.log(hypercpu::loglevel::DEBUG, "Source and destination files handles acquired");
  
}