#include <cpu.hpp>
#include <bit>
#include <cstdio>

int HyperCPU::CPU::_ins_adc_exec(HyperCPU::_instruction_t &instr, void* ptr1, void* ptr2) {
    switch (instr.args){
        case RM_R:
            if (instr.size == b8)
                *reinterpret_cast<uint8_t*>(_memory + *reinterpret_cast<uint32_t*>(ptr1)) += *reinterpret_cast<uint8_t*>(ptr2) + static_cast<int>(_carry);
            else if (instr.size == b16)puts("bruh wtf");
                //*reinterpret_cast<uint16_t*>(_memory + *reinterpret_cast<uint16_t*>(ptr1)) += std::byteswap(*reinterpret_cast<uint16_t*>(ptr2) + static_cast<int>(_carry));
            else
                *reinterpret_cast<uint32_t*>(_memory + *reinterpret_cast<uint32_t*>(ptr1)) += *reinterpret_cast<uint32_t*>(ptr2) + static_cast<int>(_carry);
            break;
        default: return 1;
    }
    return 0;
}