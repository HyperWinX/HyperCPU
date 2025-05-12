#pragma once

#include <spdlog/spdlog.h>

#include "Assembler/Core/Compiler.hpp"
#include "Common/LanguageSpec/Flags.hpp"
#include "PCH/CStd.hpp"

namespace HCAsm {
  struct BinaryResult;
  struct Instruction;
  struct Operand;

  enum class Op1T : std::uint8_t {
    R = 0x10,
    M = 0x20,
    IMM = 0x30,
    RM = 0x40,
    NONE = 0x50
  };

  enum class Op2T : std::uint8_t {
    R = 0x01,
    M = 0x02,
    IMM = 0x03,
    RM = 0x04,
    NONE = 0x05
  };

  constexpr inline std::uint8_t QuickOR(Op1T a, Op2T b) {
    return static_cast<std::uint8_t>(a) | static_cast<std::uint8_t>(b);
  }

  constexpr inline bool HasAddressAddition(HCAsm::OperandType tp) {
    return tp == OperandType::mem_reg_add_int;
  }

  enum class OperandTypes : std::uint8_t {
    R_R = QuickOR(Op1T::R, Op2T::R),
    R_RM = QuickOR(Op1T::R, Op2T::RM),
    R_M = QuickOR(Op1T::R, Op2T::M),
    R_IMM = QuickOR(Op1T::R, Op2T::IMM),
    RM_R = QuickOR(Op1T::RM, Op2T::R),
    RM_M = QuickOR(Op1T::RM, Op2T::M),
    RM_IMM = QuickOR(Op1T::RM, Op2T::IMM),
    M_R = QuickOR(Op1T::M, Op2T::R),
    R = QuickOR(Op1T::R, Op2T::NONE),
    M = QuickOR(Op1T::M, Op2T::NONE),
    IMM = QuickOR(Op1T::IMM, Op2T::NONE),
    NONE = QuickOR(Op1T::NONE, Op2T::NONE),
  };

  constexpr HyperCPU::OperandTypes QuickCast(std::uint8_t x) {
    switch (static_cast<OperandTypes>(x)) {
    case OperandTypes::R_R:
      return HyperCPU::OperandTypes::R_R;
    case OperandTypes::R_RM:
      return HyperCPU::OperandTypes::R_RM;
    case OperandTypes::R_M:
      return HyperCPU::OperandTypes::R_M;
    case OperandTypes::R_IMM:
      return HyperCPU::OperandTypes::R_IMM;
    case OperandTypes::RM_R:
      return HyperCPU::OperandTypes::RM_R;
    case OperandTypes::RM_M:
      return HyperCPU::OperandTypes::RM_M;
    case OperandTypes::RM_IMM:
      return HyperCPU::OperandTypes::RM_IMM;
    case OperandTypes::M_R:
      return HyperCPU::OperandTypes::M_R;
    case OperandTypes::R:
      return HyperCPU::OperandTypes::R;
    case OperandTypes::M:
      return HyperCPU::OperandTypes::M;
    case OperandTypes::IMM:
      return HyperCPU::OperandTypes::IMM;
    case OperandTypes::NONE:
      return HyperCPU::OperandTypes::NONE;
    default:
      spdlog::error("Invalid operand types!");
      std::abort();
    }
  }

  constexpr HyperCPU::Mode cast_mode(HCAsm::Mode md) {
    switch (md) {
    case HCAsm::Mode::b8:
      return HyperCPU::Mode::b8;
    case HCAsm::Mode::b16:
      return HyperCPU::Mode::b16;
    case HCAsm::Mode::b32:
      return HyperCPU::Mode::b32;
    case HCAsm::Mode::b64:
      return HyperCPU::Mode::b64;
    default:
      std::abort();
    }
  }

  class BinaryTransformer {
  public:
    // TODO: move to src
    BinaryTransformer(BinaryResult& result, CompilerState* state = nullptr)
        : res(result), state(state) {
    }

    void EncodeInstruction(Instruction& instr);
    HyperCPU::OperandTypes DetermineOperandTypes(Operand& op1, Operand& op2);

  private:
    BinaryResult& res;
    CompilerState* state;
  };
} // namespace HCAsm
