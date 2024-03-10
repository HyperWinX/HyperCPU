#include <cstdint>
#include <opcodes.hpp>
#include <cpu.hpp>

HyperCPU::instr_t HyperCPU::CPU::_define_instr(uint16_t opcode){
    switch(opcode){
        case ADC: return HyperCPU::INS_ADC;
        case AND: return HyperCPU::INS_AND;
        case HLT: return HyperCPU::INS_HLT;
        default: return HyperCPU::INS_UNKNOWN;
    }
}