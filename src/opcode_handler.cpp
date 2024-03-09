#include <cstdint>
#include <opcodes.hpp>
#include <cpu.hpp>

HyperCPU::instr_t HyperCPU::CPU::_define_instr(uint16_t opcode){
    switch(opcode){
        case AND: return HyperCPU::INS_AND;
    }
    return {};
}