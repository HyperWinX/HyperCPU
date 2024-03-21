#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <bit>
#include <cpu.hpp>
#include <errcode.hpp>
#include <exitcodes.hpp>
#include <opcodes.hpp>

#define is_one_byte(fopcode) fopcode > 0x00 && fopcode <= 0x0F


uint8_t HyperCPU::CPU::_fetch_byte(void){
    return _memory[_insp++];
}

uint16_t HyperCPU::CPU::_fetch_word(void){
    uint16_t val = 0;
    val = _memory[_insp++];
    val = (val << 8) | _memory[_insp++];
    return val;
}

uint32_t HyperCPU::CPU::_fetch_dword(void){
    uint32_t val;
    memcpy(&val, _memory + _insp, sizeof(uint32_t));
    _insp += 4;
    //val = std::byteswap(val);
    return val;
}

void HyperCPU::CPU::_set_datasize(HyperCPU::_instruction_t& instr, uint8_t byte){
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

HyperCPU::_instruction_t HyperCPU::CPU::_gen_instr(uint8_t fopcode, void*& ptr1, void*& ptr2){
    _instruction_t instr = {};
    instr._instrtp = _define_instr(static_cast<uint16_t>(fopcode));

    if (is_one_byte(fopcode)) return instr;

	uint8_t byte = _fetch_byte();
    switch(static_cast<argtp_t>(byte & 0xF)){
        case RM_R:
            instr.args = RM_R;
            ptr1 = _regPointers[_fetch_byte()];
            ptr2 = _regPointers[_fetch_byte()];
            break;
        case R_RM:
            instr.args = R_RM;
            ptr1 = _regPointers[_fetch_byte()];
            ptr2 = _regPointers[_fetch_byte()];
            break;
        case RM_IMM:
            instr.args = RM_IMM;
            ptr1 = _regPointers[_fetch_byte()];
            ptr2 = _memory + _insp;
            _insp += 4;
            break;
        case R_IMM:
            instr.args = R_IMM;
            ptr1 = _regPointers[_fetch_byte()];
            ptr2 = _memory + _insp;
            _insp += 4;
            break;
        case RM_M: {
            instr.args = RM_M;
            ptr1 = _regPointers[_fetch_byte()];
            uint32_t dword = _fetch_dword();
            ptr2 = _memory + dword;
            break;
        }
        case R_M:
            instr.args = R_M;
            ptr1 = _regPointers[_fetch_byte()];
            ptr2 = _memory + _fetch_dword();
            break;
        case M_R:
            instr.args = M_R;
            ptr1 = _memory + _fetch_dword();
            ptr2 = _regPointers[_fetch_byte()];
            break;
        case M_RM:
            instr.args = M_RM;
            ptr1 = _memory + _fetch_dword();
            ptr2 = _regPointers[_fetch_byte()];
            break;
        case R:
            instr.args = R;
            ptr1 = _regPointers[_fetch_byte()];
            break;
        case M:
            instr.args = M;
            ptr1 = _memory + _fetch_dword();
            break;
        case IMM:
            instr.args = IMM;
            ptr1 = _memory + _insp;
            _insp += 4;
            break;
        case NOARG:
            instr.args = NOARG;
            return instr;
        default: return instr;
    }
	_set_datasize(instr, byte);
	return instr;
}

int HyperCPU::CPU::Reset(int mem_size){
    _memory = (char*)calloc(mem_size, sizeof(char));
    if (!_memory) return 1;
    for (int i = 0; i < static_cast<int>(sizeof(_xRegs) / sizeof(uint32_t)); i++)
        _xRegs[i] = 0;
    _stp = _bstp = 0;
    _insp = 0x0100;
    _idtr = 0;
    _cmpr = 0;
    // Creating array of register pointers
    _regPointers = static_cast<void**>(calloc(vecr7, sizeof(void*)));
    if (!_regPointers) return 1;
    int index = 0;
    // Set x# registers
    for (int i = 0; index < 32; index++, i++)
        _regPointers[index] = &(_xRegs[i]);
    // Set xh# registers
    for (int i = 0; index < 64; index++, i++)
        _regPointers[index] = reinterpret_cast<void*>(&_xRegs[i]);
    // Set xl# registers
    for (int i = 0; index < 96; index++, i++)
        _regPointers[index] = reinterpret_cast<void*>(&_xRegs[i] + 2);
    // Set xlh# registers
    for (int i = 0; index < 128; index++, i++)
        _regPointers[index] = reinterpret_cast<void*>(&_xRegs[i] + 2);
    // Set xll# registers
    for (int i = 0; index < 160; index++, i++)
        _regPointers[index] = reinterpret_cast<void*>(&_xRegs[i] + 3);
    // Set other register pointers
    _regPointers[index++] = reinterpret_cast<void*>(&_stp);
    _regPointers[index++] = reinterpret_cast<void*>(&_bstp);
    _regPointers[index++] = reinterpret_cast<void*>(&_insp);
    for (int i = 0; i < 8; i++, index++)
        _regPointers[index] = reinterpret_cast<void*>(&_vRegs[i]);
    return 0;
}

void HyperCPU::CPU::CleanUp(){
    if (_memory) free(_memory);
}

int HyperCPU::CPU::Execute(){
    if (!_memory) return ERR_MEMFAIL;
    void *ptr1, *ptr2;
    while (1){
        _instruction_t instr = _gen_instr(_fetch_byte(), ptr1, ptr2); // Generate instruction from fetched byte

        /* Main loop */
        switch(instr._instrtp){
            case INS_ADC:
                if (_ins_adc_exec(instr, ptr1, ptr2))
                    return EXIT_OPCODEFAILURE;
                break;
            case INS_ADD:{
                if (_ins_add_exec(instr, ptr1, ptr2))
                    return EXIT_OPCODEFAILURE;
                break;
            }
            case INS_AND:{
                if (_ins_and_exec(instr, ptr1, ptr2))
                    return EXIT_OPCODEFAILURE;
                break;
            }
            case INS_ANDN:{
                if (_ins_andn_exec(instr, ptr1, ptr2))
                    return EXIT_OPCODEFAILURE;
                break;
            }
            case INS_CALL:{

            }
            case INS_CLC:
                _ins_clc_exec();
                break;
            case INS_INC:
                if (_ins_inc_exec(instr, ptr1))
                    return EXIT_OPCODEFAILURE;
                break;
            case INS_DEC:
                if (_ins_dec_exec(instr, ptr1))
                    return EXIT_OPCODEFAILURE;
                break;
            case INS_JE:{
                break;
            }
            case INS_UNKNOWN: return EXIT_UNKNOWN;
            case INS_HLT: return EXIT_HALT;
        }
    }
}
