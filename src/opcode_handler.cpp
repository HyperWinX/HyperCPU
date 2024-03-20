#include <cstdint>
#include <cstdio>
#include <opcodes.hpp>
#include <cpu.hpp>

HyperCPU::instr_t HyperCPU::CPU::_define_instr(uint16_t opcode){
    switch(opcode){
        case ADC: return HyperCPU::INS_ADC;
        case ADD: return HyperCPU::INS_ADD;
        case AND: return HyperCPU::INS_AND;
        case ANDN: return HyperCPU::INS_ANDN;
        case HLT: return HyperCPU::INS_HLT;
        default: return HyperCPU::INS_UNKNOWN;
    }
}