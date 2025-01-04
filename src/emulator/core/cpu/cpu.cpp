#include <functional>

#include <core/memory_controller/memory_controller_mt.hpp>
#include <core/memory_controller/memory_controller_st.hpp>
#include <core/cpu/instructions_impl/instructions.hpp>
#include <core/cpu/decode/i_decoder.hpp>
#include <core/cpu/decode/decoder.hpp>
#include <core/cpu/cpu.hpp>

hypercpu::cpu::cpu(std::size_t core_count, std::size_t mem_size) :
  mem_controller(core_count == 1 ?
    dynamic_cast<i_memory_controller*>(new memory_controller_st(mem_size, this)) : 
    dynamic_cast<i_memory_controller*>(new memory_controller_mt(mem_size, this))),
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
    
    m_decoder = new decoder(mem_controller, xip, this);
  }

hypercpu::cpu::~cpu() {
  delete m_decoder;
  delete mem_controller;
}

void hypercpu::cpu::run() {
  while (1) {
    if (halted) return;
    
    hypercpu::i_instruction instr = m_decoder->fetch_and_decode();
    if (m_decoder->is_halted()) continue;
    std::pair<void*, void*> operands = get_operands(instr.m_op_types, instr.m_opcode_mode, instr.m_op1, instr.m_op2);
    opcode_handler_assoc[static_cast<std::uint16_t>(instr.m_opcode)](instr.m_op_types, instr.m_opcode_mode, operands.first, operands.second);
  }
}