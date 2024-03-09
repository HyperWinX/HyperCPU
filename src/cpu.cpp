#include <cstdint>
#include <cstdlib>
#include <cpu.hpp>
#include <errcode.hpp>

uint8_t HyperCPU::CPU::_fetch_byte(void){
    return _memory[_insp++];
}

HyperCPU::_instruction_t HyperCPU::CPU::_gen_instr(uint8_t fopcode){
    _instruction_t instr = {};
    return instr;
}

void HyperCPU::CPU::Reset(int mem_size){
    _memory = (char*)calloc(mem_size, sizeof(char));
    for (int i = 0; i < static_cast<int>(sizeof(_xRegs) / sizeof(uint32_t)); i++)
        _xRegs[i] = 0;
    _stp = _bstp = 0;
    _insp = 0x0100;
    _idtr = 0;
    _CMPR = 0;
}

int HyperCPU::CPU::Execute(){
    if (!_memory) return ERR_MEMFAIL;
    while (1){
        _instruction_t instr = _gen_instr(_fetch_byte());
        switch(instr._instrtp){
            case INS_AND:{
                
            }
        }
    }
}