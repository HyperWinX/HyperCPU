#include <core/compiler.hpp>

#include <core/opcode_name_assoc.hpp>
#include <core/reg_name_assoc.hpp>

using hcasm::value;
using hypercpu::loglevel;

value hcasm::compile_stmt1(std::vector<value>&& args) {
    auto& instr_name = std::get<std::string>(args[0].val);

    if (!opcode_assoc.contains(instr_name.c_str())) {
        logger.log(loglevel::ERROR, "Invalid instruction name: {}", instr_name);
        std::abort();
    }

    ++current_index;

    current_state->ir.push_back(instruction {
        opcode_assoc.at(instr_name.c_str()),
        std::get<operand>(args[1].val),
        std::get<operand>(args[3].val)
    });
    return {};
}

value hcasm::compile_stmt2(std::vector<value>&& args) {
    auto& instr_name = std::get<std::string>(args[0].val);

    if (!opcode_assoc.contains(instr_name.c_str())) {
        logger.log(loglevel::ERROR, "Invalid instruction name: {}", instr_name);
        std::abort();
    }

    ++current_index;

    current_state->ir.push_back(instruction {
        opcode_assoc.at(instr_name.c_str()),
        std::get<operand>(args[1].val),
        { hcasm::operand_type::none }
    });
    return {};
}

value hcasm::compile_stmt3(std::vector<value>&& args) {
    auto& instr_name = std::get<std::string>(args[0].val);

    if (!opcode_assoc.contains(instr_name.c_str())) {
        logger.log(loglevel::ERROR, "Invalid instruction name: {}", instr_name);
        std::abort();
    }

    ++current_index;

    current_state->ir.push_back(instruction{
        opcode_assoc.at(instr_name.c_str()),
        { hcasm::operand_type::none },
        { hcasm::operand_type::none }
    });
    return {};
}

value hcasm::compile_label(std::vector<value>&& args) {
    // Label cant be register or instruction name
    auto& name = std::get<std::string>(args[0].val);

    if (opcode_assoc.contains(name.c_str()) || registers_assoc.contains(name.c_str())) {
        logger.log(loglevel::ERROR, "Label name uses reserved identifier: {}", name);
        std::abort();
    }

    if (current_state->labels.contains(name)) {
        logger.log(loglevel::ERROR, "Redefitinion of label \"{}\"", name);
        std::abort();
    }

    current_state->ir.push_back(hcasm::label{ name, current_index++ });
    return { std::get<std::string>(args[0].val) }; // Technically, placeholder
}