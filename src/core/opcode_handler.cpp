#include <opcodes.hpp>
#include <cpu.hpp>

HyperCPU::instr_t HyperCPU::CPU::define_instr(uint16_t opcode){
    switch(opcode){
        case ADC: return HyperCPU::INS_ADC;
        case ADD: return HyperCPU::INS_ADD;
        case AND: return HyperCPU::INS_AND;
        case ANDN: return HyperCPU::INS_ANDN;
        case CALL: return HyperCPU::INS_CALL;
        case CLC: return HyperCPU::INS_CLC;
        case INC: return HyperCPU::INS_INC;
        case DEC: return HyperCPU::INS_DEC;
        case MOV: return HyperCPU::INS_MOV;
        case PUSH: return HyperCPU::INS_PUSH;

        case POP: return HyperCPU::INS_POP;
        case CMP: return HyperCPU::INS_CMP;
        case HLT: return HyperCPU::INS_HLT;
        default: return HyperCPU::INS_UNKNOWN;
    }
}