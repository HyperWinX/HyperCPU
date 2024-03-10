#include <cstdint>
#include <cstdlib>
#include <cpu.hpp>
#include <errcode.hpp>
#include <exitcodes.hpp>
#include <opcodes.hpp>

#define is_one_byte(fopcode) fopcode > 0x00 && fopcode <= 0x0F


uint8_t HyperCPU::CPU::_fetch_byte(void){
    return _memory[_insp++];
}

uint16_t HyperCPU::CPU::_fetch_word(void){
    uint16_t val = *((uint16_t*)&_memory[_insp]);
    _insp += 2;
    return val;
}

uint32_t HyperCPU::CPU::_fetch_dword(void){
    uint32_t val = *((uint32_t*)&_memory[_insp]);
    _insp += 4;
    return val;
}

void HyperCPU::CPU::_set_datasize(HyperCPU::_instruction_t& instr){
    int type = static_cast<int>(instr._instrtp);
    int reg;

    if (type >= 0 && type <= 6)
        reg = static_cast<int>(instr.arg1);
    else if (type == 7 || type == 8)
        reg = static_cast<int>(instr.arg2);
    else{
        reg = -1;
        instr.size = b32;
    }

    if ((reg >= 0 && reg <= 31) || (reg >= 160 && reg <= 161))
        instr.size = b32;
    else if (reg >= 32 && reg <= 95)
        instr.size = b16;
    else
        instr.size = b8;
}

HyperCPU::_instruction_t HyperCPU::CPU::_gen_instr(uint8_t fopcode){
    _instruction_t instr = {};
    instr._instrtp = _define_instr(static_cast<uint16_t>(fopcode));

    if (is_one_byte(fopcode)) return instr;

    switch(static_cast<argtp_t>(_fetch_byte() & 0xF)){
        case RM_R:
            instr.args = RM_R;
            instr.arg1 = _fetch_byte();
            instr.arg2 = _fetch_byte();
            return instr;
        case R_RM:
            instr.args = R_RM;
            instr.arg1 = _fetch_byte();
            instr.arg2 = _fetch_byte();
            return instr;
        case RM_IMM:
            instr.args = RM_IMM;
            instr.arg1 = _fetch_byte();
            instr.arg2 = _fetch_dword();
            return instr;
        case R_IMM:
            instr.args = R_IMM;
            instr.arg1 = _fetch_byte();
            instr.arg2 = _fetch_dword();
            return instr;
        case RM_M:
            instr.args = RM_M;
            instr.arg1 = _fetch_byte();
            instr.arg2 = _fetch_dword();
            return instr;
        case R_M:
            instr.args = R_M;
            instr.arg1 = _fetch_byte();
            instr.arg2 = _fetch_dword();
            return instr;
        case M_R:
            instr.args = M_R;
            instr.arg1 = _fetch_dword();
            instr.arg2 = _fetch_byte();
            return instr;
        case M_RM:
            instr.args = M_RM;
            instr.arg1 = _fetch_dword();
            instr.arg2 = _fetch_byte();
            return instr;
        case R:
            instr.args = R;
            instr.arg1 = _fetch_byte();
            return instr;
        case IMM:
            instr.args = IMM;
            instr.arg1 = _fetch_dword();
            return instr;
        default: return instr;
    }
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

void HyperCPU::CPU::CleanUp(){
    if (_memory) free(_memory);
}

int HyperCPU::CPU::Execute(){
    if (!_memory) return ERR_MEMFAIL;
    while (1){
        _instruction_t instr = _gen_instr(_fetch_byte());
        switch(instr._instrtp){
            case INS_ADC:{
                
            }
            case INS_AND:{
                
            }
            case INS_JE:{

            }
            case INS_UNKNOWN: return EXIT_UNKNOWN;
            case INS_HLT: return EXIT_HALT;
        }
    }
}