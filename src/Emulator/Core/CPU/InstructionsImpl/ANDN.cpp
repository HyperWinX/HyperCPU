#include <Core/CPU/CPU.hpp>

#include <Misc/deref.hpp>
#include <Misc/bit_cast.hpp>
#include <Misc/overflow.hpp>


void HyperCPU::CPU::ExecANDN(OperandTypes op_types, Mode md, void* op1, void* op2) {
  switch (op_types) {
    case R_R: {
      switch (md) {
        case b8: {
          auto& dst = deref<std::uint8_t>(op1);
          dst = ~dst & HyperCPU::bit_cast_from<std::uint8_t>(op2);
          break;
        }
          
        case b16: {
          auto& dst = deref<std::uint16_t>(op1);
          dst = ~dst & HyperCPU::bit_cast_from<std::uint16_t>(op2);
          break;
        }

        case b32: {
          auto& dst = deref<std::uint32_t>(op1);
          dst = ~dst & HyperCPU::bit_cast_from<std::uint32_t>(op2);
          break;
        }

        case b64: {
          auto& dst = deref<std::uint64_t>(op1);
          dst = ~dst & HyperCPU::bit_cast_from<std::uint64_t>(op2);
          break;
        }
      }
      break;
    }

    case R_RM: {
      std::uint64_t ptr = HyperCPU::bit_cast_from<std::uint64_t>(op2);

      switch (md) {
        case b8: {
          std::uint8_t val = mem_controller->Read8(ptr);
          auto& dst = deref<std::uint8_t>(op1);
          dst = ~dst & val;
          break;
        }

        case b16: {
          std::uint16_t val = mem_controller->Read16(ptr);
          auto& dst = deref<std::uint16_t>(op1);
          dst = ~dst & val;
          break;
        }

        case b32: {
          std::uint32_t val = mem_controller->Read32(ptr);
          auto& dst = deref<std::uint32_t>(op1);
          dst = ~dst & val;
          break;
        }

        case b64: {
          std::uint64_t val = mem_controller->Read64(ptr);
          auto& dst = deref<std::uint64_t>(op1);
          dst = ~dst & val;
          break;
        }
      }
      break;
    }

    case R_M: {
      std::uint64_t ptr = HyperCPU::bit_cast<std::uint64_t>(op2);

      switch (md) {
        case b8: {
          std::uint8_t val = mem_controller->Read8(ptr);
          auto& dst = deref<std::uint8_t>(op1);
          dst = ~dst & val;
          break;
        }

        case b16: {
          std::uint16_t val = mem_controller->Read16(ptr);
          auto& dst = deref<std::uint16_t>(op1);
          dst = ~dst & val;
          break;
        }

        case b32: {
          std::uint32_t val = mem_controller->Read32(ptr);
          auto& dst = deref<std::uint32_t>(op1);
          dst = ~dst & val;
          break;
        }

        case b64: {
          std::uint64_t val = mem_controller->Read64(ptr);
          auto& dst = deref<std::uint64_t>(op1);
          dst = ~dst & val;
          break;
        }
      }
      break;
    }

    case R_IMM: {
      switch (md) {
        case b8: {
          std::uint8_t val = HyperCPU::bit_cast<std::uint8_t>(op2);
          auto& dst = deref<std::uint8_t>(op1);
          ovf = AdditionWillOverflow(dst, val);
          dst = ~dst & val;
          break;
        }
          
        case b16: {
          std::uint16_t val = HyperCPU::bit_cast<std::uint16_t>(op2);
          auto& dst = deref<std::uint16_t>(op1);
          ovf = AdditionWillOverflow(dst, val);
          dst = ~dst & val;
          break;
        }
        
        case b32: {
          std::uint32_t val = HyperCPU::bit_cast<std::uint32_t>(op2);
          auto& dst = deref<std::uint32_t>(op1);
          ovf = AdditionWillOverflow(dst, val);
          dst = ~dst & val;
          break;
        }
        
        case b64: {
          std::uint64_t val = HyperCPU::bit_cast<std::uint64_t>(op2);
          auto& dst = deref<std::uint64_t>(op1);
          ovf = AdditionWillOverflow(dst, val);
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
