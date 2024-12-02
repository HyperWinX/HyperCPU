#include <iostream>

#include <core/cpu/cpu.hpp>
#include <core/cpu/instructions/registers.hpp>

void* hypercpu::cpu::get_register(std::size_t& op1) {
  hypercpu::registers reg;
  memcpy(&reg, &op1, sizeof(hypercpu::registers));

  switch (reg) {
    case X0: return reinterpret_cast<void*>(x0);
    case X1: return reinterpret_cast<void*>(x1);
    case X2: return reinterpret_cast<void*>(x2);
    case X3: return reinterpret_cast<void*>(x3);
    case X4: return reinterpret_cast<void*>(x4);
    case X5: return reinterpret_cast<void*>(x5);
    case X6: return reinterpret_cast<void*>(x6);
    case X7: return reinterpret_cast<void*>(x7);

    case XH0: return reinterpret_cast<void*>(xh0);
    case XH1: return reinterpret_cast<void*>(xh1);
    case XH2: return reinterpret_cast<void*>(xh2);
    case XH3: return reinterpret_cast<void*>(xh3);
    case XH4: return reinterpret_cast<void*>(xh4);
    case XH5: return reinterpret_cast<void*>(xh5);
    case XH6: return reinterpret_cast<void*>(xh6);
    case XH7: return reinterpret_cast<void*>(xh7);

    case XL0: return reinterpret_cast<void*>(xl0);
    case XL1: return reinterpret_cast<void*>(xl1);
    case XL2: return reinterpret_cast<void*>(xl2);
    case XL3: return reinterpret_cast<void*>(xl3);
    case XL4: return reinterpret_cast<void*>(xl4);
    case XL5: return reinterpret_cast<void*>(xl5);
    case XL6: return reinterpret_cast<void*>(xl6);
    case XL7: return reinterpret_cast<void*>(xl7);

    case XLL0: return reinterpret_cast<void*>(xll0);
    case XLL1: return reinterpret_cast<void*>(xll1);
    case XLL2: return reinterpret_cast<void*>(xll2);
    case XLL3: return reinterpret_cast<void*>(xll3);

    case XLLH0: return reinterpret_cast<void*>(xllh0);
    case XLLH1: return reinterpret_cast<void*>(xllh1);
    case XLLH2: return reinterpret_cast<void*>(xllh2);
    case XLLH3: return reinterpret_cast<void*>(xllh3);

    case XLLL0: return reinterpret_cast<void*>(xlll0);
    case XLLL1: return reinterpret_cast<void*>(xlll1);
    case XLLL2: return reinterpret_cast<void*>(xlll2);
    case XLLL3: return reinterpret_cast<void*>(xlll3);

    case XBP: return reinterpret_cast<void*>(xbp);
    case XSP: return reinterpret_cast<void*>(xsp);
    case XIP: return reinterpret_cast<void*>(xip);
    case XGDP: return reinterpret_cast<void*>(xgdp);
    case XIDP: return reinterpret_cast<void*>(xidp);
    default: throw std::runtime_error("Invalid register");
  }
}

std::pair<void*, void*> hypercpu::cpu::get_operands(operand_types op_types, mode md, std::size_t& op1, std::size_t& op2) {
  switch (op_types) {
    case R_R:
    case R_RM:
    case RM_R: {
      void *op_1, *op_2;
      op_1 = get_register(op1);
      op_2 = get_register(op2);
      std::cout << "op_1: " << op_1 << '\n';
      std::cout << "op_2: " << op_2 << '\n';
      return std::make_pair(op_1, op_2);
    }
    
    case RM_M:
    case R_M:
      return std::make_pair(get_register(op1), reinterpret_cast<void*>(op2));

    case RM_IMM:
    case R_IMM:{
      switch (md) {
        case b8:{
          void* imm8;
          std::memcpy(&imm8, &op2, sizeof(std::uint8_t));
          return std::make_pair(get_register(op1), imm8);
        }
        case b16:{
          void* imm16;
          std::memcpy(&imm16, &op2, sizeof(std::uint16_t));
          return std::make_pair(get_register(op1), imm16);
        }
        case b32:{
          void* imm32;
          std::memcpy(&imm32, &op2, sizeof(std::uint32_t));
          return std::make_pair(get_register(op1), imm32);
        }
        case b64:{
          void* imm64;
          std::memcpy(&imm64, &op2, sizeof(std::uint64_t));
          return std::make_pair(get_register(op1), imm64);
        }
      }
    }

    case M_R:
      return std::make_pair(reinterpret_cast<void*>(op1), get_register(op2));
    
    case R:
      return std::make_pair(get_register(op1), nullptr);
    
    case M:
      return std::make_pair(reinterpret_cast<void*>(op1), nullptr);

    case NONE:
      return std::make_pair(nullptr, nullptr);
    default: exit(1);
  }
}
