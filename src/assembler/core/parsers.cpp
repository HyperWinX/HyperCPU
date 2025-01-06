#include <core/compiler.hpp>
#include <core/reg_name_assoc.hpp>

using hcasm::value;

value hcasm::parse_operand1(std::vector<value>&& args) {
  return {
    .val = operand {
      .type = hcasm::operand_type::memaddr,
      .uint1 = std::get<std::uint64_t>(args[1].val)
    }
  };
}

value hcasm::parse_operand2(std::vector<value>&& args) {
  return {
    .val = operand {
      .type = hcasm::operand_type::mem_reg_add_int,
      .reg = registers_assoc.at(std::get<std::string>(args[1].val).c_str()),
      .uint1 = std::get<std::uint64_t>(args[3].val)
    }
  };
}

value hcasm::parse_operand3(std::vector<value>&& args) {
  return {
    .val = operand {
      .type = hcasm::operand_type::mem_reg_sub_int,
      .reg = registers_assoc.at(std::get<std::string>(args[1].val).c_str()),
      .uint1 = std::get<std::uint64_t>(args[3].val)
    }
  };
}

value hcasm::parse_operand4(std::vector<value>&& args) {
  return {
    .val = operand {
      .type = hcasm::operand_type::sint,
      .sint2 = std::get<std::int64_t>(args[0].val)
    }
  };
}

value hcasm::parse_operand5(std::vector<value>&& args) {
  return {
    .val = operand {
      .type = hcasm::operand_type::uint,
      .uint1 = std::get<std::uint64_t>(args[0].val)
    }
  };
}

value hcasm::parse_operand6(std::vector<value>&& args) {
  return {
    .val = operand {
      .type = hcasm::operand_type::reg,
      .reg = registers_assoc.at(std::get<std::string>(args[0].val).c_str())
    }
  };
}