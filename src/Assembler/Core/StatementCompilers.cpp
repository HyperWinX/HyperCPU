#include "pog/line_spec.h"
#include "pog/parser.h"
#include <Core/Compiler.hpp>
#include <Core/OpcodeNameAssoc.hpp>
#include <Core/RegNameAssoc.hpp>
#include <variant>
#include <iostream>

using HCAsm::Value;
using HyperCPU::LogLevel;

Value HCAsm::CompileStatement1([[maybe_unused]] pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
    auto& instr_name = std::get<std::string>(args[0].value.val);

    if (!opcode_assoc.contains(instr_name.c_str())) {
        logger.Log(LogLevel::ERROR, "Invalid instruction name: {}", instr_name);
        std::abort();
    }

    ++current_index;

    current_state->ir.push_back(Instruction {
        opcode_assoc.at(instr_name.c_str()),
        std::get<Operand>(args[1].value.val),
        std::get<Operand>(args[3].value.val)
    });

    return {};
}

Value HCAsm::CompileStatement2(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
    auto& instr_name = std::get<std::string>(args[0].value.val);

    if (!opcode_assoc.contains(instr_name.c_str())) {
        logger.Log(LogLevel::ERROR, "Invalid instruction name: {}", instr_name);
        std::abort();
    }

    ++current_index;

    auto& tmp_op = std::get<Operand>(args[1].value.val);
    auto* tmp_str = tmp_op.str;
    if (tmp_op.type == OperandType::label && parser.get_compiler_state()->labels.contains(*tmp_str)) {
      tmp_op.uint1 = parser.get_compiler_state()->labels[*tmp_str];
      tmp_op.mode = Mode::b64;
      tmp_op.type = OperandType::uint;
      delete tmp_str;
    }

    current_state->ir.push_back(Instruction {
        opcode_assoc.at(instr_name.c_str()),
        tmp_op,
        { HCAsm::OperandType::none }
    });

    return {};
}

Value HCAsm::CompileStatement3(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
    auto& instr_name = std::get<std::string>(args[0].value.val);

    if (!opcode_assoc.contains(instr_name.c_str())) {
        logger.Log(LogLevel::ERROR, "Invalid instruction name: {}", instr_name);
        std::abort();
    }

    ++current_index;

    current_state->ir.push_back(Instruction{
        opcode_assoc.at(instr_name.c_str()),
        { HCAsm::OperandType::none },
        { HCAsm::OperandType::none }
    });
    return {};
}

Value HCAsm::CompileLabel(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
    // Label cant be register or instruction name
    auto& name = std::get<std::string>(args[0].value.val);

    if (opcode_assoc.contains(name.c_str()) || registers_assoc.contains(name.c_str())) {
        logger.Log(LogLevel::ERROR, "Label name uses reserved identifier: {}", name);
        std::abort();
    }

    if (current_state->labels.contains(name)) {
        logger.Log(LogLevel::ERROR, "Redefitinion of label \"{}\"", name);
        std::abort();
    }

    current_state->ir.push_back(HCAsm::Label{ name, current_index++, false });
    current_state->labels[name] = current_index - 1;
    return {};
}

Value HCAsm::CompileEntryLabel(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  // Label cant be register or instruction name
  auto& name = std::get<std::string>(args[1].value.val);

  if (opcode_assoc.contains(name.c_str()) || registers_assoc.contains(name.c_str())) {
      logger.Log(LogLevel::ERROR, "Label name uses reserved identifier: {}", name);
      std::abort();
  }

  if (current_state->labels.contains(name)) {
      logger.Log(LogLevel::ERROR, "Redefitinion of label \"{}\"", name);
      std::abort();
  }

  current_state->ir.push_back(HCAsm::Label{ name, current_index++, true });
  current_state->labels[name] = current_index - 1;
  return {};
}

Value HCAsm::CompileRawValueb8(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  current_state->ir.push_back(HCAsm::RawValue{ Mode::b8, std::get<Operand>(args[1].value.val)});
  return {};
}

Value HCAsm::CompileRawValueb16(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  current_state->ir.push_back(HCAsm::RawValue{ Mode::b16, std::get<Operand>(args[1].value.val)});
  return {};
}

Value HCAsm::CompileRawValueb32(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  current_state->ir.push_back(HCAsm::RawValue{ Mode::b32, std::get<Operand>(args[1].value.val)});
  return {};
}

Value HCAsm::CompileRawValueb64(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  auto& op = std::get<Operand>(args[1].value.val);

  switch (op.type) {
    case HCAsm::OperandType::uint:
      current_state->ir.push_back(HCAsm::RawValue{ Mode::b64, op});
      break;
    case HCAsm::OperandType::label:
      current_state->ir.push_back(HCAsm::RawValue{ Mode::b64_label, op});
      break;
    default:
      ThrowError(args[1], parser, "invalid token, expected int literal or label");
  }
  return {};
}
