#pragma once

#include <cstddef>
#include <functional>

#include <core/memory_controller/i_memory_controller.hpp>
#include <core/cpu/interrupts/reserved_interrupts.hpp>
#include <core/cpu/instructions/flags.hpp>
#include <core/cpu/decode/decoder.hpp>


#define DECLARE_INSTR(name) void exec_##name(operand_types op_types, mode md, void* op1, void* op2)

namespace hypercpu {
  using opcode_handler = std::function<void(hypercpu::operand_types op_types, hypercpu::mode md, void* op1, void* op2)>;

  class memory_controller_st;
  class memory_controller_mt;

  class cpu {
  private:
    friend class decoder;
    friend class memory_controller_st;
    friend class memory_controller_mt;
    // Components
    i_memory_controller* mem_controller;
    decoder* m_decoder;

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

    void trigger_interrupt(hypercpu::cpu_exceptions exception);
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
    explicit cpu(std::size_t core_count, std::size_t mem_size);

    void run();
    
    ~cpu();
  };
}
