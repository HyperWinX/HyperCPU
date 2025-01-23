#include "pog/parser.h"
#include <Core/Compiler.hpp>
#include <Core/OpcodeNameAssoc.hpp>
#include <Core/RegNameAssoc.hpp>

using HCAsm::Value;
using HyperCPU::LogLevel;

Value HCAsm::CompileStatement1(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
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

Value HCAsm::CompileStatement2(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
    auto& instr_name = std::get<std::string>(args[0].value.val);

    if (!opcode_assoc.contains(instr_name.c_str())) {
        logger.Log(LogLevel::ERROR, "Invalid instruction name: {}", instr_name);
        std::abort();
    }

    ++current_index;

    current_state->ir.push_back(Instruction {
        opcode_assoc.at(instr_name.c_str()),
        std::get<Operand>(args[1].value.val),
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

    current_state->ir.push_back(HCAsm::Label{ name, current_index++ });
    current_state->labels[name] = current_index - 1;
    return { std::get<std::string>(args[0].value.val) }; // Technically, placeholder
}