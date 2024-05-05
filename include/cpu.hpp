#include <cstdint>

#include <tuple>
#include <string>

#pragma once

namespace HyperCPU{
    enum instr_t{
        INS_ADC=0,
        INS_ADD=1,
        INS_AND=2,
        INS_ANDN=3,
        INS_CALL=4,
        INS_CLC=5,
        INS_INC=6,
        INS_DEC=7,
        INS_HLT=8,
        INS_MOV=9,
        INS_PUSH=10,
        INS_POP=11,
        INS_CMP=12,
        INS_BSWP=13,
        INS_JMP=14,
        INS_INFO=15,
        INS_JE=16,
        INS_JGE=17,
        INS_JLE=18,
        INS_JG=19,
        INS_JL=20,
        INS_RET=21,
        INS_SUB=22,
        INS_MUL=23,
        INS_DIV=24,
        INS_UNKNOWN=65535
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
        NOARG=0x0D,
        UNDEF=0x0F
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
    enum exception_t{
        INVALID_OPCODE=0,
        SEGMENTATION_FAULT=1,
        GDT_READ_FAILURE=2,
        GDT_INVALID_ADDRESS=3,
        INFO_INVALID_MODE=4,
        TRIPLE_FAULT=5
    };
    struct instruction_t{
        instr_t _instrtp;
        argtp_t args;
        datasize_t size;
        uint32_t arg1, arg2;
    };
    struct idt_entry_t{
        uint32_t address;
    } __attribute__((packed));
    struct gdt_table_t{
        uint16_t length;
        uint32_t base;
    } __attribute__((packed));
    struct gdt_entry_t{
        uint32_t base;
        uint32_t limit;
        uint8_t flags;
        uint8_t type;
    } __attribute__((packed));
    extern uint8_t allowed_op_types[][14];
    class CPU{
        private:
        // Functions
        uint8_t fetch_byte(void);
        uint16_t fetch_word(void);
        uint32_t fetch_dword(void);
        instruction_t gen_instr(uint8_t fopcode, void*& ptr1, void*& ptr2);
        instr_t define_instr(uint16_t);
        void set_datasize(instruction_t&, uint8_t);
        uint8_t verify_operand_types(instruction_t&);

        // Stack helpers
        void push_byte(uint8_t byte);
        void push_word(uint16_t word);
        void push_dword(uint32_t dword);
        uint8_t pop_byte(void);
        uint16_t pop_word(void);
        uint32_t pop_dword(void);
        
        // Data fetchers
        std::tuple<uint8_t, uint8_t> fetch_content8(argtp_t type, void *ptr1, void *ptr2);
        std::tuple<uint16_t, uint16_t> fetch_content16(argtp_t type, void *ptr1, void *ptr2);
        std::tuple<uint32_t, uint32_t> fetch_content32(argtp_t type, void *ptr1, void *ptr2);
        uint8_t fetch_fptr8(argtp_t type, void *ptr);
        uint16_t fetch_fptr16(argtp_t type, void *ptr);
        uint32_t fetch_fptr32(argtp_t type, void *ptr);
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
        int write_instruction_result(instruction_t &instr, void *dst, void *src, int length);
        // Exception handlers
        int raise_fatal_exception(exception_t exception);
        // Memory controller
        void writememoryptr(uint32_t addr, void *ptr, int length);
        // GDT
        int is_access_allowed(uint32_t addr);
        // IDT
        void raise_exception_interrupt(exception_t exception);
        void execute_IDT_entry(uint8_t entry);
        // All instructions
        int ins_adc_exec(instruction_t& instr, void* ptr1, void* ptr2);
        int ins_add_exec(instruction_t& instr, void* ptr1, void* ptr2);
        int ins_and_exec(instruction_t& instr, void* ptr1, void* ptr2);
        int ins_andn_exec(instruction_t& instr, void* ptr1, void* ptr2);
        void ins_clc_exec();
        int ins_inc_exec(instruction_t& instr, void* ptr1);
        int ins_dec_exec(instruction_t& instr, void* ptr1);
        int ins_mov_exec(instruction_t& instr, void* ptr1, void* ptr2);
        int ins_call_exec();
        int ins_push_exec(instruction_t& instr, void* ptr1);
        int ins_pop_exec(instruction_t& instr, void* ptr1);
        int ins_cmp_exec(instruction_t& instr, void* ptr1, void* ptr2);
        int ins_bswp_exec(instruction_t& instr, void *ptr1);
        void ins_info_exec();
        void ins_jmp_exec(instruction_t& instr, void *ptr1);
        void ins_je_exec(instruction_t& instr, void *ptr1);
        void ins_jge_exec(instruction_t& instr, void *ptr1);
        void ins_jle_exec(instruction_t& instr, void *ptr1);
        void ins_jg_exec(instruction_t& instr, void *ptr1);
        void ins_jl_exec(instruction_t& instr, void *ptr1);
        void ins_ret_exec();
        int ins_sub_exec(instruction_t& instr, void *ptr1, void *ptr2);
        int ins_mul_exec(instruction_t& instr, void *ptr1, void *ptr2);
        int ins_div_exec(instruction_t& instr, void *ptr1, void *ptr2);
        public:
        // Variables
        char* memoryptr;
        void** regPointers;
        uint32_t xRegs[32]; // General purpose register
        uint32_t stp, bstp; // Stack related registers
        uint32_t insp; // Instruction pointer
        uint32_t idtr; // IDT pointer register
        uint32_t gdtr; // GDT pointer register
        uint64_t vRegs[8];
        bool gdt_initialized; // GDT is initialized
        bool idt_initialized; // IDT is initialized
        bool cmpr; // CMP result flag
        bool bigger; // Affected if cmpr after CMP instruction is set to 0
        bool carry_flag; // Carry flag
        bool ovr; // Overflow flag
        std::string developer = "HyperWin";
        std::string version = "0.1a";
        std::string name = "HyperCPU";
        int Reset(int mem_size);
        void CleanUp();
        int Execute();
    };
}
