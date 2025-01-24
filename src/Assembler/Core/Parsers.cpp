#include <Core/ModeNameAssoc.hpp>
#include <Core/RegNameAssoc.hpp>
#include <Core/Compiler.hpp>

#include <pog/line_spec.h>
#include <string>

using HCAsm::Value;

Value HCAsm::ParseOperand1(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  return {
    .val = Operand {
      .type = HCAsm::OperandType::memaddr_int,
      .mode = HCAsm::Mode::none,
      .uint1 = std::get<std::uint64_t>(args[1].value.val)
    }
  };
}

Value HCAsm::ParseOperand2(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  auto& reg = std::get<std::string>(args[1].value.val);

  if (!registers_assoc.contains(reg.c_str())) [[unlikely]] {
    ThrowError(
      args[1], 
      parser, 
      std::format("expected register, got unknown identifier \"{}\"", std::get<std::string>(args[1].value.val)));
  }

  return {
    .val = Operand {
      .type = HCAsm::OperandType::memaddr_reg,
      .reg = registers_assoc.at(reg.c_str()),
      .mode = HCAsm::Mode::none,
    }
  };
}

Value HCAsm::ParseOperand3(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  auto& reg = std::get<std::string>(args[1].value.val);

  if (!registers_assoc.contains(reg.c_str())) [[unlikely]] {
    ThrowError(
      args[1], 
      parser, 
      std::format("expected register, got unknown identifier \"{}\"", std::get<std::string>(args[1].value.val)));
  } else if (std::get<std::uint64_t>(args[3].value.val) > 255) [[unlikely]] {
    ThrowError(
      args[3], 
      parser, 
      std::format("out of bounds integer provided: {} > 255", std::get<std::uint64_t>(args[3].value.val)));
  }

  return {
    .val = Operand {
      .type = HCAsm::OperandType::mem_reg_add_int,
      .reg = registers_assoc.at(reg.c_str()),
      .mode = HCAsm::Mode::none,
      .uint1 = std::get<std::uint64_t>(args[3].value.val)
    }
  };
}

Value HCAsm::ParseOperand4(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  auto& Mode = std::get<std::string>(args[0].value.val);

  if (!mode_assoc.contains(Mode.c_str())) [[unlikely]] {
    ThrowError(
      args[0], 
      parser, 
      std::format("unknown data size specified: \"{}\"", Mode));
  } else if (std::get<std::string>(args[1].value.val) != "ptr") {
    ThrowError(
      args[1], 
      parser, 
      std::format("unknown keyword \"{}\" specified, \"ptr\" expected", std::get<std::string>(args[1].value.val)));
  }

  return {
    .val = Operand {
      .type = HCAsm::OperandType::memaddr_int,
      .mode = mode_assoc.at(Mode.c_str()),
      .uint1 = std::get<std::uint64_t>(args[3].value.val)
    }
  };
}

Value HCAsm::ParseOperand5(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  auto& reg = std::get<std::string>(args[3].value.val);
  auto& Mode = std::get<std::string>(args[0].value.val);

  if (!registers_assoc.contains(reg.c_str())) {
    ThrowError(
      args[3], 
      parser, 
      std::format("expected register, got unknown identifier \"{}\"", std::get<std::string>(args[3].value.val)));
  } else if (!mode_assoc.contains(Mode.c_str())) {
    ThrowError(
      args[0], 
      parser, 
      std::format("unknown data size specified: \"{}\"", Mode));
  } else if (std::get<std::string>(args[1].value.val) != "ptr") {
    ThrowError(
      args[1], 
      parser, 
      std::format("unknown keyword \"{}\" specified, \"ptr\" expected", std::get<std::string>(args[1].value.val)));
  }

  return {
    .val = Operand {
      .type = HCAsm::OperandType::memaddr_reg,
      .reg = registers_assoc.at(reg.c_str()),
      .mode = mode_assoc.at(Mode.c_str()),
    }
  };
}

Value HCAsm::ParseOperand6(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  auto& reg = std::get<std::string>(args[3].value.val);
  auto& Mode = std::get<std::string>(args[0].value.val);

  if (!registers_assoc.contains(reg.c_str())) {
    ThrowError(
      args[3], 
      parser, 
      std::format("expected register, got unknown identifier \"{}\"", std::get<std::string>(args[3].value.val)));
  } else if (!mode_assoc.contains(Mode.c_str())) {
    ThrowError(
      args[0], 
      parser, 
      std::format("unknown data size specified: \"{}\"", Mode));
  } else if (std::get<std::string>(args[1].value.val) != "ptr") {
    ThrowError(
      args[1], 
      parser, 
      std::format("unknown keyword \"{}\" specified, \"ptr\" expected", std::get<std::string>(args[1].value.val)));
  } else if (std::get<std::uint64_t>(args[5].value.val) > 255) [[unlikely]] {
    ThrowError(
      args[5], 
      parser, 
      std::format("out of bounds integer provided: {} > 255", std::get<std::uint64_t>(args[5].value.val)));
  }

  return {
    .val = Operand {
      .type = HCAsm::OperandType::mem_reg_add_int,
      .reg = registers_assoc.at(reg.c_str()),
      .mode = mode_assoc.at(Mode.c_str()),
      .uint1 = std::get<std::uint64_t>(args[5].value.val)
    }
  };
}

Value HCAsm::ParseOperand7(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  return {
    .val = Operand {
      .type = HCAsm::OperandType::sint,
      .mode = HCAsm::Mode::none,
      .sint2 = std::get<std::int64_t>(args[0].value.val),
    }
  };
}

Value HCAsm::ParseOperand8(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  return {
    .val = Operand {
      .type = HCAsm::OperandType::uint,
      .mode = HCAsm::Mode::none,
      .uint1 = std::get<std::uint64_t>(args[0].value.val)
    }
  };
}

Value HCAsm::ParseOperand9(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  auto& reg = std::get<std::string>(args[0].value.val);

  if (!registers_assoc.contains(reg.c_str())) {
    ThrowError(
      args[0], 
      parser, 
      std::format("expected register, got unknown identifier \"{}\"", std::get<std::string>(args[0].value.val)));
  }

  return {
    .val = Operand {
      .type = HCAsm::OperandType::reg,
      .reg = registers_assoc.at(reg.c_str()),
      .mode = ModeFromRegister(registers_assoc.at(reg.c_str()))
    }
  };
}
