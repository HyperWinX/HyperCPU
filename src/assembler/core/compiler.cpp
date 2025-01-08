#include <print>
#include <string>
#include <fstream>

#include <pog/pog.h>

#include <core/compiler.hpp>
#include <logger/logger.hpp>
#include <variant>

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
  
  parser.token("#use")
    .fullword()
    .symbol("use");
  parser.token("ptr")
    .fullword()
    .symbol("ptr");
  
  parser.token("[a-zA-Z_][a-zA-Z0-9_]*")
    .symbol("ident")
    .action(tokenize_ident);
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
    .production("[", "ident", "]", parse_operand2)
    .production("[", "ident", "+", "uint", "]", parse_operand3)
    .production("[", "ident", "+", "hex", "]", parse_operand3)
    .production("[", "ident", "+", "binary", "]", parse_operand3)
    .production("ident", "ptr", "[", "hex", "]", parse_operand4)
    .production("ident", "ptr", "[", "ident", "]", parse_operand5)
    .production("ident", "ptr", "[", "ident", "+", "uint", "]", parse_operand6)
    .production("ident", "ptr", "[", "ident", "+", "hex", "]", parse_operand6)
    .production("ident", "ptr", "[", "ident", "+", "binary", "]", parse_operand6)
    .production("hex", parse_operand8)
    .production("binary", parse_operand8)
    .production("sint", parse_operand7)
    .production("uint", parse_operand8)
    .production("ident", parse_operand9);

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
  auto binary = transform_to_binary(ir);


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

constexpr inline std::uint8_t hcasm::hcasm_compiler::operand_size(hcasm::operand op) {
  switch (op.type) {
    case hcasm::operand_type::mem_reg_add_int:
    case hcasm::operand_type::memaddr_reg:
    case hcasm::operand_type::reg:
      return 1;
    case hcasm::operand_type::memaddr_int:
      return 8;
    case hcasm::operand_type::sint:
    case hcasm::operand_type::uint:
      switch (op.mode) {
        case hcasm::mode::b8:   return 1;
        case hcasm::mode::b16:  return 2;
        case hcasm::mode::b32:  return 4;
        case hcasm::mode::b64:  return 8;
        default: __builtin_unreachable();
      }
    default: __builtin_unreachable();
  }
}

std::uint8_t hcasm::hcasm_compiler::instruction_size(hcasm::instruction& instr) {
  std::uint8_t result = 3; // Opcode is always two bytes long + one byte for operand types

  if (instr.op1.type != hcasm::operand_type::none && instr.op2.type != hcasm::operand_type::none) {
    if (instr.op1.type == hcasm::operand_type::mem_reg_add_int || instr.op2.type == hcasm::operand_type::mem_reg_add_int) {
      ++result; // Prefix byte
    }
    result += operand_size(instr.op1);
    result += operand_size(instr.op2);
  } else if (instr.op1.type != hcasm::operand_type::none && instr.op2.type == hcasm::operand_type::none) {
    result += operand_size(instr.op1);
  } else if (instr.op1.type == hcasm::operand_type::none && instr.op2.type != hcasm::operand_type::none) {
    result += operand_size(instr.op2);
  }

  return result;
}

hcasm::binary_result hcasm::hcasm_compiler::transform_to_binary(hcasm::compiler_state& ir) {
  // Count code size - pass 1
  logger.log(loglevel::DEBUG, "Running pass 1 - counting code size");
  
  for (auto& instr : ir.ir) {
    if (std::holds_alternative<instruction>(instr)) {
      ir.code_size += instruction_size(std::get<instruction>(instr));
    } else if (std::holds_alternative<label>(instr)) {
      auto& lbl = std::get<label>(instr);
      current_state->labels[lbl.name] = ir.code_size;
    }
  }

  // Compile code - pass 2
  binary_result binary = { new unsigned char[ir.code_size] };
  if (!binary.binary) {
    logger.log(loglevel::ERROR, "Failed to allocate memory for binary data!");
    std::abort();
  }

  for (auto& instr : ir.ir) {
    if (std::holds_alternative<instruction>(instr)) {
      auto& ins = std::get<instruction>(instr);

      
    }
  }

  return binary;
}