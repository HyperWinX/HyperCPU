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
    .symbol("\\n")
    .action([](std::string_view tok) -> Value {
      std::cerr << "FUCKIN' YESS!\n";
      std::abort();
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
    .production("hex", ParseOperand8)
    .production("binary", ParseOperand8)
    .production("sint", ParseOperand7)
    .production("uint", ParseOperand8)
    .production("ident", ParseOperand9);

}

void HCAsm::HCAsmCompiler::Compile(std::string& source, std::string& destination) {
  // Verify that files are available
  std::ifstream src(source);
  std::ofstream dst(destination);
  if (!src.is_open() || !dst.is_open()) {
    logger.Log(LogLevel::ERROR, "Failed to open source file!");
    std::exit(1);
  }
  logger.Log(LogLevel::DEBUG, "Source and destination files handles acquired");
  std::string contents;
  src >> contents;

  logger.Log(LogLevel::DEBUG, "Stage 1 compiling - transforming to IR");
  CompilerState ir = TransformToIR(contents);

  logger.Log(LogLevel::DEBUG, "Stage 2 compiling - transforming to binary");
  auto binary = TransformToBinary(ir);


}

HCAsm::CompilerState HCAsm::HCAsmCompiler::TransformToIR(std::string& src) {
  CompilerState state;
  current_state = &state;
  this->state = &state;

  auto report = parser.prepare();
  std::puts(report.to_string().c_str());
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
      return 8;
    case HCAsm::OperandType::sint:
    case HCAsm::OperandType::uint:
      // Return 8, because it is the max size of that type of operand. We don't know exact size of operand at this stage.
      return 8;
    default: std::abort();
    //default: std::unreachable();
  }
}

std::uint8_t HCAsm::HCAsmCompiler::InstructionSize(HCAsm::Instruction& instr) {
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
      current_state->labels[lbl.name] = ir.code_size;
    }
  }

  // Compile code - pass 2
  BinaryResult binary = { new unsigned char[ir.code_size] };
  if (!binary.binary) {
    logger.Log(LogLevel::ERROR, "Failed to allocate memory for binary data!");
    std::abort();
  }

  BinaryTransformer transformer(binary);

  for (auto& instr : ir.ir) {
    if (std::holds_alternative<Instruction>(instr)) {
      auto& ins = std::get<Instruction>(instr);

      transformer.EncodeInstruction(ins);
    }
  }

  return binary;
}