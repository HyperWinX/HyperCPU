#pragma once

#include "emulator/core/cpu/instructions/flags.hpp"
#include "emulator/core/cpu/instructions/opcodes.hpp"
#include <string>

#include <pog/parser.h>

#include <logger/logger.hpp>
#include <emulator/core/cpu/instructions/registers.hpp>
#include <vector>


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
    memaddr_reg,
    memaddr_int,
    none
  };

  enum class mode {
    b8,
    b16,
    b32,
    b64,
    none
  };

  struct operand {
    operand_type type;
    hypercpu::registers reg;
    enum mode mode;
    union {
      std::uint64_t uint1;
      std::int64_t sint2;
    };
  };

  struct instruction {
    hypercpu::opcode opcode;
    operand op1, op2;
  };

  struct label {
    std::uint64_t index;
  };

  struct value {
    std::variant<std::int64_t, std::uint64_t, std::string, operand, instruction> val;
  };

  struct compiler_state {
    std::vector<instruction> ir;
    std::vector<label> labels;
    std::uint64_t code_size;
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
  value parse_operand7(std::vector<value>&& args);
  value parse_operand8(std::vector<value>&& args);
  value parse_operand9(std::vector<value>&& args);
  value parse_operand10(std::vector<value>&& args);
  value parse_operand11(std::vector<value>&& args);

  value compile_stmt1(std::vector<value>&& args);
  value compile_stmt2(std::vector<value>&& args);
  value compile_stmt3(std::vector<value>&& args);
  value compile_label(std::vector<value>&& args);

  extern hypercpu::logger logger;
  extern compiler_state* current_state;
  extern std::uint64_t current_index;

  class hcasm_compiler {
  private:
    pog::Parser<value> parser;
    compiler_state* state;

  public:
    hcasm_compiler(hypercpu::loglevel lvl = hypercpu::loglevel::WARNING);

    void compile(std::string& source, std::string& destination);
    compiler_state transform_to_IR(std::string& src);
    unsigned char* transform_to_binary(compiler_state& ir);
  };
  
}