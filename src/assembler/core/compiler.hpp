#pragma once

#include "emulator/core/cpu/instructions/flags.hpp"
#include "emulator/core/cpu/instructions/opcodes.hpp"
#include <string>

#include <pog/parser.h>

#include <logger/logger.hpp>
#include <emulator/core/cpu/instructions/registers.hpp>
#include <type_traits>
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
    sint,
    uint,
    memaddr_reg,
    memaddr_int,
    none
  };

  enum class mode : std::uint8_t {
    b8  = 0b00,
    b16 = 0b01,
    b32 = 0b10,
    b64 = 0b11,
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
    std::string name;
    std::uint64_t index;
  };

  struct value {
    std::variant<std::int64_t, std::uint64_t, std::string, operand, instruction> val;
  };

  struct binary_result {
    unsigned char* binary;
    std::uint64_t ptr;

    template<typename T, std::enable_if_t<
      std::is_integral_v<T> && 
      std::is_unsigned_v<T>, bool> = true>
    constexpr inline void push(T data) {
      std::memcpy(binary + ptr, &data, sizeof(data));
      ptr += sizeof(data);
    }

    ~binary_result() {
      delete[] binary;
    }
  };

  struct line_counter {
    int a;
  };

  struct compiler_state {
    compiler_state() : code_size(0) { }

    std::vector<std::variant<instruction, label>> ir;
    std::unordered_map<std::string, std::uint64_t> labels;
    std::uint64_t code_size;
  };

  constexpr inline mode mode_from_register(hypercpu::registers reg) {
    using namespace hypercpu;
    switch (reg) {
      case registers::X0:
      case registers::X1:
      case registers::X2:
      case registers::X3:
      case registers::X4:
      case registers::X5:
      case registers::X6:
      case registers::X7:
        return mode::b64;
      case registers::XH0:
      case registers::XH1:
      case registers::XH2:
      case registers::XH3:
      case registers::XH4:
      case registers::XH5:
      case registers::XH6:
      case registers::XH7:
      case registers::XL0:
      case registers::XL1:
      case registers::XL2:
      case registers::XL3:
      case registers::XL4:
      case registers::XL5:
      case registers::XL6:
      case registers::XL7:
        return mode::b32;
      case registers::XLL0:
      case registers::XLL1:
      case registers::XLL2:
      case registers::XLL3:
        return mode::b16;
      case registers::XLLH0:
      case registers::XLLH1:
      case registers::XLLH2:
      case registers::XLLH3:
      case registers::XLLL0:
      case registers::XLLL1:
      case registers::XLLL2:
      case registers::XLLL3:
        return mode::b8;
      default:
        std::unreachable();
    }
  }

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
  public:
    hcasm_compiler(hypercpu::loglevel lvl = hypercpu::loglevel::WARNING);

    void compile(std::string& source, std::string& destination);
    compiler_state transform_to_IR(std::string& src);
    binary_result transform_to_binary(compiler_state& ir);

  private:
    pog::Parser<value> parser;
    compiler_state* state;

    constexpr inline std::uint8_t operand_size(operand op);
    std::uint8_t instruction_size(instruction& instr);
  };
  
}