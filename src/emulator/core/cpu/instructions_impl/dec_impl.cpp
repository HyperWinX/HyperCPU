#include <core/cpu/instructions_impl/instructions.hpp>
#include <core/cpu/cpu.hpp>

#include <misc/deref.hpp>
#include <misc/bit_cast.hpp>
#include <misc/overflow.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void hypercpu::cpu::exec_dec(operand_types op_types, mode md, void* op1, void* op2) {
  switch (md) {
    case b8: {
      auto& dst = deref<std::uint8_t>(op1);
      udf = (dst == 0);
      --dst;
      break;
    }

    case b16: {
      auto& dst = deref<std::uint16_t>(op1);
      udf = (dst == 0);
      --dst;
      break;
    }

    case b32: {
      auto& dst = deref<std::uint32_t>(op1);
      udf = (dst == 0);
      --dst;
      break;
    }

    case b64: {
      auto& dst = deref<std::uint64_t>(op1);
      udf = (dst == 0);
      --dst;
      break;
    }
  }
}

#pragma GCC diagnostic pop
