#pragma once

#include <string>

#include <pog/parser.h>

#include <logger/logger.hpp>
#include <emulator/core/cpu/instructions/registers.hpp>


namespace hcasm {
  enum class value_type {
    operand,
    string,
    sint,
    uint
  };

  enum class operand_type {
    reg,
    mem_reg_add_int,
    mem_reg_sub_int,
    sint,
    uint,
    memaddr
  };

  struct operand {
    operand_type type;
    hypercpu::registers reg1, reg2;
    union {
      std::uint64_t uint1;
      std::int64_t sint2;
    };
  };

  struct value {
    std::variant<std::int64_t, std::uint64_t, std::string, operand> val;
  };

  value tokenize_sint(std::string_view str);
  value tokenize_uint(std::string_view str);
  value tokenize_str(std::string_view str);
  value tokenize_hex(std::string_view str);
  value tokenize_ident(std::string_view str);
  value tokenize_binary(std::string_view str);

  value parse_operand1(std::vector<value>&& args);
  value parse_operand2(std::vector<value>&& args);
  value parse_operand3(std::vector<value>&& args);
  value parse_operand4(std::vector<value>&& args);
  value parse_operand5(std::vector<value>&& args);
  value parse_operand6(std::vector<value>&& args);

  class hcasm_compiler {
  private:
    pog::Parser<value> parser;
    hypercpu::logger logger;

  public:
    hcasm_compiler(hypercpu::loglevel lvl = hypercpu::loglevel::WARNING);
    void compile(std::string& source, std::string& dest);
  };
  
}