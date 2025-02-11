#include "pog/line_spec.h"
#include <ios>
#include <iterator>
#include <print>
#include <string>
#include <fstream>
#include <iostream>
#include <variant>

#include <Core/BinaryTransformer.hpp>
#include <Core/Compiler.hpp>
#include <Logger/Logger.hpp>

#include <pog/pog.h>


using HyperCPU::LogLevel;

namespace HCAsm {
  HyperCPU::Logger logger{HyperCPU::LogLevel::WARNING};
  HCAsm::CompilerState* current_state;
  std::uint64_t current_index = 0;
}

HCAsm::HCAsmCompiler::HCAsmCompiler(LogLevel lvl) {
  logger = HyperCPU::Logger{lvl};
  // Setup tokens
  parser.token("[^\\S\n]+");
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
  parser.token(R"(\n)")
    .action([this](std::string_view tok) -> Value {
      ++parser.get_line_counter();
      parser.reset_line_offset();
      return {};
    });
  
  parser.token("#use")
    .fullword()
    .symbol("use");
  
  parser.token("[a-zA-Z_][a-zA-Z0-9_]*")
    .symbol("ident")
    .action(TokenizeIdentifier);
  parser.token(R"("[^"]*")")
    .symbol("string")
    .action(TokenizeString);
  parser.token("[0-9]+s")
    .symbol("sint")
    .action(TokenizeSignedInt);
  parser.token("[0-9]+u")
    .symbol("uint")
    .action(TokenizeUnsignedInt);
  parser.token(R"([0-9a-fA-F]+h)")
    .symbol("hex")
    .action(TokenizeHexadecimal);
  parser.token(R"([01]+b)")
    .symbol("binary")
    .action(TokenizeBinary);
  parser.token(R"('.')")
    .symbol("char")
    .action(TokenizeChar);
  parser.end_token().action([this](std::string_view) -> Value {
    parser.pop_input_stream();
    return {};
  });
  logger.Log(HyperCPU::LogLevel::DEBUG, "Tokens configured");

  // Setup parser rules
  parser.set_start_symbol("statements");
  parser.rule("statements")
    .production("statements", "statement")
    .production("statement");
  parser.rule("statement")
    .production("ident", "operand", ",", "operand", ";", CompileStatement1)
    .production("ident", "operand", ";", CompileStatement2)
    .production("ident", ";", CompileStatement3)
    .production("ident", ":", CompileLabel);

  parser.rule("operand")
    .production("[", "hex", "]", ParseOperand1)
    .production("[", "ident", "]", ParseOperand2)
    .production("[", "ident", "+", "uint", "]", ParseOperand3)
    .production("[", "ident", "+", "hex", "]", ParseOperand3)
    .production("[", "ident", "+", "binary", "]", ParseOperand3)
    .production("ident", "ident", "[", "hex", "]", ParseOperand4)
    .production("ident", "ident", "[", "ident", "]", ParseOperand5)
    .production("ident", "ident", "[", "ident", "+", "uint", "]", ParseOperand6)
    .production("ident", "ident", "[", "ident", "+", "hex", "]", ParseOperand6)
    .production("ident", "ident", "[", "ident", "+", "binary", "]", ParseOperand6)
    .production("ident", "hex", ParseOperand10)
    .production("ident", "binary", ParseOperand10)
    .production("ident", "uint", ParseOperand10)
    .production("ident", "char", ParseOperand10)
    .production("ident", "sint", ParseOperand11)
    .production("hex", ParseOperand8)
    .production("binary", ParseOperand8)
    .production("sint", ParseOperand7)
    .production("uint", ParseOperand8)
    .production("char", ParseOperand8)
    .production("ident", ParseOperand9);

}

HCAsm::BinaryResult HCAsm::HCAsmCompiler::Compile(std::string& contents, std::uint32_t& code_size) { 
  files.push(std::move(contents));

  logger.Log(LogLevel::DEBUG, "Stage 1 compiling - transforming to IR");
  CompilerState ir = TransformToIR(files.back());

  logger.Log(LogLevel::DEBUG, "Stage 2 compiling - transforming to binary");
  auto binary = TransformToBinary(ir);
  code_size = ir.code_size;

  return binary;
}

HCAsm::CompilerState HCAsm::HCAsmCompiler::TransformToIR(std::string& src) {
  CompilerState state;
  current_state = &state;
  this->state = &state;
  parser.set_compiler_state(&state);

  parser.prepare();
  logger.Log(LogLevel::DEBUG, "Parser prepared.");
  logger.Log(LogLevel::DEBUG, "Compiling...");
  
  parser.parse(src);
  current_state = nullptr;
  return state;
}

constexpr inline std::uint8_t HCAsm::HCAsmCompiler::OperandSize(HCAsm::Operand op) {
  switch (op.type) {
    case HCAsm::OperandType::mem_reg_add_int:
    case HCAsm::OperandType::memaddr_reg:
    case HCAsm::OperandType::reg:
      return 1;
    case HCAsm::OperandType::memaddr_int:
    case HCAsm::OperandType::sint:
    case HCAsm::OperandType::uint:
    case HCAsm::OperandType::label:
      return 8;
    default: std::abort();
    //default: std::unreachable();
  }
}

std::uint8_t HCAsm::HCAsmCompiler::InstructionSize(const HCAsm::Instruction& instr) {
  std::uint8_t result = 3; // Opcode is always two bytes long + one byte for operand types

  if (instr.op1.type != HCAsm::OperandType::none && instr.op2.type != HCAsm::OperandType::none) {
    if (instr.op1.type == HCAsm::OperandType::mem_reg_add_int || instr.op2.type == HCAsm::OperandType::mem_reg_add_int) {
      ++result; // Prefix byte
    }
    result += OperandSize(instr.op1);
    result += OperandSize(instr.op2);
  } else if (instr.op1.type != HCAsm::OperandType::none && instr.op2.type == HCAsm::OperandType::none) {
    result += OperandSize(instr.op1);
  } else if (instr.op1.type == HCAsm::OperandType::none && instr.op2.type != HCAsm::OperandType::none) {
    result += OperandSize(instr.op2);
  }

  return result;
}

HCAsm::BinaryResult HCAsm::HCAsmCompiler::TransformToBinary(HCAsm::CompilerState& ir) {
  // Count code size - pass 1
  logger.Log(LogLevel::DEBUG, "Running pass 1 - counting code size");
  
  for (auto& instr : ir.ir) {
    if (std::holds_alternative<Instruction>(instr)) {
      ir.code_size += InstructionSize(std::get<Instruction>(instr));
    } else if (std::holds_alternative<Label>(instr)) {
      auto& lbl = std::get<Label>(instr);
      
      ir.labels[lbl.name] = ir.code_size;
    }
  }

  // Resolve references - pass 2

  logger.Log(LogLevel::DEBUG, std::format("{} label references are waiting for resolve", ir.pending_resolves.size()));
  if (!ir.pending_resolves.empty()) {
    logger.Log(LogLevel::DEBUG, "Resolving label references");

    for (auto& args : ir.pending_resolves) {
      auto& operand = args.op;

      if (ir.labels.contains(*operand.str)) {
        args.op.type = OperandType::uint;
        args.op.uint1 = ir.labels[*operand.str];
      } else {
        ThrowError(args.args[0], parser, std::format("failed to resolve undefined reference to \"{}\"", *operand.str));
      }
    }
  }

  // Compile code - pass 3
  BinaryResult binary = { new unsigned char[ir.code_size] };
  if (!binary.binary) {
    logger.Log(LogLevel::ERROR, "Failed to allocate memory for binary data!");
    std::abort();
  }

  logger.Log(LogLevel::DEBUG, "Running pass 2 - compiling");

  BinaryTransformer transformer(binary, &ir);

  for (auto& instr : ir.ir) {
    if (std::holds_alternative<Instruction>(instr)) {
      auto& ins = std::get<Instruction>(instr);

      transformer.EncodeInstruction(ins);
    }
  }

  return binary;
}

std::string_view HCAsm::FindLine(const pog::LineSpecialization& line_spec, const std::string_view& str) {
  std::size_t start = 0;
  std::size_t end = 0;
  std::size_t current_line = 1;

  while (end < str.size()) {
    if (str[end] == '\n') {
      if (current_line == line_spec.line) {
        return std::string_view { str.begin() + start, end - start };
      }
      start = end + 1;
      current_line++;
    }
    end++;
  }

  if (current_line == line_spec.line) {
    return std::string_view { str.begin() + start, str.end() };
  }

  throw std::out_of_range("Line number out of range");
}

[[noreturn]] void HCAsm::ThrowError(pog::TokenWithLineSpec<Value>& err_token, pog::Parser<Value>& parser, std::string err_msg) {
  logger.Log(HyperCPU::LogLevel::ERROR, "error: {}", err_msg);
  auto line = FindLine(err_token.line_spec, parser.get_top_file());
  std::println("{} | {}", err_token.line_spec.line, line);
  std::println("{:<{}} | {:<{}}{}",
    "", std::to_string(err_token.line_spec.line).length(),
    "", err_token.line_spec.offset,
    std::string(err_token.line_spec.length, '^'));
  std::exit(1);
}

void HCAsm::WriteResultFile(HyperCPU::FileType type, HCAsm::BinaryResult& result, std::ofstream& output, std::uint32_t code_size) {
  HyperCPU::GenericHeader gen_header;
  gen_header.type = type;
  gen_header.magic = HyperCPU::magic;
  gen_header.version = HyperCPU::current_version;
  gen_header.code_size = code_size;
  output.write(reinterpret_cast<char*>(&gen_header), sizeof(gen_header));

  output.write(reinterpret_cast<char*>(result.binary), code_size);
}
