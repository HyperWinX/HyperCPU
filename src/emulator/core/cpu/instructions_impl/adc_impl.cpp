#include <cstdint>

#include <core/cpu/instructions_impl/instructions.hpp>
#include <core/cpu/cpu.hpp>

#include <misc/deref.hpp>
#include <misc/bit_cast.hpp>
#include <misc/overflow.hpp>


void hypercpu::cpu::exec_adc(operand_types op_types, mode md, void* op1, void* op2) {
  switch (op_types) {
    case R_R: {
      switch (md) {
        case b8:
          ovf = addition_will_overflow(deref<std::uint8_t>(op1), deref<std::uint8_t>(op2));
          deref<std::uint8_t>(op1) += hypercpu::bit_cast_from<std::uint8_t>(op2);
          if (crf) ++deref<std::uint8_t>(op1);
          break;

        case b16:
          ovf = addition_will_overflow(deref<std::uint16_t>(op1), deref<std::uint16_t>(op2));
          deref<std::uint16_t>(op1) += hypercpu::bit_cast_from<std::uint16_t>(op2);
          if (crf) ++deref<std::uint16_t>(op1);
          break;

        case b32:
          ovf = addition_will_overflow(deref<std::uint32_t>(op1), deref<std::uint32_t>(op2));
          deref<std::uint32_t>(op1) += hypercpu::bit_cast_from<std::uint32_t>(op2);
          if (crf) ++deref<std::uint32_t>(op1);
          break;

        case b64:
          ovf = addition_will_overflow(deref<std::uint64_t>(op1), deref<std::uint64_t>(op2));
          deref<std::uint64_t>(op1) += hypercpu::bit_cast_from<std::uint64_t>(op2);
          if (crf) ++deref<std::uint64_t>(op1);
          break;
      }
      break;
    }

    case R_RM: {
      std::uint64_t ptr = hypercpu::bit_cast_from<std::uint64_t>(op2);

      switch (md) {
        case b8: {
          std::uint8_t val = mem_controller->read8(ptr);
          ovf = addition_will_overflow(deref<std::uint8_t>(op1), val);
          deref<std::uint8_t>(op1) += val;
          if (crf) ++deref<std::uint8_t>(op1);
          break;
        }

        case b16: {
          std::uint16_t val = mem_controller->read16(ptr);
          ovf = addition_will_overflow(deref<std::uint16_t>(op1), val);
          deref<std::uint16_t>(op1) += val;
          if (crf) ++deref<std::uint16_t>(op1);
          break;
        }

        case b32: {
          std::uint32_t val = mem_controller->read32(ptr);
          ovf = addition_will_overflow(deref<std::uint32_t>(op1), val);
          deref<std::uint32_t>(op1) += val;
          if (crf) ++deref<std::uint32_t>(op1);
          break;
        }

        case b64: {
          std::uint64_t val = mem_controller->read64(ptr);
          ovf = addition_will_overflow(deref<std::uint64_t>(op1), val);
          deref<std::uint64_t>(op1) += val;
          if (crf) ++deref<std::uint64_t>(op1);
          break;
        }
      }
      break;
    }

    case R_M: {
      std::uint64_t ptr = hypercpu::bit_cast<std::uint64_t>(op2);

      switch (md) {
        case b8: {
          std::uint8_t val = mem_controller->read8(ptr);
          ovf = addition_will_overflow(deref<std::uint8_t>(op1), val);
          deref<std::uint8_t>(op1) += val;
          if (crf) ++deref<std::uint8_t>(op1);
          break;
        }

        case b16: {
          std::uint16_t val = mem_controller->read16(ptr);
          ovf = addition_will_overflow(deref<std::uint16_t>(op1), val);
          deref<std::uint16_t>(op1) += val;
          if (crf) ++deref<std::uint16_t>(op1);
          break;
        }

        case b32: {
          std::uint32_t val = mem_controller->read32(ptr);
          ovf = addition_will_overflow(deref<std::uint32_t>(op1), val);
          deref<std::uint32_t>(op1) += val;
          if (crf) ++deref<std::uint32_t>(op1);
          break;
        }

        case b64: {
          std::uint64_t val = mem_controller->read64(ptr);
          ovf = addition_will_overflow(deref<std::uint64_t>(op1), val);
          deref<std::uint64_t>(op1) += val;
          if (crf) ++deref<std::uint64_t>(op1);
          break;
        }
      }
      break;
    }

    case R_IMM: {
      switch (md) {
        case b8: {
          std::uint8_t val = hypercpu::bit_cast<std::uint8_t>(op2);
          ovf = addition_will_overflow(deref<std::uint8_t>(op1), val);
          deref<std::uint8_t>(op1) += val;
          if (crf) ++deref<std::uint8_t>(op1);
          break;
        }
          
        case b16: {
          std::uint16_t val = hypercpu::bit_cast<std::uint16_t>(op2);
          ovf = addition_will_overflow(deref<std::uint16_t>(op1), val);
          deref<std::uint16_t>(op1) += val;
          if (crf) ++deref<std::uint16_t>(op1);
          break;
        }
        
        case b32: {
          std::uint32_t val = hypercpu::bit_cast<std::uint32_t>(op2);
          ovf = addition_will_overflow(deref<std::uint32_t>(op1), val);
          deref<std::uint32_t>(op1) += val;
          if (crf) ++deref<std::uint32_t>(op1);
          break;
        }
        
        case b64: {
          std::uint64_t val = hypercpu::bit_cast<std::uint64_t>(op2);
          ovf = addition_will_overflow(deref<std::uint64_t>(op1), val);
          deref<std::uint64_t>(op1) += val;
          if (crf) ++deref<std::uint64_t>(op1);
          break;
        }
      }
      break;
    }

    default:
      break;
  }
}
