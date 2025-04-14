#include <Core/CPU/Instructions/Registers.hpp>
#include <Misc/bit_cast.hpp>
#include <Core/CPU/CPU.hpp>
#include <Exit.hpp>


OperandContainer HyperCPU::CPU::GetRegister(OperandContainer& op1) {
  HyperCPU::Registers reg;
  memcpy(&reg, &op1, sizeof(HyperCPU::Registers));

  switch (reg) {
    case X0: return HyperCPU::bit_cast<std::uint64_t>(x0);
    case X1: return reinterpret_cast<std::uint64_t>(x1);
    case X2: return reinterpret_cast<std::uint64_t>(x2);
    case X3: return reinterpret_cast<std::uint64_t>(x3);
    case X4: return reinterpret_cast<std::uint64_t>(x4);
    case X5: return reinterpret_cast<std::uint64_t>(x5);
    case X6: return reinterpret_cast<std::uint64_t>(x6);
    case X7: return reinterpret_cast<std::uint64_t>(x7);

    case XH0: return reinterpret_cast<std::uint64_t>(xh0);
    case XH1: return reinterpret_cast<std::uint64_t>(xh1);
    case XH2: return reinterpret_cast<std::uint64_t>(xh2);
    case XH3: return reinterpret_cast<std::uint64_t>(xh3);
    case XH4: return reinterpret_cast<std::uint64_t>(xh4);
    case XH5: return reinterpret_cast<std::uint64_t>(xh5);
    case XH6: return reinterpret_cast<std::uint64_t>(xh6);
    case XH7: return reinterpret_cast<std::uint64_t>(xh7);

    case XL0: return reinterpret_cast<std::uint64_t>(xl0);
    case XL1: return reinterpret_cast<std::uint64_t>(xl1);
    case XL2: return reinterpret_cast<std::uint64_t>(xl2);
    case XL3: return reinterpret_cast<std::uint64_t>(xl3);
    case XL4: return reinterpret_cast<std::uint64_t>(xl4);
    case XL5: return reinterpret_cast<std::uint64_t>(xl5);
    case XL6: return reinterpret_cast<std::uint64_t>(xl6);
    case XL7: return reinterpret_cast<std::uint64_t>(xl7);

    case XLL0: return reinterpret_cast<std::uint64_t>(xll0);
    case XLL1: return reinterpret_cast<std::uint64_t>(xll1);
    case XLL2: return reinterpret_cast<std::uint64_t>(xll2);
    case XLL3: return reinterpret_cast<std::uint64_t>(xll3);

    case XLLH0: return reinterpret_cast<std::uint64_t>(xllh0);
    case XLLH1: return reinterpret_cast<std::uint64_t>(xllh1);
    case XLLH2: return reinterpret_cast<std::uint64_t>(xllh2);
    case XLLH3: return reinterpret_cast<std::uint64_t>(xllh3);

    case XLLL0: return reinterpret_cast<std::uint64_t>(xlll0);
    case XLLL1: return reinterpret_cast<std::uint64_t>(xlll1);
    case XLLL2: return reinterpret_cast<std::uint64_t>(xlll2);
    case XLLL3: return reinterpret_cast<std::uint64_t>(xlll3);

    case XBP: return reinterpret_cast<std::uint64_t>(xbp);
    case XSP: return reinterpret_cast<std::uint64_t>(xsp);
    case XIP: return reinterpret_cast<std::uint64_t>(xip);
    case XGDP: return reinterpret_cast<std::uint64_t>(xgdp);
    case XIVT: return reinterpret_cast<std::uint64_t>(xivt);
    default: throw std::runtime_error("Invalid register");
  }
}

std::pair<OperandContainer, OperandContainer> HyperCPU::CPU::GetOperands(OperandTypes op_types, Mode md, OperandContainer op1, OperandContainer op2) {
  switch (op_types) {
    case R_R:
    case R_RM:
    case RM_R: {
      std::uint64_t op_1, op_2;
      op_1 = GetRegister(op1);
      op_2 = GetRegister(op2);
      return std::make_pair(op_1, op_2);
    }
    
    case RM_M:
    case R_M:
      return std::make_pair(GetRegister(op1), std::bit_cast<std::uint64_t>(op2));

    case RM_IMM:
    case R_IMM:{
      switch (md) {
        case b8:{
          std::uint8_t imm8;
          std::memcpy(&imm8, &op2, sizeof(std::uint8_t));
          return std::make_pair(GetRegister(op1), HyperCPU::bit_cast<std::uint64_t>(imm8));
        }
        case b16:{
          std::uint16_t imm16;
          std::memcpy(&imm16, &op2, sizeof(std::uint16_t));
          return std::make_pair(GetRegister(op1), HyperCPU::bit_cast<std::uint64_t>(imm16));
        }
        case b32:{
          std::uint32_t imm32;
          std::memcpy(&imm32, &op2, sizeof(std::uint32_t));
          return std::make_pair(GetRegister(op1), HyperCPU::bit_cast<std::uint64_t>(imm32));
        }
        case b64:{
          std::uint64_t imm64;
          std::memcpy(&imm64, &op2, sizeof(std::uint64_t));
          return std::make_pair(GetRegister(op1), HyperCPU::bit_cast<std::uint64_t>(imm64));
        }
      }
      break;
    }

    case M_R:
      return std::make_pair(std::bit_cast<std::uint64_t>(op1), GetRegister(op2));
    
    case R:
      return std::make_pair(GetRegister(op1), nullptr);
    
    case IMM:
    case M:
      return std::make_pair(std::bit_cast<std::uint64_t>(op1), nullptr);

    case NONE:
      return std::make_pair(nullptr, nullptr);
    default:
      ABORT();
  }
  return {};
}
