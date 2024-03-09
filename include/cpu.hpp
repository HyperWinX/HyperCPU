#include <cstdint>

#pragma once

#define byte_is_instr(byte) byte

namespace HyperCPU{
    enum instr_t{
        INS_AND
    };
    enum reg_t{
        x0, x1, x2, x3, x4, x5, x6, x7,
        x8, x9, x10, x11, x12, x13, x14, x15,
        x16, x17, x18, x19, x20, x21, x22, x23,
        x24, x25, x26, x27, x28, x29, x30, x31, // GP registers

        xh0, xh1, xh2, xh3, xh4, xh5, xh6, xh7,
        xh8, xh9, xh10, xh11, xh12, xh13, xh14, xh15,
        xh16, xh17, xh18, xh19, xh20, xh21, xh22, xh23,
        xh24, xh25, xh26, xh27, xh28, xh29, xh30, xh31, // GP registers: high halfs

        xl0, xl1, xl2, xl3, xl4, xl5, xl6, xl7,
        xl8, xl9, xl10, xl11, xl12, xl13, xl14, xl15,
        xl16, xl17, xl18, xl19, xl20, xl21, xl22, xl23,
        xl24, xl25, xl26, xl27, xl28, xl29, xl30, xl31, // GP registers: low halfs

        stp, bstp, // Stack related registers

        insp, // Instruction pointer register

        vecr0, vecr1, vecr2, vecr3, vecr4, vecr5, vecr6, vecr7 // Vector operation registers
    };
    struct _instruction_t{
        instr_t _instrtp;
        uint32_t arg1, arg2;
    };
    class CPU{
        private:
        char* _memory;
        uint32_t _xRegs[32]; // General purpose register
        uint32_t _stp, _bstp; // Stack related registers
        uint32_t _insp; // Instruction pointer
        uint32_t _idtr; // IDT pointer register
        bool _CMPR; // CMP result flag
        uint8_t _fetch_byte(void);
        _instruction_t _gen_instr(uint8_t);
        instr_t _define_instr(uint16_t);

        public:
        void Reset(int mem_size);
        int Execute();
    };
}