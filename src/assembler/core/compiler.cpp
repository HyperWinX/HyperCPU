#include <print>
#include <string>
#include <fstream>

#include <pog/pog.h>

#include <core/compiler.hpp>
#include <logger/logger.hpp>

using hypercpu::loglevel;

namespace hcasm {
  hypercpu::logger logger{hypercpu::loglevel::WARNING};
  hcasm::compiler_state* current_state;
  std::uint64_t current_index = 0;
}

hcasm::hcasm_compiler::hcasm_compiler(loglevel lvl) {
  logger = hypercpu::logger{lvl};
  // Setup tokens
  parser.token("\\s+");
  parser.token(R"(\+)")
    .symbol("+");
  parser.token(R"(-)")
    .symbol("-");
  parser.token(",")
    .symbol(",");
  parser.token("\\[")
    .symbol("[");
  parser.token("\\]")
    .symbol("]");
  parser.token(";")
    .symbol(";");
  parser.token(":")
    .symbol(":");
  parser.token("<")
    .symbol("<");
  parser.token(">")
    .symbol(">");
  parser.token("[a-zA-Z_][a-zA-Z0-9_]*")
    .symbol("ident")
    .action(tokenize_ident);
  parser.token("#use")
    .symbol("use");
  parser.token(R"("[^"]*")")
    .symbol("string")
    .action(tokenize_str);
  parser.token("[0-9]+s")
    .symbol("sint")
    .action(tokenize_sint);
  parser.token("[0-9]+u")
    .symbol("uint")
    .action(tokenize_uint);
  parser.token(R"([0-9a-fA-F]+h)")
    .symbol("hex")
    .action(tokenize_hex);
  parser.token(R"([01]+b)")
    .symbol("binary")
    .action(tokenize_binary);
  logger.log(hypercpu::loglevel::DEBUG, "Tokens configured");

  // Setup parser rules
  parser.set_start_symbol("statements");
  parser.rule("statements")
    .production("statements", "statement")
    .production("statement");
  parser.rule("statement")
    .production("ident", "operand", ",", "operand", ";", compile_stmt1)
    .production("ident", "operand", ";", compile_stmt2)
    .production("ident", ";", compile_stmt3)
    .production("ident", ":", compile_label);

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
  logger.log(loglevel::DEBUG, "Source and destination files handles acquired");
  std::string contents;
  src >> contents;

  logger.log(loglevel::DEBUG, "Stage 1 compiling - transforming to IR");
  compiler_state ir = transform_to_IR(contents);

  logger.log(loglevel::DEBUG, "Stage 2 compiling - transforming to binary");
  transform_to_binary(ir, dst);
}

hcasm::compiler_state hcasm::hcasm_compiler::transform_to_IR(std::string& src) {
  compiler_state state;
  current_state = &state;
  this->state = &state;

  parser.prepare();
  logger.log(loglevel::DEBUG, "Parser prepared.");
  logger.log(loglevel::DEBUG, "Compiling...");
  
  parser.parse(src);
  current_state = 0;
  return state;
}

void hcasm::hcasm_compiler::transform_to_binary(hcasm::compiler_state& ir, std::ofstream& dst) {

}