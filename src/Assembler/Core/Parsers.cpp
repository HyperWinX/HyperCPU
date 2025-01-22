#include <Core/ModeNameAssoc.hpp>
#include <Core/RegNameAssoc.hpp>
#include <Core/Compiler.hpp>

using HCAsm::Value;

Value HCAsm::ParseOperand1(std::vector<Value>&& args) {
  return {
    .val = Operand {
      .type = HCAsm::OperandType::memaddr_int,
      .mode = HCAsm::Mode::none,
      .uint1 = std::get<std::uint64_t>(args[1].val)
    }
  };
}

Value HCAsm::ParseOperand2(std::vector<Value>&& args) {
  auto& reg = std::get<std::string>(args[1].val);

  if (!registers_assoc.contains(reg.c_str())) {
    logger.Log(HyperCPU::LogLevel::ERROR, "Expected register, got unknown identifier \"{}\"", reg);
    std::abort();
  }

  return {
    .val = Operand {
      .type = HCAsm::OperandType::memaddr_reg,
      .reg = registers_assoc.at(reg.c_str()),
      .mode = HCAsm::Mode::none,
    }
  };
}

Value HCAsm::ParseOperand3(std::vector<Value>&& args) {
  auto& reg = std::get<std::string>(args[1].val);

  if (!registers_assoc.contains(reg.c_str())) {
    logger.Log(HyperCPU::LogLevel::ERROR, "Expected register, got unknown identifier \"{}\"", reg);
    std::abort();
  }

  return {
    .val = Operand {
      .type = HCAsm::OperandType::mem_reg_add_int,
      .reg = registers_assoc.at(reg.c_str()),
      .mode = HCAsm::Mode::none,
      .uint1 = std::get<std::uint64_t>(args[3].val)
    }
  };
}

Value HCAsm::ParseOperand4(std::vector<Value>&& args) {
  auto& Mode = std::get<std::string>(args[0].val);

  if (!mode_assoc.contains(Mode.c_str())) {
    logger.Log(HyperCPU::LogLevel::ERROR, "Unknown data size: {}", Mode);
    std::abort();
  } else if (std::get<std::string>(args[1].val) != "ptr") {
    logger.Log(HyperCPU::LogLevel::ERROR, "Cannot use data size without \"ptr\"");
    std::abort();
  }

  return {
    .val = Operand {
      .type = HCAsm::OperandType::memaddr_int,
      .mode = mode_assoc.at(Mode.c_str()),
      .uint1 = std::get<std::uint64_t>(args[3].val)
    }
  };
}

Value HCAsm::ParseOperand5(std::vector<Value>&& args) {
  auto& reg = std::get<std::string>(args[3].val);
  auto& Mode = std::get<std::string>(args[0].val);

  if (!registers_assoc.contains(reg.c_str())) {
    logger.Log(HyperCPU::LogLevel::ERROR, "Expected register, got unknown identifier \"{}\"", reg);
    std::abort();
  } else if (!mode_assoc.contains(Mode.c_str())) {
    logger.Log(HyperCPU::LogLevel::ERROR, "Unknown data size: {}", Mode);
    std::abort();
  } else if (std::get<std::string>(args[1].val) != "ptr") {
    logger.Log(HyperCPU::LogLevel::ERROR, "Cannot use data size without \"ptr\"");
    std::abort();
  }

  return {
    .val = Operand {
      .type = HCAsm::OperandType::memaddr_reg,
      .reg = registers_assoc.at(reg.c_str()),
      .mode = mode_assoc.at(Mode.c_str()),
    }
  };
}

Value HCAsm::ParseOperand6(std::vector<Value>&& args) {
  auto& reg = std::get<std::string>(args[3].val);
  auto& Mode = std::get<std::string>(args[0].val);

  if (!registers_assoc.contains(reg.c_str())) {
    logger.Log(HyperCPU::LogLevel::ERROR, "Expected register, got unknown identifier \"{}\"", reg);
    std::abort();
  } else if (!mode_assoc.contains(Mode.c_str())) {
    logger.Log(HyperCPU::LogLevel::ERROR, "Unknown data size: {}", Mode);
    std::abort();
  } else if (std::get<std::string>(args[1].val) != "ptr") {
    logger.Log(HyperCPU::LogLevel::ERROR, "Cannot use data size without \"ptr\"");
    std::abort();
  }

  return {
    .val = Operand {
      .type = HCAsm::OperandType::mem_reg_add_int,
      .reg = registers_assoc.at(reg.c_str()),
      .mode = mode_assoc.at(Mode.c_str()),
      .uint1 = std::get<std::uint64_t>(args[5].val)
    }
  };
}

Value HCAsm::ParseOperand7(std::vector<Value>&& args) {
  return {
    .val = Operand {
      .type = HCAsm::OperandType::sint,
      .mode = HCAsm::Mode::none,
      .sint2 = std::get<std::int64_t>(args[0].val),
    }
  };
}

Value HCAsm::ParseOperand8(std::vector<Value>&& args) {
  return {
    .val = Operand {
      .type = HCAsm::OperandType::uint,
      .mode = HCAsm::Mode::none,
      .uint1 = std::get<std::uint64_t>(args[0].val)
    }
  };
}

Value HCAsm::ParseOperand9(std::vector<Value>&& args) {
  auto& reg = std::get<std::string>(args[0].val);

  if (!registers_assoc.contains(reg.c_str())) {
    logger.Log(HyperCPU::LogLevel::ERROR, "Expected register, got unknown identifier \"{}\"", reg);
    std::abort();
  }

  return {
    .val = Operand {
      .type = HCAsm::OperandType::reg,
      .reg = registers_assoc.at(reg.c_str()),
      .mode = ModeFromRegister(registers_assoc.at(reg.c_str()))
    }
  };
}
