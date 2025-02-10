#include <functional>
#include <fstream>

#include <Core/MemoryController/MemoryControllerMT.hpp>
#include <Core/MemoryController/MemoryControllerST.hpp>
#include <Core/CPU/Decoders/IDecoder.hpp>
#include <Core/CPU/Decoders/StdDecoder.hpp>
#include <Core/CPU/CPU.hpp>

HyperCPU::CPU::CPU(std::size_t core_count, std::size_t mem_size, char* binary, std::uint64_t binary_size) :
  mem_controller(core_count == 1 ?
    dynamic_cast<IMemoryController*>(new MemoryControllerST(mem_size, this)) : 
    dynamic_cast<IMemoryController*>(new MemoryControllerMT(mem_size, this))),
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
    
    opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::HALT)] =
      [this](const IInstruction& instr, void* op1, void* op2) -> void { this->ExecHALT(instr, op1, op2); };
    opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::ADD)] = 
      [this](const IInstruction& instr, void* op1, void* op2) -> void { this->ExecADD(instr, op1, op2); };
    opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::ADC)] = 
      [this](const IInstruction& instr, void* op1, void* op2) -> void { this->ExecADC(instr, op1, op2); };
    opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::AND)] = 
      [this](const IInstruction& instr, void* op1, void* op2) -> void { this->ExecAND(instr, op1, op2); };
    opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::ANDN)] = 
      [this](const IInstruction& instr, void* op1, void* op2) -> void { this->ExecANDN(instr, op1, op2); };
    opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::BSWAP)] = 
      [this](const IInstruction& instr, void* op1, void* op2) -> void { this->ExecBSWAP(instr, op1, op2); };
    opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::CALL)] = 
      [this](const IInstruction& instr, void* op1, void* op2) -> void { this->ExecCALL(instr, op1, op2); };
    opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::CCRF)] = 
      [this](const IInstruction& instr, void* op1, void* op2) -> void { this->ExecCCRF(instr, op1, op2); };
    opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::COVF)] = 
      [this](const IInstruction& instr, void* op1, void* op2) -> void { this->ExecCOVF(instr, op1, op2); };
    opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::CUDF)] = 
      [this](const IInstruction& instr, void* op1, void* op2) -> void { this->ExecCUDF(instr, op1, op2); };
    opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::INC)] = 
      [this](const IInstruction& instr, void* op1, void* op2) -> void { this->ExecINC(instr, op1, op2); };
    opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::DEC)] = 
      [this](const IInstruction& instr, void* op1, void* op2) -> void { this->ExecDEC(instr, op1, op2); };
    opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::HID)] = 
      [this](const IInstruction& instr, void* op1, void* op2) -> void { this->ExecHID(instr, op1, op2); };
    opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::MUL)] = 
      [this](const IInstruction& instr, void* op1, void* op2) -> void { this->ExecMUL(instr, op1, op2); };
    opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::OR)] = 
      [this](const IInstruction& instr, void* op1, void* op2) -> void { this->ExecOR(instr, op1, op2); };
    opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::SUB)] = 
      [this](const IInstruction& instr, void* op1, void* op2) -> void { this->ExecSUB(instr, op1, op2); };
    opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::SHFL)] = 
      [this](const IInstruction& instr, void* op1, void* op2) -> void { this->ExecSHFL(instr, op1, op2); };
    opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::SHFR)] = 
      [this](const IInstruction& instr, void* op1, void* op2) -> void { this->ExecSHFR(instr, op1, op2); };
    opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::DIV)] = 
      [this](const IInstruction& instr, void* op1, void* op2) -> void { this->ExecDIV(instr, op1, op2); };
    opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::LOIVT)] = 
      [this](const IInstruction& instr, void* op1, void* op2) -> void { this->ExecLOIVT(instr, op1, op2); };
    opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::INTR)] = 
      [this](const IInstruction& instr, void* op1, void* op2) -> void { this->ExecINTR(instr, op1, op2); };
    opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::MOV)] = 
      [this](const IInstruction& instr, void* op1, void* op2) -> void { this->ExecMOV(instr, op1, op2); };
    opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::READ)] = 
      [this](const IInstruction& instr, void* op1, void* op2) -> void { this->ExecREAD(instr, op1, op2); };
    opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::WRITE)] = 
      [this](const IInstruction& instr, void* op1, void* op2) -> void { this->ExecWRITE(instr, op1, op2); };

    read_io_handlers[0] = std::bind(&CPU::read_console, this);

    write_io_handlers[0] = std::bind(&CPU::write_console, this, std::placeholders::_1);
    
    m_decoder = std::make_unique<Decoder>(mem_controller, xip, this);
    if (binary) {
      std::memcpy(mem_controller->get_ptr(), binary, binary_size);
    }
  }

HyperCPU::CPU::~CPU() {
  delete mem_controller;
}

void HyperCPU::CPU::Run() {
  while (1) {
    if (halted) return;
    
    HyperCPU::IInstruction instr = m_decoder->FetchAndDecode();
    if (m_decoder->IsHalted()) {
      halted = true;
      continue;
    }
    std::pair<void*, void*> operands = GetOperands(instr.m_op_types, instr.m_opcode_mode, instr.m_op1, instr.m_op2);
    opcode_handler_assoc[static_cast<std::uint16_t>(instr.m_opcode)](instr, operands.first, operands.second);
  }
}

std::uint8_t HyperCPU::CPU::read_console() {
  return std::getchar();
}

void HyperCPU::CPU::write_console(std::uint8_t ch) {
  std::putchar(ch);
}
