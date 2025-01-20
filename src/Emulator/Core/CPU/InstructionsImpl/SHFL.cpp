#include <core/cpu/instructions_impl/instructions.hpp>
#include <core/cpu/cpu.hpp>

#include <misc/deref.hpp>
#include <misc/bit_cast.hpp>
#include <misc/overflow.hpp>


void hypercpu::cpu::exec_shfl(operand_types op_types, mode md, void* op1, void* op2) {
  switch (op_types) {
    case R_R: {
      switch (md) {
        case b8:
          deref<std::uint8_t>(op1) <<= hypercpu::bit_cast_from<std::uint8_t>(op2);
          break;

        case b16:
          deref<std::uint16_t>(op1) <<= hypercpu::bit_cast_from<std::uint16_t>(op2);
          break;

        case b32:
          deref<std::uint32_t>(op1) <<= hypercpu::bit_cast_from<std::uint32_t>(op2);
          break;

        case b64:
          deref<std::uint64_t>(op1) <<= hypercpu::bit_cast_from<std::uint64_t>(op2);
          break;
      }
      break;
    }

    case R_IMM: {
      switch (md) {
        case b8: {
          std::uint8_t val = hypercpu::bit_cast<std::uint8_t>(op2);
          deref<std::uint8_t>(op1) <<= val;
          break;
        }
          
        case b16: {
          std::uint16_t val = hypercpu::bit_cast<std::uint16_t>(op2);
          deref<std::uint16_t>(op1) <<= val;
          break;
        }
        
        case b32: {
          std::uint32_t val = hypercpu::bit_cast<std::uint32_t>(op2);
          deref<std::uint32_t>(op1) <<= val;
          break;
        }
        
        case b64: {
          std::uint64_t val = hypercpu::bit_cast<std::uint64_t>(op2);
          deref<std::uint64_t>(op1) <<= val;
          break;
        }
      }
      break;
    }

    default:
      break;
  }
}
