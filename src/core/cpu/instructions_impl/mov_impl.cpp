#include <core/cpu/instructions_impl/instructions.hpp>
#include <core/cpu/cpu.hpp>

void hypercpu::cpu::exec_mov(operand_types op_types, mode md, void* op1, void* op2) {
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
          *static_cast<std::uint8_t*>(op1) = mem_controller->read8(ptr);
          break;

        case b16:
          *static_cast<std::uint16_t*>(op1) = mem_controller->read16(ptr);
          break;

        case b32:
          *static_cast<std::uint32_t*>(op1) = mem_controller->read32(ptr);
          break;

        case b64:
          *static_cast<std::uint64_t*>(op1) = mem_controller->read64(ptr);
          break;
      }
      break;
    }

    case R_M: {
      std::uint64_t ptr = reinterpret_cast<std::uint64_t>(op2);

      switch (md) {
        case b8:
          *static_cast<std::uint8_t*>(op1) = mem_controller->read8(ptr);
          break;

        case b16:
          *static_cast<std::uint16_t*>(op1) = mem_controller->read16(ptr);
          break;
        
        case b32:
          *static_cast<std::uint32_t*>(op1) = mem_controller->read32(ptr);
          break;
        
        case b64:
          *static_cast<std::uint64_t*>(op1) = mem_controller->read64(ptr);
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
      std::size_t ptr1, ptr2;
      std::memcpy(&ptr1, op1, 8);
      ptr2 = reinterpret_cast<std::size_t>(op2);

      switch (md) {
        case b8: 
          mem_controller->load8(ptr1, mem_controller->read8(ptr2));
          break;
        
        case b16:
          mem_controller->load16(ptr1, mem_controller->read16(ptr2));
          break;

        case b32:
          mem_controller->load32(ptr1, mem_controller->read32(ptr2));
          break;
        
        case b64:
          mem_controller->load64(ptr1, mem_controller->read64(ptr2));
          break;
      }
      break;
    }

    case RM_R: {
      std::size_t ptr1;
      std::memcpy(&ptr1, op1, 8);

      switch (md) {
        case b8: {
          std::uint8_t val;
          std::memcpy(&val, op2, 1);
          mem_controller->load8(ptr1, val);
          break;
        }

        case b16: {
          std::uint16_t val;
          std::memcpy(&val, op2, 2);
          mem_controller->load16(ptr1, val);
          break;
        }

        case b32: {
          std::uint32_t val;
          std::memcpy(&val, op2, 4);
          mem_controller->load32(ptr1, val);
          break;
        }

        case b64: {
          std::uint64_t val;
          std::memcpy(&val, op2, 8);
          mem_controller->load64(ptr1, val);
          break;
        }
      }
      break;
    }

    case RM_IMM: {
      std::size_t ptr1;
      std::memcpy(&ptr1, op1, 8);

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
    }

    case M_R: {
      std::size_t ptr1 = reinterpret_cast<std::size_t>(op1);

      switch (md) {
        case b8: {
          std::uint8_t val;
          std::memcpy(&val, op2, 1);
          mem_controller->load8(ptr1, val);
          break;
        }

        case b16: {
          std::uint16_t val;
          std::memcpy(&val, op2, 2);
          mem_controller->load16(ptr1, val);
          break;
        }

        case b32: {
          std::uint32_t val;
          std::memcpy(&val, op2, 4);
          mem_controller->load32(ptr1, val);
          break;
        }

        case b64: {
          std::uint64_t val;
          std::memcpy(&val, op2, 8);
          mem_controller->load64(ptr1, val);
          break;
        }
      }
      break;
    }
  }
}