#include <Core/Compiler.hpp>
#include <Core/OpcodeNameAssoc.hpp>
#include <Core/RegNameAssoc.hpp>

using HCAsm::Value;
using HyperCPU::LogLevel;

Value HCAsm::CompileStatement1(std::vector<Value>&& args) {
    auto& instr_name = std::get<std::string>(args[0].val);

    if (!opcode_assoc.contains(instr_name.c_str())) {
        logger.Log(LogLevel::ERROR, "Invalid instruction name: {}", instr_name);
        std::abort();
    }

    ++current_index;

    current_state->ir.push_back(Instruction {
        opcode_assoc.at(instr_name.c_str()),
        std::get<Operand>(args[1].val),
        std::get<Operand>(args[3].val)
    });
    return {};
}

Value HCAsm::CompileStatement2(std::vector<Value>&& args) {
    auto& instr_name = std::get<std::string>(args[0].val);

    if (!opcode_assoc.contains(instr_name.c_str())) {
        logger.Log(LogLevel::ERROR, "Invalid instruction name: {}", instr_name);
        std::abort();
    }

    ++current_index;

    current_state->ir.push_back(Instruction {
        opcode_assoc.at(instr_name.c_str()),
        std::get<Operand>(args[1].val),
        { HCAsm::OperandType::none }
    });
    return {};
}

Value HCAsm::CompileStatement3(std::vector<Value>&& args) {
    auto& instr_name = std::get<std::string>(args[0].val);

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

Value HCAsm::CompileLabel(std::vector<Value>&& args) {
    // Label cant be register or instruction name
    auto& name = std::get<std::string>(args[0].val);

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
    return { std::get<std::string>(args[0].val) }; // Technically, placeholder
}