#include <cstdint>

#include <tuple>

#pragma once

namespace HyperCPU{
    enum instr_t{
        INS_ADC,
        INS_ADD,
        INS_AND,
        INS_ANDN,
        INS_CALL,
        INS_CLC,
        INS_INC,
        INS_DEC,
        INS_HLT,
        INS_MOV,
        INS_PUSH,
        INS_POP,
        INS_CMP,
        INS_BSWP,
        INS_JE,
        INS_UNKNOWN
    };
    enum argtp_t{
        RM_R=0x01,
        R_RM=0x02,
        RM_IMM=0x03,
        R_IMM=0x04,
        RM_M=0x05,
        R_M=0x06,
        M_R=0x07,
        M_RM=0x08,
        R_R=0x09,
        R=0x0A,
        M=0x0B,
        IMM=0x0C,
        NOARG=0x0F
    };
    enum datasize_t{
        b8=0,
        b16=1,
        b32=2,
		bUNKNOWN=3
    };
    enum reg_t{
        x0=0, x1=1, x2=2, x3=3, x4=4, x5=5, x6=6, x7=7,
        x8=8, x9=9, x10=10, x11=11, x12=12, x13=13, x14=14, x15=15,
        x16=16, x17=17, x18=18, x19=19, x20=20, x21=21, x22=22, x23=23,
        x24=24, x25=25, x26=26, x27=27, x28=28, x29=29, x30=30, x31=31, // GP registers

        xh0=32, xh1=33, xh2=34, xh3=35, xh4=36, xh5=37, xh6=38, xh7=39,
        xh8=40, xh9=41, xh10=42, xh11=43, xh12=44, xh13=45, xh14=46, xh15=47,
        xh16=48, xh17=49, xh18=50, xh19=51, xh20=52, xh21=53, xh22=54, xh23=55,
        xh24=56, xh25=57, xh26=58, xh27=59, xh28=60, xh29=61, xh30=62, xh31=63, // GP registers: high halfs

        xl0=64, xl1=65, xl2=66, xl3=67, xl4=68, xl5=69, xl6=70, xl7=71,
        xl8=72, xl9=73, xl10=74, xl11=75, xl12=76, xl13=77, xl14=78, xl15=79,
        xl16=80, xl17=81, xl18=82, xl19=83, xl20=84, xl21=85, xl22=86, xl23=87,
        xl24=88, xl25=89, xl26=90, xl27=91, xl28=92, xl29=93, xl30=94, xl31=95, // GP registers: low halfs

        xlh0=96, xlh1=97, xlh2=98, xlh3=99, xlh4=100, xlh5=101, xlh6=102, xlh7=103,
        xlh8=104, xlh9=105, xlh10=106, xlh11=107, xlh12=108, xlh13=109, xlh14=110, xlh15=111,
        xlh16=112, xlh17=113, xlh18=114, xlh19=115, xlh20=116, xlh21=117, xlh22=118, xlh23=119,
        xlh24=120, xlh25=121, xlh26=122, xlh27=123, xlh28=124, xlh29=125, xlh30=126, xlh31=127, // GP registers: high halfs of low halfs

        xll0=128, xll1=129, xll2=130, xll3=131, xll4=132, xll5=133, xll6=134, xll7=135,
        xll8=136, xll9=137, xll10=138, xll11=139, xll12=140, xll13=141, xll14=142, xll15=143,
        xll16=144, xll17=145, xll18=146, xll19=147, xll20=148, xll21=149, xll22=150, xll23=151,
        xll24=152, xll25=153, xll26=154, xll27=155, xll28=156, xll29=157, xll30=158, xll31=159, // GP registers: low halfs of low halfs

        stp=160, bstp=161, // Stack related registers

        insp=162, // Instruction pointer register

        vecr0=163, vecr1=164, vecr2=165, vecr3=166, vecr4=167, vecr5=168, vecr6=169, vecr7=170 // Vector operation registers
    };

    struct _instruction_t{
        instr_t _instrtp;
        argtp_t args;
        datasize_t size;
        uint32_t arg1, arg2;
    };

    enum _exception_t{
        INVALID_OPCODE=0
    };
    class CPU{
        private:
        // Functions
        uint8_t _fetch_byte(void);
        uint16_t _fetch_word(void);
        uint32_t _fetch_dword(void);
        _instruction_t _gen_instr(uint8_t fopcode, void*& ptr1, void*& ptr2);
        instr_t _define_instr(uint16_t);
        void _set_datasize(_instruction_t&, uint8_t);

        // Stack helpers
        void _push_byte(uint8_t byte);
        void _push_word(uint16_t word);
        void _push_dword(uint32_t dword);
        uint8_t _pop_byte(void);
        uint16_t _pop_word(void);
        uint32_t _pop_dword(void);
        
        // Data fetchers
        std::tuple<uint8_t, uint8_t> _fetch_content8(argtp_t type, void *ptr1, void *ptr2);
        std::tuple<uint16_t, uint16_t> _fetch_content16(argtp_t type, void *ptr1, void *ptr2);
        std::tuple<uint32_t, uint32_t> _fetch_content32(argtp_t type, void *ptr1, void *ptr2);
        uint8_t _fetch_fptr8(argtp_t type, void *ptr);
        uint16_t _fetch_fptr16(argtp_t type, void *ptr);
        uint32_t _fetch_fptr32(argtp_t type, void *ptr);
        inline uint8_t rm_8(void* ptr);
        inline uint16_t rm_16(void* ptr);
        inline uint32_t rm_32(void* ptr);
        inline uint8_t r_8(void* ptr);
        inline uint16_t r_16(void* ptr);
        inline uint32_t r_32(void* ptr);
        inline uint8_t m_8(void* ptr);
        inline uint16_t m_16(void* ptr);
        inline uint32_t m_32(void* ptr);
        inline uint8_t imm_8(void* ptr);
        inline uint16_t imm_16(void* ptr);
        inline uint32_t imm_32(void* ptr);
        int carry(void);
        int _write_instruction_result(_instruction_t &instr, void *dst, void *src, int length);
        // Exception handlers
        int _raise_fatal_exception(_exception_t exception);
        // All instructions
        int _ins_adc_exec(_instruction_t& instr, void* ptr1, void* ptr2);
        int _ins_add_exec(_instruction_t& instr, void* ptr1, void* ptr2);
        int _ins_and_exec(_instruction_t& instr, void* ptr1, void* ptr2);
        int _ins_andn_exec(_instruction_t& instr, void* ptr1, void* ptr2);
        void _ins_clc_exec(void);
        int _ins_inc_exec(_instruction_t& instr, void* ptr1);
        int _ins_dec_exec(_instruction_t& instr, void* ptr1);
        int _ins_mov_exec(_instruction_t& instr, void* ptr1, void* ptr2);
        void _ins_call_exec(void* ptr1);
        int _ins_push_exec(_instruction_t& instr, void* ptr1);
        int _ins_pop_exec(_instruction_t& instr, void* ptr1);
        int _ins_cmp_exec(_instruction_t& instr, void* ptr1, void* ptr2);
        int _ins_bswp_exec(_instruction_t& instr, void *ptr1);
        public:
        // Variables
        char* _memory;
        void** _regPointers;
        uint32_t _xRegs[32]; // General purpose register
        uint32_t _stp, _bstp; // Stack related registers
        uint32_t _insp; // Instruction pointer
        uint32_t _idtr; // IDT pointer register
        uint64_t _vRegs[8];
        bool _cmpr; // CMP result flag
        bool _bigger; // Affected if _cmpr after CMP instruction is set to 0
        bool _carry; // Carry flag
        bool _ovr; // Overflow flag
        
        int Reset(int mem_size);
        void CleanUp();
        int Execute();
    };
}
