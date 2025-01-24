#include <Emulator/Core/CPU/Instructions/Flags.hpp>
#include <Core/BinaryTransformer.hpp>
#include <Core/Compiler.hpp>

#include <utility>

HyperCPU::OperandTypes HCAsm::BinaryTransformer::DetermineOperandTypes(Operand& op1, Operand& op2) {
  Op1T tp1;
  Op2T tp2;

  switch (op1.type) {
    case HCAsm::OperandType::reg:
      tp1 = Op1T::R; break;
    case HCAsm::OperandType::mem_reg_add_int:
    case HCAsm::OperandType::memaddr_reg:
      tp1 = Op1T::RM; break;
    case HCAsm::OperandType::sint:
    case HCAsm::OperandType::uint:
    case HCAsm::OperandType::label:
      tp1 = Op1T::IMM; break;
    case HCAsm::OperandType::memaddr_int:
      tp1 = Op1T::M; break;
    case HCAsm::OperandType::none:
      tp1 = Op1T::NONE; break;
    default:
      std::unreachable();
  }

  switch (op2.type) {
    case HCAsm::OperandType::reg:
      tp2 = Op2T::R; break;
    case HCAsm::OperandType::mem_reg_add_int:
    case HCAsm::OperandType::memaddr_reg:
      tp2 = Op2T::RM; break;
    case HCAsm::OperandType::sint:
    case HCAsm::OperandType::uint:
    case HCAsm::OperandType::label:
      tp2 = Op2T::IMM; break;
    case HCAsm::OperandType::memaddr_int:
      tp2 = Op2T::M; break;
    case HCAsm::OperandType::none:
      tp2 = Op2T::NONE; break;
    default:
      std::unreachable();
  }

  return QuickCast(QuickOR(tp1, tp2));
}



void HCAsm::BinaryTransformer::EncodeInstruction(HCAsm::Instruction& instr) {
  HyperCPU::OperandTypes types = DetermineOperandTypes(instr.op1, instr.op2);

  res.push(static_cast<std::uint16_t>(instr.opcode));

  std::uint8_t encoded_operands = 0;

  if (HasAddressAddition(instr.op1.type) && HasAddressAddition(instr.op2.type)) {
    logger.Log(HyperCPU::LogLevel::ERROR, "You can't use memory address additions for two operands!");
    std::abort();
  } else if (HasAddressAddition(instr.op1.type) || HasAddressAddition(instr.op2.type)) {
    encoded_operands |= 0b10000000;
    if (HasAddressAddition(instr.op2.type)) {
      encoded_operands |= 0b01000000;
    } else {
      // Do nothing - bit 0 means first operand
    }
  }
  
  // Handle case when one of operands is a label - we should mock the immediate 64 bit value
  if (instr.op1.type == OperandType::label) {
    std::uint64_t num = this->state->labels.at(*instr.op1.str);
    delete instr.op1.str;
    instr.op1.uint1 = num;
  } else if (instr.op2.type == OperandType::label) {
    std::uint64_t num = this->state->labels.at(*instr.op2.str);
    delete instr.op2.str;
    instr.op2.uint1 = num;
  }

  HCAsm::Mode md;
  switch (types) {
    case HyperCPU::OperandTypes::RM_M:
      if (instr.op2.mode != HCAsm::Mode::none) {
        md = instr.op2.mode;
        break;
      }
    case HyperCPU::OperandTypes::RM_IMM:
      if (instr.op1.mode == HCAsm::Mode::none) {
        logger.Log(HyperCPU::LogLevel::ERROR, "Ambiguous operand size!");
        std::abort();
      }
    case HyperCPU::OperandTypes::R_R:
    case HyperCPU::OperandTypes::R_RM:
    case HyperCPU::OperandTypes::R_M:
    case HyperCPU::OperandTypes::R_IMM:
    case HyperCPU::OperandTypes::R:
      md = instr.op1.mode;
      break;
    case HyperCPU::OperandTypes::IMM:
      md = HCAsm::Mode::b64;
      break;
    case HyperCPU::OperandTypes::RM_R:
    case HyperCPU::OperandTypes::M_R:
      md = instr.op2.mode;
      break;
    default:
      std::unreachable();
  }
  encoded_operands |= (static_cast<std::uint8_t>(md) << 4);
  encoded_operands |= static_cast<std::uint8_t>(types);

  res.push(static_cast<std::uint8_t>(encoded_operands));

  switch (types) {
    case HyperCPU::OperandTypes::R_R:
    case HyperCPU::OperandTypes::R_RM:
    case HyperCPU::OperandTypes::RM_R:
      res.push(static_cast<std::uint8_t>(instr.op1.reg));
      res.push(static_cast<std::uint8_t>(instr.op2.reg));
      break;
    case HyperCPU::OperandTypes::RM_M:
    case HyperCPU::OperandTypes::R_M:
      res.push(static_cast<std::uint8_t>(instr.op1.reg));
      res.push(instr.op2.uint1);
      break;
    case HyperCPU::OperandTypes::RM_IMM:
    case HyperCPU::OperandTypes::R_IMM:
      res.push(static_cast<std::uint8_t>(instr.op1.reg));
      switch (md) {
        case HCAsm::Mode::b8:   res.push(static_cast<std::uint8_t>(instr.op2.uint1));  break;
        case HCAsm::Mode::b16:  res.push(static_cast<std::uint16_t>(instr.op2.uint1)); break;
        case HCAsm::Mode::b32:  res.push(static_cast<std::uint32_t>(instr.op2.uint1)); break;
        case HCAsm::Mode::b64:  res.push(static_cast<std::uint64_t>(instr.op2.uint1)); break;
        default:
          std::unreachable();
      }
      break;
    case HyperCPU::OperandTypes::R:
      res.push(static_cast<std::uint8_t>(instr.op1.reg));
      break;
    case HyperCPU::OperandTypes::M:
      res.push(instr.op1.uint1);
      break;
    case HyperCPU::OperandTypes::IMM:
      switch (md) {
        case HCAsm::Mode::b8:   res.push(static_cast<std::uint8_t>(instr.op1.uint1));  break;
        case HCAsm::Mode::b16:  res.push(static_cast<std::uint16_t>(instr.op1.uint1)); break;
        case HCAsm::Mode::b32:  res.push(static_cast<std::uint32_t>(instr.op1.uint1)); break;
        case HCAsm::Mode::b64:  res.push(static_cast<std::uint64_t>(instr.op1.uint1)); break;
        default:
          std::unreachable();
      }
      break;
    case HyperCPU::OperandTypes::M_R:
      res.push(instr.op2.uint1);
      res.push(static_cast<std::uint8_t>(instr.op2.reg));
      break;
    case HyperCPU::OperandTypes::NONE:
      break;
    default:
      std::unreachable();
  }
}