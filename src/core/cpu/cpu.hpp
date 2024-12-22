#pragma once

#include <cstddef>
#include <functional>

#include <core/memory_controller/memory_controller_st.hpp>
#include <core/memory_controller/memory_controller_mt.hpp>
#include <core/memory_controller/i_memory_controller.hpp>
#include <core/cpu/instructions/flags.hpp>
#include <core/cpu/decode/i_decoder.hpp>
#include <core/cpu/decode/decoder.hpp>


#define DECLARE_INSTR(name) void exec_##name(operand_types op_types, mode md, void* op1, void* op2)

namespace hypercpu {
  using opcode_handler = std::function<void(hypercpu::operand_types op_types, hypercpu::mode md, void* op1, void* op2)>;

  class cpu {
  private:
    // Components
    i_memory_controller* mem_controller;
    i_decoder* m_decoder;

    // Data
    std::size_t core_count;
    std::size_t total_mem;
    bool halted;

    // General space for registers
    std::uint64_t data[13];

    // GP Registers
    std::uint64_t *x0, *x1, *x2, *x3, *x4, *x5, *x6, *x7;
    std::uint32_t *xh0, *xh1, *xh2, *xh3, *xh4, *xh5, *xh6, *xh7;
    std::uint32_t *xl0, *xl1,* xl2, *xl3, *xl4, *xl5, *xl6, *xl7;
    std::uint16_t *xll0, *xll1, *xll2, *xll3;
    std::uint8_t *xllh0, *xllh1, *xllh2, *xllh3;
    std::uint8_t *xlll0, *xlll1, *xlll2, *xlll3;

    // Specific registers
    std::uint64_t *xbp, *xsp, *xip, *xgdp, *xivt;

    // Flags
    bool crf, ovf, udf;

    std::array<opcode_handler, 128> opcode_handler_assoc;

    std::pair<void*, void*> get_operands(operand_types op_types, mode md, std::size_t& op1, std::size_t& op2);
    void* get_register(std::size_t& op1);

    void stack_push8(std::uint8_t) noexcept;
    void stack_push16(std::uint16_t) noexcept;
    void stack_push32(std::uint32_t) noexcept;
    void stack_push64(std::uint64_t) noexcept;

    std::uint8_t stack_pop8() noexcept;
    std::uint16_t stack_pop16() noexcept;
    std::uint32_t stack_pop32() noexcept;
    std::uint64_t stack_pop64() noexcept;

    void trigger_interrupt(std::uint8_t num);
    void run_interrupt_subroutine();
    
    DECLARE_INSTR(add);
    DECLARE_INSTR(adc);
    DECLARE_INSTR(and);
    DECLARE_INSTR(andn);
    DECLARE_INSTR(bswap);
    DECLARE_INSTR(call);
    DECLARE_INSTR(ccrf);
    DECLARE_INSTR(covf);
    DECLARE_INSTR(cudf);
    DECLARE_INSTR(inc);
    DECLARE_INSTR(dec);
    DECLARE_INSTR(hid);
    DECLARE_INSTR(mul);
    DECLARE_INSTR(or);
    DECLARE_INSTR(sub);
    DECLARE_INSTR(shfl);
    DECLARE_INSTR(shfr);
    DECLARE_INSTR(div);
    DECLARE_INSTR(halt);
    DECLARE_INSTR(mov);
    DECLARE_INSTR(loivt);
    DECLARE_INSTR(intr);
    
  public:
    explicit inline cpu(std::size_t core_count, std::size_t mem_size) :
      mem_controller(core_count == 1 ?
        dynamic_cast<i_memory_controller*>(new memory_controller_st(mem_size)) : 
        dynamic_cast<i_memory_controller*>(new memory_controller_mt(mem_size))),
      core_count(core_count),
      total_mem(mem_size),
      halted(false) {
        // Initializing all register pointers
        std::memset(&data, 0, sizeof(data));
        x0 = &data[0];
        x1 = &data[1];
        x2 = &data[2];
        x3 = &data[3];
        x4 = &data[4];
        x5 = &data[5];
        x6 = &data[6];
        x7 = &data[7];

        xl0 = reinterpret_cast<std::uint32_t*>(&data[0]);
        xl1 = reinterpret_cast<std::uint32_t*>(&data[1]);
        xl2 = reinterpret_cast<std::uint32_t*>(&data[2]);
        xl3 = reinterpret_cast<std::uint32_t*>(&data[3]);
        xl4 = reinterpret_cast<std::uint32_t*>(&data[4]);
        xl5 = reinterpret_cast<std::uint32_t*>(&data[5]);
        xl6 = reinterpret_cast<std::uint32_t*>(&data[6]);
        xl7 = reinterpret_cast<std::uint32_t*>(&data[7]);

        xh0 = reinterpret_cast<std::uint32_t*>(&data[0]) + 1;
        xh1 = reinterpret_cast<std::uint32_t*>(&data[1]) + 1;
        xh2 = reinterpret_cast<std::uint32_t*>(&data[2]) + 1;
        xh3 = reinterpret_cast<std::uint32_t*>(&data[3]) + 1;
        xh4 = reinterpret_cast<std::uint32_t*>(&data[4]) + 1;
        xh5 = reinterpret_cast<std::uint32_t*>(&data[5]) + 1;
        xh6 = reinterpret_cast<std::uint32_t*>(&data[6]) + 1;
        xh7 = reinterpret_cast<std::uint32_t*>(&data[7]) + 1;

        xll0 = reinterpret_cast<std::uint16_t*>(&data[0]);
        xll1 = reinterpret_cast<std::uint16_t*>(&data[1]);
        xll2 = reinterpret_cast<std::uint16_t*>(&data[2]);
        xll3 = reinterpret_cast<std::uint16_t*>(&data[3]);

        xllh0 = reinterpret_cast<std::uint8_t*>(&data[0]) + 1;
        xllh1 = reinterpret_cast<std::uint8_t*>(&data[1]) + 1;
        xllh2 = reinterpret_cast<std::uint8_t*>(&data[2]) + 1;
        xllh3 = reinterpret_cast<std::uint8_t*>(&data[3]) + 1;

        xlll0 = reinterpret_cast<std::uint8_t*>(&data[0]);
        xlll1 = reinterpret_cast<std::uint8_t*>(&data[1]);
        xlll2 = reinterpret_cast<std::uint8_t*>(&data[2]);
        xlll3 = reinterpret_cast<std::uint8_t*>(&data[3]);

        xbp = &data[8];
        xsp = &data[9];
        xip = &data[10];
        xgdp = &data[11];
        xivt = &data[12];
        
        opcode_handler_assoc[static_cast<std::uint16_t>(hypercpu::opcode::HALT)] =
          [this](operand_types op_types, mode md, void* op1, void* op2) -> void { this->exec_halt(op_types, md, op1, op2); };
        opcode_handler_assoc[static_cast<std::uint16_t>(hypercpu::opcode::ADD)] = 
          [this](operand_types op_types, mode md, void* op1, void* op2) -> void { this->exec_add(op_types, md, op1, op2); };
        opcode_handler_assoc[static_cast<std::uint16_t>(hypercpu::opcode::ADC)] = 
          [this](operand_types op_types, mode md, void* op1, void* op2) -> void { this->exec_adc(op_types, md, op1, op2); };
        opcode_handler_assoc[static_cast<std::uint16_t>(hypercpu::opcode::AND)] = 
          [this](operand_types op_types, mode md, void* op1, void* op2) -> void { this->exec_and(op_types, md, op1, op2); };
        opcode_handler_assoc[static_cast<std::uint16_t>(hypercpu::opcode::ANDN)] = 
          [this](operand_types op_types, mode md, void* op1, void* op2) -> void { this->exec_andn(op_types, md, op1, op2); };
        opcode_handler_assoc[static_cast<std::uint16_t>(hypercpu::opcode::BSWAP)] = 
          [this](operand_types op_types, mode md, void* op1, void* op2) -> void { this->exec_bswap(op_types, md, op1, op2); };
        opcode_handler_assoc[static_cast<std::uint16_t>(hypercpu::opcode::CALL)] = 
          [this](operand_types op_types, mode md, void* op1, void* op2) -> void { this->exec_call(op_types, md, op1, op2); };
        opcode_handler_assoc[static_cast<std::uint16_t>(hypercpu::opcode::CCRF)] = 
          [this](operand_types op_types, mode md, void* op1, void* op2) -> void { this->exec_ccrf(op_types, md, op1, op2); };
        opcode_handler_assoc[static_cast<std::uint16_t>(hypercpu::opcode::COVF)] = 
          [this](operand_types op_types, mode md, void* op1, void* op2) -> void { this->exec_covf(op_types, md, op1, op2); };
        opcode_handler_assoc[static_cast<std::uint16_t>(hypercpu::opcode::CUDF)] = 
          [this](operand_types op_types, mode md, void* op1, void* op2) -> void { this->exec_cudf(op_types, md, op1, op2); };
        opcode_handler_assoc[static_cast<std::uint16_t>(hypercpu::opcode::INC)] = 
          [this](operand_types op_types, mode md, void* op1, void* op2) -> void { this->exec_inc(op_types, md, op1, op2); };
        opcode_handler_assoc[static_cast<std::uint16_t>(hypercpu::opcode::DEC)] = 
          [this](operand_types op_types, mode md, void* op1, void* op2) -> void { this->exec_dec(op_types, md, op1, op2); };
        opcode_handler_assoc[static_cast<std::uint16_t>(hypercpu::opcode::HID)] = 
          [this](operand_types op_types, mode md, void* op1, void* op2) -> void { this->exec_hid(op_types, md, op1, op2); };
        opcode_handler_assoc[static_cast<std::uint16_t>(hypercpu::opcode::MUL)] = 
          [this](operand_types op_types, mode md, void* op1, void* op2) -> void { this->exec_mul(op_types, md, op1, op2); };
        opcode_handler_assoc[static_cast<std::uint16_t>(hypercpu::opcode::OR)] = 
          [this](operand_types op_types, mode md, void* op1, void* op2) -> void { this->exec_or(op_types, md, op1, op2); };
        opcode_handler_assoc[static_cast<std::uint16_t>(hypercpu::opcode::SUB)] = 
          [this](operand_types op_types, mode md, void* op1, void* op2) -> void { this->exec_sub(op_types, md, op1, op2); };
        opcode_handler_assoc[static_cast<std::uint16_t>(hypercpu::opcode::SHFL)] = 
          [this](operand_types op_types, mode md, void* op1, void* op2) -> void { this->exec_shfl(op_types, md, op1, op2); };
        opcode_handler_assoc[static_cast<std::uint16_t>(hypercpu::opcode::SHFR)] = 
          [this](operand_types op_types, mode md, void* op1, void* op2) -> void { this->exec_shfr(op_types, md, op1, op2); };
        opcode_handler_assoc[static_cast<std::uint16_t>(hypercpu::opcode::DIV)] = 
          [this](operand_types op_types, mode md, void* op1, void* op2) -> void { this->exec_div(op_types, md, op1, op2); };
        opcode_handler_assoc[static_cast<std::uint16_t>(hypercpu::opcode::LOIVT)] = 
          [this](operand_types op_types, mode md, void* op1, void* op2) -> void { this->exec_loivt(op_types, md, op1, op2); };
        opcode_handler_assoc[static_cast<std::uint16_t>(hypercpu::opcode::INTR)] = 
          [this](operand_types op_types, mode md, void* op1, void* op2) -> void { this->exec_intr(op_types, md, op1, op2); };
        opcode_handler_assoc[static_cast<std::uint16_t>(hypercpu::opcode::MOV)] = 
          [this](operand_types op_types, mode md, void* op1, void* op2) -> void { this->exec_mov(op_types, md, op1, op2); };
        
        m_decoder = dynamic_cast<i_decoder*>(new decoder(mem_controller, xip));
      }

    void run();

    ~cpu() {
      delete mem_controller;
      delete m_decoder;
    }
  };
}
