#include "core/mode_name_assoc.hpp"
#include <core/compiler.hpp>
#include <core/reg_name_assoc.hpp>

using hcasm::value;

value hcasm::parse_operand1(std::vector<value>&& args) {
  return {
    .val = operand {
      .type = hcasm::operand_type::memaddr_int,
      .mode = hcasm::mode::none,
      .uint1 = std::get<std::uint64_t>(args[1].val)
    }
  };
}

value hcasm::parse_operand2(std::vector<value>&& args) {
  auto& reg = std::get<std::string>(args[1].val);

  if (!registers_assoc.contains(reg.c_str())) {
    logger.log(hypercpu::loglevel::ERROR, "Expected register, got unknown identifier \"{}\"", reg);
    std::abort();
  }

  return {
    .val = operand {
      .type = hcasm::operand_type::memaddr_reg,
      .reg = registers_assoc.at(reg.c_str()),
      .mode = hcasm::mode::none,
    }
  };
}

value hcasm::parse_operand3(std::vector<value>&& args) {
  auto& reg = std::get<std::string>(args[1].val);

  if (!registers_assoc.contains(reg.c_str())) {
    logger.log(hypercpu::loglevel::ERROR, "Expected register, got unknown identifier \"{}\"", reg);
    std::abort();
  }

  return {
    .val = operand {
      .type = hcasm::operand_type::mem_reg_add_int,
      .reg = registers_assoc.at(reg.c_str()),
      .mode = hcasm::mode::none,
      .uint1 = std::get<std::uint64_t>(args[3].val)
    }
  };
}

value hcasm::parse_operand4(std::vector<value>&& args) {
  auto& reg = std::get<std::string>(args[1].val);

  if (!registers_assoc.contains(reg.c_str())) {
    logger.log(hypercpu::loglevel::ERROR, "Expected register, got unknown identifier \"{}\"", reg);
    std::abort();
  }

  return {
    .val = operand {
      .type = hcasm::operand_type::mem_reg_sub_int,
      .reg = registers_assoc.at(reg.c_str()),
      .mode = hcasm::mode::none,
      .uint1 = std::get<std::uint64_t>(args[3].val)
    }
  };
}

value hcasm::parse_operand5(std::vector<value>&& args) {
  auto& mode = std::get<std::string>(args[0].val);

  if (!mode_assoc.contains(mode.c_str())) {
    logger.log(hypercpu::loglevel::ERROR, "Unknown data size: {}", mode);
    std::abort();
  }

  return {
    .val = operand {
      .type = hcasm::operand_type::memaddr_int,
      .mode = mode_assoc.at(mode.c_str()),
      .uint1 = std::get<std::uint64_t>(args[3].val)
    }
  };
}

value hcasm::parse_operand6(std::vector<value>&& args) {
  auto& reg = std::get<std::string>(args[3].val);
  auto& mode = std::get<std::string>(args[0].val);

  if (!registers_assoc.contains(reg.c_str())) {
    logger.log(hypercpu::loglevel::ERROR, "Expected register, got unknown identifier \"{}\"", reg);
    std::abort();
  } else if (!mode_assoc.contains(mode.c_str())) {
    logger.log(hypercpu::loglevel::ERROR, "Unknown data size: {}", mode);
    std::abort();
  }

  return {
    .val = operand {
      .type = hcasm::operand_type::memaddr_reg,
      .reg = registers_assoc.at(reg.c_str()),
      .mode = mode_assoc.at(mode.c_str()),
    }
  };
}

value hcasm::parse_operand7(std::vector<value>&& args) {
  auto& reg = std::get<std::string>(args[3].val);
  auto& mode = std::get<std::string>(args[0].val);

  if (!registers_assoc.contains(reg.c_str())) {
    logger.log(hypercpu::loglevel::ERROR, "Expected register, got unknown identifier \"{}\"", reg);
    std::abort();
  } else if (!mode_assoc.contains(mode.c_str())) {
    logger.log(hypercpu::loglevel::ERROR, "Unknown data size: {}", mode);
    std::abort();
  }

  return {
    .val = operand {
      .type = hcasm::operand_type::mem_reg_add_int,
      .reg = registers_assoc.at(reg.c_str()),
      .mode = mode_assoc.at(mode.c_str()),
      .uint1 = std::get<std::uint64_t>(args[5].val)
    }
  };
}

value hcasm::parse_operand8(std::vector<value>&& args) {
  auto& reg = std::get<std::string>(args[3].val);
  auto& mode = std::get<std::string>(args[0].val);

  if (!registers_assoc.contains(reg.c_str())) {
    logger.log(hypercpu::loglevel::ERROR, "Expected register, got unknown identifier \"{}\"", reg);
    std::abort();
  } else if (!mode_assoc.contains(mode.c_str())) {
    logger.log(hypercpu::loglevel::ERROR, "Unknown data size: {}", mode);
    std::abort();
  }

  return {
    .val = operand {
      .type = hcasm::operand_type::mem_reg_sub_int,
      .reg = registers_assoc.at(reg.c_str()),
      .mode = mode_assoc.at(mode.c_str()),
      .uint1 = std::get<std::uint64_t>(args[5].val)
    }
  };
}

value hcasm::parse_operand9(std::vector<value>&& args) {
  return {
    .val = operand {
      .type = hcasm::operand_type::sint,
      .mode = hcasm::mode::none,
      .sint2 = std::get<std::int64_t>(args[0].val),
    }
  };
}

value hcasm::parse_operand10(std::vector<value>&& args) {
  return {
    .val = operand {
      .type = hcasm::operand_type::uint,
      .mode = hcasm::mode::none,
      .uint1 = std::get<std::uint64_t>(args[0].val)
    }
  };
}

value hcasm::parse_operand11(std::vector<value>&& args) {
  auto& reg = std::get<std::string>(args[0].val);

  if (!registers_assoc.contains(reg.c_str())) {
    logger.log(hypercpu::loglevel::ERROR, "Expected register, got unknown identifier \"{}\"", reg);
    std::abort();
  }

  return {
    .val = operand {
      .type = hcasm::operand_type::reg,
      .reg = registers_assoc.at(reg.c_str()),
      .mode = hcasm::mode::none,
    }
  };
}
