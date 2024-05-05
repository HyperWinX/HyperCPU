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
        case BSWP: return HyperCPU::INS_BSWP;
        case POP: return HyperCPU::INS_POP;
        case CMP: return HyperCPU::INS_CMP;
        case HLT: return HyperCPU::INS_HLT;
        case INFO: return HyperCPU::INS_INFO;
        case JMP: return HyperCPU::INS_JMP;
        case JE: return HyperCPU::INS_JE;
        case JGE: return HyperCPU::INS_JGE;
        case JLE: return HyperCPU::INS_JLE;
        case JG: return HyperCPU::INS_JG;
        case JL: return HyperCPU::INS_JL;
        case RET: return HyperCPU::INS_RET;
        case SUB: return HyperCPU::INS_SUB;
        case MUL: return HyperCPU::INS_MUL;
        case DIV: return HyperCPU::INS_DIV;
        default: return HyperCPU::INS_UNKNOWN;
    }
}