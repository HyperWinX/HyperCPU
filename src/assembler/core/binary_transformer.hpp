#pragma once

#include "core/compiler.hpp"
#include <mapbox/eternal.hpp>

#include <emulator/core/cpu/instructions/flags.hpp>

namespace hcasm {
  struct binary_result;
  struct instruction;
  struct operand;

  enum class op1_t : std::uint8_t {
    R     = 0x10,
    M     = 0x20,
    IMM   = 0x30,
    RM    = 0x40,
    NONE  = 0x50
  };

  enum class op2_t : std::uint8_t {
    R     = 0x01,
    M     = 0x02,
    IMM   = 0x03,
    RM    = 0x04,
    NONE  = 0x05
  };

  constexpr inline std::uint8_t quick_or(op1_t a, op2_t b) {
    return static_cast<std::uint8_t>(a) | static_cast<std::uint8_t>(b);
  }

  constexpr inline bool has_addr_addition(hcasm::operand_type tp) {
    return tp == operand_type::mem_reg_add_int;
  }

  enum class operand_types : std::uint8_t {
    R_R     = quick_or(op1_t::R, op2_t::R),
    R_RM    = quick_or(op1_t::R, op2_t::RM),
    R_M     = quick_or(op1_t::R, op2_t::M),
    R_IMM   = quick_or(op1_t::R, op2_t::IMM),
    RM_R    = quick_or(op1_t::RM, op2_t::R),
    RM_M    = quick_or(op1_t::RM, op2_t::M),
    RM_IMM  = quick_or(op1_t::RM, op2_t::IMM),
    M_R     = quick_or(op1_t::M, op2_t::R),
    R       = quick_or(op1_t::R, op2_t::NONE),
    M       = quick_or(op1_t::M, op2_t::NONE),
    IMM     = quick_or(op1_t::IMM, op2_t::NONE),
    NONE    = quick_or(op1_t::NONE, op2_t::NONE),
  };

  constexpr hypercpu::operand_types quick_cast(std::uint8_t x) {
    switch (static_cast<operand_types>(x)) {
      case operand_types::R_R:     return hypercpu::operand_types::R_R;
      case operand_types::R_RM:    return hypercpu::operand_types::R_RM;
      case operand_types::R_M:     return hypercpu::operand_types::R_M;
      case operand_types::R_IMM:   return hypercpu::operand_types::R_IMM;
      case operand_types::RM_R:    return hypercpu::operand_types::RM_R;
      case operand_types::RM_M:    return hypercpu::operand_types::RM_M;
      case operand_types::RM_IMM:  return hypercpu::operand_types::RM_IMM;
      case operand_types::M_R:     return hypercpu::operand_types::M_R;
      case operand_types::R:       return hypercpu::operand_types::R;
      case operand_types::M:       return hypercpu::operand_types::M;
      case operand_types::IMM:     return hypercpu::operand_types::IMM;
      case operand_types::NONE:    return hypercpu::operand_types::NONE;
      default:
        logger.log(hypercpu::loglevel::ERROR, "Invalid operand types!");
        std::abort();
    }
  }

  constexpr hypercpu::mode cast_mode(hcasm::mode md) {
    switch (md) {
      case hcasm::mode::b8:   return hypercpu::mode::b8;
      case hcasm::mode::b16:  return hypercpu::mode::b16;
      case hcasm::mode::b32:  return hypercpu::mode::b32;
      case hcasm::mode::b64:  return hypercpu::mode::b64;
      default:
        std::unreachable();
    }
  }



  class binary_transformer {
  public:
    binary_transformer(binary_result& result) : res(result) { }

    void encode_instruction(instruction& instr);
    hypercpu::operand_types determine_op_types(operand& op1, operand& op2);
  private:
    binary_result& res;
  };
}