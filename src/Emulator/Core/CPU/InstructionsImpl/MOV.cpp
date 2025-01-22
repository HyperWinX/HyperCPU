#include <Core/CPU/CPU.hpp>

#include <Misc/bit_cast.hpp>


void HyperCPU::CPU::ExecMOV(OperandTypes op_types, Mode md, void* op1, void* op2) {
  switch (op_types) {
    case R_R: {
      switch (md) {
        case b8:
          std::memcpy(op1, op2, 1);
          break;

        case b16:
          std::memcpy(op1, op2, 2);
          break;

        case b32:
          std::memcpy(op1, op2, 4);
          break;

        case b64:
          std::memcpy(op1, op2, 8);
          break;
      }
      break;
    }

    case R_RM: {
      std::uint64_t ptr;
      std::memcpy(&ptr, op2, 8);

      switch (md) {
        case b8:
          *static_cast<std::uint8_t*>(op1) = mem_controller->Read8(ptr);
          break;

        case b16:
          *static_cast<std::uint16_t*>(op1) = mem_controller->Read16(ptr);
          break;

        case b32:
          *static_cast<std::uint32_t*>(op1) = mem_controller->Read32(ptr);
          break;

        case b64:
          *static_cast<std::uint64_t*>(op1) = mem_controller->Read64(ptr);
          break;
      }
      break;
    }

    case R_M: {
      std::uint64_t ptr = reinterpret_cast<std::uint64_t>(op2);

      switch (md) {
        case b8:
          *static_cast<std::uint8_t*>(op1) = mem_controller->Read8(ptr);
          break;

        case b16:
          *static_cast<std::uint16_t*>(op1) = mem_controller->Read16(ptr);
          break;
        
        case b32:
          *static_cast<std::uint32_t*>(op1) = mem_controller->Read32(ptr);
          break;
        
        case b64:
          *static_cast<std::uint64_t*>(op1) = mem_controller->Read64(ptr);
          break;
      }
      break;
    }

    case R_IMM: {
      switch (md) {
        case b8:
          std::memcpy(op1, &op2, 1);
          break;
          
        case b16:
          std::memcpy(op1, &op2, 2);
          break;
        
        case b32:
          std::memcpy(op1, &op2, 4);
          break;
        
        case b64:
          std::memcpy(op1, &op2, 8);
          break;
      }
      break;
    }

    case RM_M: {
      std::size_t ptr1, ptr2 = 0;
      std::memcpy(&ptr1, op1, 8);
      ptr2 = reinterpret_cast<std::size_t>(op2);

      switch (md) {
        case b8: 
          mem_controller->Load8(ptr1, mem_controller->Read8(ptr2));
          break;
        
        case b16:
          mem_controller->Load16(ptr1, mem_controller->Read16(ptr2));
          break;

        case b32:
          mem_controller->Load32(ptr1, mem_controller->Read32(ptr2));
          break;
        
        case b64:
          mem_controller->Load64(ptr1, mem_controller->Read64(ptr2));
          break;
      }
      break;
    }

    case RM_R: {
      std::size_t ptr = HyperCPU::bit_cast_from<std::size_t>(op1);

      switch (md) {
        case b8: {
          mem_controller->Load8(ptr, *static_cast<std::uint8_t*>(op2));
          break;
        }

        case b16: {
          mem_controller->Load16(ptr, *static_cast<std::uint16_t*>(op2));
          break;
        }

        case b32: {
          mem_controller->Load32(ptr, *static_cast<std::uint32_t*>(op2));
          break;
        }

        case b64: {
          mem_controller->Load64(ptr, *static_cast<std::uint64_t*>(op2));
          break;
        }
      }
      break;
    }

    case RM_IMM: {
      std::size_t ptr1 = HyperCPU::bit_cast_from<std::size_t>(op1);

      switch (md) {
        case b8:
          mem_controller->Load8(ptr1, HyperCPU::bit_cast<std::uint8_t>(op2));
          break;
          
        case b16:
          mem_controller->Load16(ptr1, HyperCPU::bit_cast<std::uint16_t>(op2));
          break;
        
        case b32:
          mem_controller->Load32(ptr1, HyperCPU::bit_cast<std::uint32_t>(op2));
          break;
        
        case b64:
          mem_controller->Load64(ptr1, HyperCPU::bit_cast<std::uint64_t>(op2));
          break;
      }
      break;
    }

    case M_R: {
      std::size_t ptr1 = HyperCPU::bit_cast<std::size_t>(op1);

      switch (md) {
        case b8: {
          mem_controller->Load8(ptr1, HyperCPU::bit_cast_from<std::uint8_t>(op2));
          break;
        }

        case b16: {
          mem_controller->Load16(ptr1, HyperCPU::bit_cast_from<std::uint16_t>(op2));
          break;
        }

        case b32: {
          mem_controller->Load32(ptr1, HyperCPU::bit_cast_from<std::uint32_t>(op2));
          break;
        }

        case b64: {
          mem_controller->Load64(ptr1, HyperCPU::bit_cast_from<std::uint64_t>(op2));
          break;
        }
      }
      break;
    }

    default:
      break;
  }
}
