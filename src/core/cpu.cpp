#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cpu.hpp>
#include <errcode.hpp>
#include <exitcodes.hpp>
#include <opcodes.hpp>
#include <iostream>

#define is_one_byte(fopcode) (fopcode > 0x00 && fopcode <= 0x0F)

uint8_t HyperCPU::CPU::fetch_byte(void){
    return memoryptr[insp++];
}

uint16_t HyperCPU::CPU::fetch_word(void){
    uint16_t val = 0;
    val = memoryptr[insp++];
    val = (val << 8) | memoryptr[insp++];
    return val;
}

uint32_t HyperCPU::CPU::fetch_dword(void){
    uint32_t val;
    memcpy(&val, memoryptr + insp, sizeof(uint32_t));
    insp += 4;
    //val = std::byteswap(val);
    return val;
}

void HyperCPU::CPU::set_datasize(HyperCPU::instruction_t& instr, uint8_t byte){
    switch(static_cast<datasize_t>((byte & 0b00110000) >> 4)){
		case b8:
			instr.size = b8;
			return;
		case b16:
			instr.size = b16;
			return;
		case b32:
			instr.size = b32;
			return;
		default:
			instr.size = bUNKNOWN;
			return;
	}
}

HyperCPU::instruction_t HyperCPU::CPU::gen_instr(uint8_t fopcode, void*& ptr1, void*& ptr2){
    instruction_t instr = {};
    instr._instrtp = define_instr(static_cast<uint16_t>(fopcode));

    if (is_one_byte(fopcode)) return instr;

    if (fopcode == CALL){
        instr.args = NOARG;
        return instr;
    }
	uint8_t byte = fetch_byte();
    set_datasize(instr, byte);
    switch(static_cast<argtp_t>(byte & 0xF)){
        case RM_R:
            instr.args = RM_R;
            ptr1 = regPointers[fetch_byte()];
            ptr2 = regPointers[fetch_byte()];
            break;
        case R_RM:
            instr.args = R_RM;
            ptr1 = regPointers[fetch_byte()];
            ptr2 = regPointers[fetch_byte()];
            break;
        case RM_IMM:
            instr.args = RM_IMM;
            ptr1 = regPointers[fetch_byte()];
            ptr2 = memoryptr + insp;
            insp += 4;
            break;
        case R_IMM:
            instr.args = R_IMM;
            ptr1 = regPointers[fetch_byte()];
            ptr2 = memoryptr + insp;
            insp += 4;
            break;
        case RM_M: {
            instr.args = RM_M;
            ptr1 = regPointers[fetch_byte()];
            uint32_t dword = fetch_dword();
            ptr2 = memoryptr + dword;
            break;
        }
        case R_M:
            instr.args = R_M;
            ptr1 = regPointers[fetch_byte()];
            ptr2 = memoryptr + fetch_dword();
            break;
        case M_R:
            instr.args = M_R;
            ptr1 = memoryptr + fetch_dword();
            ptr2 = regPointers[fetch_byte()];
            break;
        case M_RM:
            instr.args = M_RM;
            ptr1 = memoryptr + fetch_dword();
            ptr2 = regPointers[fetch_byte()];
            break;
        case R_R:
            instr.args = R_R;
            ptr1 = regPointers[fetch_byte()];
            ptr2 = regPointers[fetch_byte()];
            break;
        case R:
            instr.args = R;
            ptr1 = regPointers[fetch_byte()];
            break;
        case M:
            instr.args = M;
            ptr1 = memoryptr + fetch_dword();
            break;
        case IMM:
            instr.args = IMM;
            ptr1 = memoryptr + insp;
            switch (instr.size){
                case b8: insp += 1; break;
                case b16: insp += 2; break;
                case b32: insp += 4; break;
                case bUNKNOWN: return instr;
            }
            break;
        case NOARG:
            instr.args = NOARG;
            return instr;
        default: return instr;
    }
	return instr;
}

int HyperCPU::CPU::Reset(int mem_size){
    memoryptr = (char*)calloc(mem_size, sizeof(char));
    if (!memoryptr) return 1;
    for (int i = 0; i < static_cast<int>(sizeof(xRegs) / sizeof(uint32_t)); i++)
        xRegs[i] = 0;
    stp = bstp = 0;
    insp = 0x0100;
    idtr = 0;
    gdtr = 0;
    cmpr = 0;
    gdt_initialized = false;
    idt_initialized = false;
    cmpr = false;
    ovr = false;
    bigger = false;
    carry_flag = false;
    // Creating array of register pointers
    regPointers = static_cast<void**>(calloc(vecr7, sizeof(char*)));
    if (!regPointers) return 1;
    int index = 0;
    // Set x# registers
    for (int i = 0; index < 32; index++, i++)
        regPointers[index] = &(xRegs[i]);
    // Set xh# registers
    for (int i = 0; index < 64; index++, i++)
        regPointers[index] = reinterpret_cast<void*>(&xRegs[i]);
    // Set xl# registers
    for (int i = 0; index < 96; index++, i++)
        regPointers[index] = reinterpret_cast<void*>((char*)&xRegs[i] + 2);
    // Set xlh# registers
    for (int i = 0; index < 128; index++, i++)
        regPointers[index] = reinterpret_cast<void*>((char*)&xRegs[i] + 2);
    // Set xll# registers
    for (int i = 0; index < 160; index++, i++)
        regPointers[index] = reinterpret_cast<void*>((char*)&xRegs[i] + 3);
    // Set other register pointers
    regPointers[index++] = reinterpret_cast<void*>(&stp);
    regPointers[index++] = reinterpret_cast<void*>(&bstp);
    regPointers[index++] = reinterpret_cast<void*>(&insp);
    //for (int i = 0; i < 8; i++, index++)
        //regPointers[index] = reinterpret_cast<void*>(&vRegs[i]);
    return 0;
}

void HyperCPU::CPU::CleanUp(){
    if (memoryptr) free(memoryptr);
}

int HyperCPU::CPU::Execute(){
    if (!memoryptr) return ERR_MEMFAIL;
    void *ptr1, *ptr2;
    while (1){
        instruction_t instr = gen_instr(fetch_byte(), ptr1, ptr2); // Generate instruction from fetched byte

        /* Main loop */
        switch(instr._instrtp){
            case INS_ADC:
                if (ins_adc_exec(instr, ptr1, ptr2))
                    return EXIT_OPCODEFAILURE;
                break;
            case INS_ADD:{
                if (ins_add_exec(instr, ptr1, ptr2))
                    return EXIT_OPCODEFAILURE;
                break;
            }
            case INS_AND:{
                if (ins_and_exec(instr, ptr1, ptr2))
                    return EXIT_OPCODEFAILURE;
                break;
            }
            case INS_ANDN:{
                if (ins_andn_exec(instr, ptr1, ptr2))
                    return EXIT_OPCODEFAILURE;
                break;
            }
            case INS_CALL:
                ins_call_exec();
                break;
            case INS_CLC:
                ins_clc_exec();
                break;
            case INS_INC:
                if (ins_inc_exec(instr, ptr1))
                    return EXIT_OPCODEFAILURE;
                break;
            case INS_DEC:
                if (ins_dec_exec(instr, ptr1))
                    return EXIT_OPCODEFAILURE;
                break;
            case INS_MOV:
                if (ins_mov_exec(instr, ptr1, ptr2))
                    return EXIT_OPCODEFAILURE;
                break;
            case INS_PUSH:
                if (ins_push_exec(instr, ptr1))
                    return EXIT_OPCODEFAILURE;
                break;
            case INS_POP:
                if (ins_pop_exec(instr, ptr1))
                    return EXIT_OPCODEFAILURE;
                break;
            case INS_CMP:
                if (ins_cmp_exec(instr, ptr1, ptr2))
                    return EXIT_OPCODEFAILURE;
                break;
            case INS_BSWP:
                if (ins_bswp_exec(instr, ptr1))
                    return EXIT_OPCODEFAILURE;
                break;
            case INS_INFO:
                ins_info_exec();
                break;
            case INS_JMP:
                ins_jmp_exec(instr, ptr1);
                break;
            case INS_JGE:
                ins_jge_exec(instr, ptr1);
                break;
            case INS_JLE:
                ins_jle_exec(instr, ptr1);
                break;
            case INS_JE:
                ins_je_exec(instr, ptr1);
                break;
            case INS_JG:
                ins_jg_exec(instr, ptr1);
                break;
            case INS_JL:
                ins_jl_exec(instr, ptr1);
                break;
            case INS_RET:
                ins_ret_exec();
                break;
            case INS_SUB:
                if (ins_sub_exec(instr, ptr1, ptr2))
                    return EXIT_OPCODEFAILURE;
                break;
            case INS_MUL:
                if (ins_mul_exec(instr, ptr1, ptr2))
                    return EXIT_OPCODEFAILURE;
                break;
            case INS_DIV:
                if (ins_div_exec(instr, ptr1, ptr2))
                    return EXIT_OPCODEFAILURE;
                break;
            case INS_UNKNOWN: return EXIT_UNKNOWN;
            case INS_HLT: return EXIT_HALT;
            default: return EXIT_UNKNOWN;
        }
    }
}
