#include <core/cpu/instructions_impl/instructions.hpp>
#include <core/cpu/cpu.hpp>

#include <misc/deref.hpp>
#include <misc/bit_cast.hpp>
#include <misc/overflow.hpp>


void hypercpu::cpu::exec_andn(operand_types op_types, mode md, void* op1, void* op2) {
  switch (op_types) {
    case R_R: {
      switch (md) {
        case b8: {
          auto& dst = deref<std::uint8_t>(op1);
          ovf = addition_will_overflow(dst, deref<std::uint8_t>(op2));
          dst = ~dst & hypercpu::bit_cast_from<std::uint8_t>(op2);
          break;
        }
          
        case b16: {
          auto& dst = deref<std::uint16_t>(op1);
          ovf = addition_will_overflow(dst, deref<std::uint16_t>(op2));
          dst = ~dst & hypercpu::bit_cast_from<std::uint16_t>(op2);
          break;
        }

        case b32: {
          auto& dst = deref<std::uint32_t>(op1);
          ovf = addition_will_overflow(dst, deref<std::uint32_t>(op2));
          dst = ~dst & hypercpu::bit_cast_from<std::uint32_t>(op2);
          break;
        }

        case b64: {
          auto& dst = deref<std::uint64_t>(op1);
          ovf = addition_will_overflow(dst, deref<std::uint64_t>(op2));
          dst = ~dst & hypercpu::bit_cast_from<std::uint64_t>(op2);
          break;
        }
      }
      break;
    }

    case R_RM: {
      std::uint64_t ptr = hypercpu::bit_cast_from<std::uint64_t>(op2);

      switch (md) {
        case b8: {
          std::uint8_t val = mem_controller->read8(ptr);
          auto& dst = deref<std::uint8_t>(op1);
          ovf = addition_will_overflow(dst, val);
          dst = ~dst & val;
          break;
        }

        case b16: {
          std::uint16_t val = mem_controller->read16(ptr);
          auto& dst = deref<std::uint16_t>(op1);
          ovf = addition_will_overflow(dst, val);
          dst = ~dst & val;
          break;
        }

        case b32: {
          std::uint32_t val = mem_controller->read32(ptr);
          auto& dst = deref<std::uint32_t>(op1);
          ovf = addition_will_overflow(dst, val);
          dst = ~dst & val;
          break;
        }

        case b64: {
          std::uint64_t val = mem_controller->read64(ptr);
          auto& dst = deref<std::uint64_t>(op1);
          ovf = addition_will_overflow(dst, val);
          dst = ~dst & val;
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
          auto& dst = deref<std::uint8_t>(op1);
          ovf = addition_will_overflow(dst, val);
          dst = ~dst & val;
          break;
        }

        case b16: {
          std::uint16_t val = mem_controller->read16(ptr);
          auto& dst = deref<std::uint16_t>(op1);
          ovf = addition_will_overflow(dst, val);
          dst = ~dst & val;
          break;
        }

        case b32: {
          std::uint32_t val = mem_controller->read32(ptr);
          auto& dst = deref<std::uint32_t>(op1);
          ovf = addition_will_overflow(dst, val);
          dst = ~dst & val;
          break;
        }

        case b64: {
          std::uint64_t val = mem_controller->read64(ptr);
          auto& dst = deref<std::uint64_t>(op1);
          ovf = addition_will_overflow(dst, val);
          dst = ~dst & val;
          break;
        }
      }
      break;
    }

    case R_IMM: {
      switch (md) {
        case b8: {
          std::uint8_t val = hypercpu::bit_cast<std::uint8_t>(op2);
          auto& dst = deref<std::uint8_t>(op1);
          ovf = addition_will_overflow(dst, val);
          dst = ~dst & val;
          break;
        }
          
        case b16: {
          std::uint16_t val = hypercpu::bit_cast<std::uint16_t>(op2);
          auto& dst = deref<std::uint16_t>(op1);
          ovf = addition_will_overflow(dst, val);
          dst = ~dst & val;
          break;
        }
        
        case b32: {
          std::uint32_t val = hypercpu::bit_cast<std::uint32_t>(op2);
          auto& dst = deref<std::uint32_t>(op1);
          ovf = addition_will_overflow(dst, val);
          dst = ~dst & val;
          break;
        }
        
        case b64: {
          std::uint64_t val = hypercpu::bit_cast<std::uint64_t>(op2);
          auto& dst = deref<std::uint64_t>(op1);
          ovf = addition_will_overflow(dst, val);
          dst = ~dst & val;
          break;
        }
      }
      break;
    }

    default:
      break;
  }
}
