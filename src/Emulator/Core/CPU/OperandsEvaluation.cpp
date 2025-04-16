#include <Core/CPU/Instructions/Registers.hpp>
#include <Misc/bit_cast.hpp>
#include <Core/CPU/CPU.hpp>
#include <Exit.hpp>


HyperCPU::OperandContainer HyperCPU::CPU::GetRegister(OperandContainer& op1) {
  HyperCPU::Registers reg;
  memcpy(&reg, &op1, sizeof(HyperCPU::Registers));

  switch (reg) {
    case X0: return OperandContainer{x0};
    case X1: return OperandContainer{x1};
    case X2: return OperandContainer{x2};
    case X3: return OperandContainer{x3};
    case X4: return OperandContainer{x4};
    case X5: return OperandContainer{x5};
    case X6: return OperandContainer{x6};
    case X7: return OperandContainer{x7};

    case XH0: return OperandContainer{xh0};
    case XH1: return OperandContainer{xh1};
    case XH2: return OperandContainer{xh2};
    case XH3: return OperandContainer{xh3};
    case XH4: return OperandContainer{xh4};
    case XH5: return OperandContainer{xh5};
    case XH6: return OperandContainer{xh6};
    case XH7: return OperandContainer{xh7};

    case XL0: return OperandContainer{xl0};
    case XL1: return OperandContainer{xl1};
    case XL2: return OperandContainer{xl2};
    case XL3: return OperandContainer{xl3};
    case XL4: return OperandContainer{xl4};
    case XL5: return OperandContainer{xl5};
    case XL6: return OperandContainer{xl6};
    case XL7: return OperandContainer{xl7};

    case XLL0: return OperandContainer{xll0};
    case XLL1: return OperandContainer{xll1};
    case XLL2: return OperandContainer{xll2};
    case XLL3: return OperandContainer{xll3};

    case XLLH0: return OperandContainer{xllh0};
    case XLLH1: return OperandContainer{xllh1};
    case XLLH2: return OperandContainer{xllh2};
    case XLLH3: return OperandContainer{xllh3};

    case XLLL0: return OperandContainer{xlll0};
    case XLLL1: return OperandContainer{xlll1};
    case XLLL2: return OperandContainer{xlll2};
    case XLLL3: return OperandContainer{xlll3};

    case XBP: return OperandContainer{xbp};
    case XSP: return OperandContainer{xsp};
    case XIP: return OperandContainer{xip};
    case XGDP: return OperandContainer{xgdp};
    case XIVT: return OperandContainer{xivt};
    default: throw std::runtime_error("Invalid register");
  }
}

std::pair<HyperCPU::OperandContainer, HyperCPU::OperandContainer> HyperCPU::CPU::GetOperands(OperandTypes op_types, Mode md, OperandContainer& op1, OperandContainer& op2) {
  switch (op_types) {
    case R_R:
    case R_RM:
    case RM_R: {
      OperandContainer op_1, op_2;
      op_1 = GetRegister(op1);
      op_2 = GetRegister(op2);
      return std::make_pair(op_1, op_2);
    }
    
    case RM_M:
    case R_M:
      return std::make_pair(GetRegister(op1), op2);

    case RM_IMM:
    case R_IMM:{
      switch (md) {
        case b8:{
          std::uint8_t imm8;
          std::memcpy(&imm8, &op2, sizeof(std::uint8_t));
          return std::make_pair(GetRegister(op1), OperandContainer{HyperCPU::bit_cast<std::uint64_t>(imm8)});
        }
        case b16:{
          std::uint16_t imm16;
          std::memcpy(&imm16, &op2, sizeof(std::uint16_t));
          return std::make_pair(GetRegister(op1), OperandContainer{HyperCPU::bit_cast<std::uint64_t>(imm16)});
        }
        case b32:{
          std::uint32_t imm32;
          std::memcpy(&imm32, &op2, sizeof(std::uint32_t));
          return std::make_pair(GetRegister(op1), OperandContainer{HyperCPU::bit_cast<std::uint64_t>(imm32)});
        }
        case b64:{
          std::uint64_t imm64;
          std::memcpy(&imm64, &op2, sizeof(std::uint64_t));
          return std::make_pair(GetRegister(op1), OperandContainer{HyperCPU::bit_cast<std::uint64_t>(imm64)});
        }
      }
      break;
    }

    case M_R:
      return std::make_pair(op1, GetRegister(op2));
    
    case R:
      return std::make_pair(GetRegister(op1), nullptr);
    
    case IMM:
    case M:
      return std::make_pair(op1, nullptr);

    case NONE:
      return std::make_pair(nullptr, nullptr);
    default:
      ABORT();
  }
  return {};
}
