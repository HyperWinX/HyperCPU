#pragma once

#include <type_traits>
#include <utility>
#include <string>
#include <vector>
#include <queue>

#include <Emulator/Core/CPU/Instructions/Registers.hpp>
#include <Emulator/Core/CPU/Instructions/Flags.hpp>
#include <Emulator/Core/CPU/Instructions/Opcodes.hpp>
#include <Emulator/Main/Main.hpp>
#include <Logger/Logger.hpp>

#include <pog/parser.h>
#include <pog/line_spec.h>


namespace HCAsm {
  enum class ValueType {
    operand,
    string,
    sint,
    uint,
  };

  enum class OperandType {
    reg,
    mem_reg_add_int,
    sint,
    uint,
    memaddr_reg,
    memaddr_int,
    label,
    none
  };

  enum class Mode : std::uint8_t {
    b8  = 0b00,
    b16 = 0b01,
    b32 = 0b10,
    b64 = 0b11,
    none
  };

  struct Operand {
    OperandType type;
    HyperCPU::Registers reg;
    enum Mode mode;
    bool needs_resolve;
    union {
      std::uint64_t uint1;
      std::int64_t sint2;
      std::string* str;
    };
  };

  struct Instruction {
    HyperCPU::Opcode opcode;
    Operand op1, op2;
  };

  struct Label {
    std::string name;
    std::uint64_t index;
  };

  struct Value {
    std::variant<std::int64_t, std::uint64_t, std::string, Operand, Instruction> val;
  };

  struct BinaryResult {
    unsigned char* binary;
    std::uint64_t ptr;

    template<typename T, std::enable_if_t<
      std::is_integral_v<T> && 
      std::is_unsigned_v<T>, bool> = true>
    constexpr inline void push(T data) {
      std::memcpy(binary + ptr, &data, sizeof(data));
      ptr += sizeof(data);
    }

    ~BinaryResult() {
      delete[] binary;
    }
  };

  struct PendingLabelReferenceResolve {
    Operand& op;
    std::vector<pog::TokenWithLineSpec<Value>> args;
  };

  struct LineCounter {
    int a;
  };

  // Needs improvements and optimizations
  struct CompilerState {
    CompilerState() : code_size(0) { }

    std::vector<PendingLabelReferenceResolve> pending_resolves;
    std::vector<pog::TokenWithLineSpec<Value>> tmp_args;
    std::vector<std::variant<Instruction, Label>> ir;
    std::unordered_map<std::string, std::uint64_t> labels;
    std::uint64_t code_size;
  };

  constexpr inline Mode ModeFromRegister(HyperCPU::Registers reg) {
    using namespace HyperCPU;
    switch (reg) {
      case Registers::X0:
      case Registers::X1:
      case Registers::X2:
      case Registers::X3:
      case Registers::X4:
      case Registers::X5:
      case Registers::X6:
      case Registers::X7:
        return Mode::b64;
      case Registers::XH0:
      case Registers::XH1:
      case Registers::XH2:
      case Registers::XH3:
      case Registers::XH4:
      case Registers::XH5:
      case Registers::XH6:
      case Registers::XH7:
      case Registers::XL0:
      case Registers::XL1:
      case Registers::XL2:
      case Registers::XL3:
      case Registers::XL4:
      case Registers::XL5:
      case Registers::XL6:
      case Registers::XL7:
        return Mode::b32;
      case Registers::XLL0:
      case Registers::XLL1:
      case Registers::XLL2:
      case Registers::XLL3:
        return Mode::b16;
      case Registers::XLLH0:
      case Registers::XLLH1:
      case Registers::XLLH2:
      case Registers::XLLH3:
      case Registers::XLLL0:
      case Registers::XLLL1:
      case Registers::XLLL2:
      case Registers::XLLL3:
        return Mode::b8;
      default:
        std::unreachable();
    }
  }

  std::string_view FindLine(const pog::LineSpecialization&, const std::string_view&);
  void WriteResultFile(HyperCPU::FileType type, HCAsm::BinaryResult& result, std::ofstream& output, std::uint32_t code_size);

  [[noreturn]] void ThrowError(pog::TokenWithLineSpec<Value>& err_token, pog::Parser<Value>& parser, std::string err_msg);

  Value TokenizeSignedInt(std::string_view str);
  Value TokenizeUnsignedInt(std::string_view str);
  Value TokenizeString(std::string_view str);
  Value TokenizeHexadecimal(std::string_view str);
  Value TokenizeIdentifier(std::string_view str);
  Value TokenizeBinary(std::string_view str);

  Value ParseOperand1(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value ParseOperand2(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value ParseOperand3(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value ParseOperand4(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value ParseOperand5(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value ParseOperand6(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value ParseOperand7(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value ParseOperand8(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value ParseOperand9(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value parse_operand10(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value parse_operand11(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);

  Value CompileStatement1(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value CompileStatement2(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value CompileStatement3(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value CompileLabel(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);

  extern HyperCPU::Logger logger;
  extern CompilerState* current_state;
  extern std::uint64_t current_index;

  class HCAsmCompiler {
  public:
    HCAsmCompiler(HyperCPU::LogLevel lvl = HyperCPU::LogLevel::WARNING);

    BinaryResult Compile(std::string& contents, std::uint32_t& code_size);
    CompilerState TransformToIR(std::string& src);
    BinaryResult TransformToBinary(CompilerState& ir);

  private:
    pog::Parser<Value> parser;
    CompilerState* state;
    std::queue<std::string> files;

    constexpr inline std::uint8_t OperandSize(const Operand op);
    std::uint8_t InstructionSize(const Instruction& instr);
  };
  
}
