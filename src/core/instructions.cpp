#include <cpu.hpp>

#include <cstdio>
#include <cstring>
#include <cstdint>

#include <iostream>
#include <functional>

#define RM_T(ptr, type) (*reinterpret_cast<type*>(_memory + *reinterpret_cast<uint32_t*>(ptr)))
#define R_T(ptr, type) (*reinterpret_cast<type*>(ptr))
#define M_T(ptr, type) (*reinterpret_cast<type*>(ptr))
#define IMM_T(ptr, type) (*reinterpret_cast<type*>(ptr))
#define CARRY_T() (static_cast<int>(_carry))

int HyperCPU::CPU::_ins_adc_exec(HyperCPU::_instruction_t &instr, void* ptr1, void* ptr2) {
    if (instr.size == b8){
        std::tuple<uint8_t, uint8_t> parts = _fetch_content8(instr.args, ptr1, ptr2);
        uint16_t result = 0;
        result = std::get<0>(parts) + std::get<1>(parts) + carry();
        if (result > UINT8_MAX) _ovr = true;
        else _ovr = false;
        _write_instruction_result(instr, ptr1, &result, 1);
    }
    else if (instr.size == b16){
        std::tuple<uint16_t, uint16_t> parts = _fetch_content16(instr.args, ptr1, ptr2);
        uint32_t result;
        result = std::get<0>(parts) + std::get<1>(parts) + carry();
        if (result > UINT16_MAX) _ovr = true;
        else _ovr = false;
        _write_instruction_result(instr, ptr1, &result, 2);
    }
    else if (instr.size == b32){
        std::tuple<uint32_t, uint32_t> parts = _fetch_content32(instr.args, ptr1, ptr2);
        uint64_t result;
        result = std::get<0>(parts) + std::get<1>(parts) + carry();
        if (result > UINT32_MAX) _ovr = true;
        else _ovr = false;
        _write_instruction_result(instr, ptr1, &result, 4);
    }
    else return 1;
    return 0;
}

int HyperCPU::CPU::_ins_add_exec(HyperCPU::_instruction_t &instr, void* ptr1, void* ptr2) {
    if (instr.size == b8){
        std::tuple<uint8_t, uint8_t> parts = _fetch_content8(instr.args, ptr1, ptr2);
        uint16_t result = 0;
        result = std::get<0>(parts) + std::get<1>(parts);
        if (result > UINT8_MAX) _ovr = true;
        else _ovr = false;
        _write_instruction_result(instr, ptr1, &result, 1);
    }
    else if (instr.size == b16){
        std::tuple<uint16_t, uint16_t> parts = _fetch_content16(instr.args, ptr1, ptr2);
        uint32_t result;
        result = std::get<0>(parts) + std::get<1>(parts);
        if (result > UINT16_MAX) _ovr = true;
        else _ovr = false;
        _write_instruction_result(instr, ptr1, &result, 2);
    }
    else if (instr.size == b32){
        std::tuple<uint32_t, uint32_t> parts = _fetch_content32(instr.args, ptr1, ptr2);
        uint64_t result;
        result = std::get<0>(parts) + std::get<1>(parts);
        if (result > UINT32_MAX) _ovr = true;
        else _ovr = false;
        _write_instruction_result(instr, ptr1, &result, 4);
    }
    else return 1;
    return 0;
}

int HyperCPU::CPU::_ins_and_exec(HyperCPU::_instruction_t &instr, void* ptr1, void* ptr2) {
    if (instr.size == b8){
        std::tuple<uint8_t, uint8_t> parts = _fetch_content8(instr.args, ptr1, ptr2);
        uint16_t result = 0;
        result = std::get<0>(parts) & std::get<1>(parts);
        if (result > UINT8_MAX) _ovr = true;
        else _ovr = false;
        _write_instruction_result(instr, ptr1, &result, 1);
    }
    else if (instr.size == b16){
        std::tuple<uint16_t, uint16_t> parts = _fetch_content16(instr.args, ptr1, ptr2);
        uint32_t result;
        result = std::get<0>(parts) & std::get<1>(parts);
        if (result > UINT16_MAX) _ovr = true;
        else _ovr = false;
        _write_instruction_result(instr, ptr1, &result, 2);
    }
    else if (instr.size == b32){
        std::tuple<uint32_t, uint32_t> parts = _fetch_content32(instr.args, ptr1, ptr2);
        uint64_t result;
        result = std::get<0>(parts) & std::get<1>(parts);
        if (result > UINT32_MAX) _ovr = true;
        else _ovr = false;
        _write_instruction_result(instr, ptr1, &result, 4);
    }
    else return 1;
    return 0;
}

int HyperCPU::CPU::_ins_andn_exec(HyperCPU::_instruction_t &instr, void* ptr1, void* ptr2) {
    if (instr.size == b8){
        std::tuple<uint8_t, uint8_t> parts = _fetch_content8(instr.args, ptr1, ptr2);
        uint16_t result = 0;
        result = ~(std::get<0>(parts) & std::get<1>(parts));
        if (result > UINT8_MAX) _ovr = true;
        else _ovr = false;
        _write_instruction_result(instr, ptr1, &result, 1);
    }
    else if (instr.size == b16){
        std::tuple<uint16_t, uint16_t> parts = _fetch_content16(instr.args, ptr1, ptr2);
        uint32_t result;
        result = ~(std::get<0>(parts) & std::get<1>(parts));
        if (result > UINT16_MAX) _ovr = true;
        else _ovr = false;
        _write_instruction_result(instr, ptr1, &result, 2);
    }
    else if (instr.size == b32){
        std::tuple<uint32_t, uint32_t> parts = _fetch_content32(instr.args, ptr1, ptr2);
        uint64_t result;
        result = ~(std::get<0>(parts) & std::get<1>(parts));
        if (result > UINT16_MAX) _ovr = true;
        else _ovr = false;
        _write_instruction_result(instr, ptr1, &result, 4);
    }
    else return 1;
    return 0;
}

void HyperCPU::CPU::_ins_clc_exec(void){
    _carry = false;
}

int HyperCPU::CPU::_ins_inc_exec(HyperCPU::_instruction_t &instr, void *ptr1) {
    if (instr.size == b8){
        uint8_t val = _fetch_fptr8(instr.args, ptr1);
        uint16_t result = 0;
        result = val;
        result++;
        if (result > UINT8_MAX) _ovr = true;
        else _ovr = false;
        printf("Pointer: %lX, hex in the location: %#010X\n", ptr1, *(uint32_t*)ptr1);
        _write_instruction_result(instr, ptr1, &result, 1);
    }
    else if (instr.size == b16){
        uint16_t val = _fetch_fptr16(instr.args, ptr1);
        uint32_t result;
        result = val;
        result++;
        if (result > UINT16_MAX) _ovr = true;
        else _ovr = false;
        _write_instruction_result(instr, ptr1, &result, 2);
    }
    else if (instr.size == b32){
        uint32_t val = _fetch_fptr32(instr.args, ptr1);
        uint64_t result;
        result = val;
        result++;
        if (result > UINT16_MAX) _ovr = true;
        else _ovr = false;
        _write_instruction_result(instr, ptr1, &result, 4);
    }
    else return 1;
    return 0;
}

int HyperCPU::CPU::_ins_dec_exec(HyperCPU::_instruction_t &instr, void *ptr1) {
    if (instr.size == b8){
        uint8_t val = _fetch_fptr8(instr.args, ptr1);
        uint16_t result = 0;
        result = val - 1;
        if (result > UINT8_MAX) _ovr = true;
        else _ovr = false;
        _write_instruction_result(instr, ptr1, &result, 1);
    }
    else if (instr.size == b16){
        uint16_t val = _fetch_fptr16(instr.args, ptr1);
        uint32_t result;
        result = val - 1;
        if (result > UINT16_MAX) _ovr = true;
        else _ovr = false;
        _write_instruction_result(instr, ptr1, &result, 2);
    }
    else if (instr.size == b32){
        uint32_t val = _fetch_fptr32(instr.args, ptr1);
        uint64_t result;
        result = val - 1;
        if (result > UINT16_MAX) _ovr = true;
        else _ovr = false;
        _write_instruction_result(instr, ptr1, &result, 4);
    }
    else return 1;
    return 0;
}

int HyperCPU::CPU::_ins_mov_exec(HyperCPU::_instruction_t &instr, void* ptr1, void* ptr2) {
    if (instr.size == b8){
        std::tuple<uint8_t, uint8_t> data = _fetch_content8(instr.args, ptr1, ptr2);
        uint8_t value = std::get<1>(data);
        _write_instruction_result(instr, ptr1, &value, 1);
    }
    else if (instr.size == b16){
        std::tuple<uint16_t, uint16_t> data = _fetch_content16(instr.args, ptr1, ptr2);
        uint16_t value = std::get<1>(data);
        _write_instruction_result(instr, ptr1, &value, 2);
    }
    else if (instr.size == b32){
        std::tuple<uint32_t, uint32_t> data = _fetch_content32(instr.args, ptr1, ptr2);
        uint32_t value = std::get<1>(data);
        _write_instruction_result(instr, ptr1, &value, 4);
    }
    else return 1;
    return 0;
}

void HyperCPU::CPU::_ins_call_exec(void *ptr1) {
    uint32_t addr = _fetch_dword();
    _push_dword(_insp);
    _insp = addr;
}

int HyperCPU::CPU::_ins_push_exec(HyperCPU::_instruction_t &instr, void *ptr1) {
    if (instr.size == b8){
        uint8_t data = _fetch_fptr8(instr.args, ptr1);
        _push_byte(data);
    } else if (instr.size == b16){
        uint16_t data = _fetch_fptr16(instr.args, ptr1);
        _push_word(data);
    } else if (instr.size == b32){
        uint32_t data = _fetch_fptr32(instr.args, ptr1);
        _push_dword(data);
    } else return 1;
    return 0;
}

int HyperCPU::CPU::_ins_pop_exec(HyperCPU::_instruction_t &instr, void *ptr1) {
    if (instr.size == b8){
        uint8_t data = _pop_byte();
        _write_instruction_result(instr, ptr1, &data, 1);
    } else if (instr.size == b16){
        uint16_t data = _pop_word();
        _write_instruction_result(instr, ptr1, &data, 2);
    } else if (instr.size == b32){
        uint32_t data = _pop_dword();
        _write_instruction_result(instr, ptr1, &data, 4);
    } else return 1;
    return 0;
}

int HyperCPU::CPU::_ins_cmp_exec(HyperCPU::_instruction_t &instr, void *ptr1, void *ptr2) {
    int64_t result = 0;

    if (instr.size == b8){
        std::tuple<uint8_t, uint8_t> data = _fetch_content8(instr.args, ptr1, ptr2);
        result = static_cast<int16_t>(std::get<0>(data)) - static_cast<int16_t>(std::get<1>(data));
    } else if (instr.size == b16){
        std::tuple<uint16_t, uint16_t> data = _fetch_content16(instr.args, ptr1, ptr2);
        result = static_cast<int32_t>(std::get<0>(data)) - static_cast<int32_t>(std::get<1>(data));
    } else if (instr.size == b32){
        std::tuple<uint32_t, uint32_t> data = _fetch_content32(instr.args, ptr1, ptr2);
        result = static_cast<int64_t>(std::get<0>(data)) - static_cast<int64_t>(std::get<1>(data));
    } else return 1;

    if (!result){_cmpr = true; _carry = false;}
    else if (result < 0){_cmpr = false; _carry = false;}
    else {_cmpr = false; _carry = true;}
    return 0;
}

int HyperCPU::CPU::_ins_bswp_exec(HyperCPU::_instruction_t &instr, void *ptr1){
    if (instr.size == b16){
        uint16_t data = _fetch_fptr16(instr.args, ptr1);
        data = std::byteswap(data);
        _write_instruction_result(instr, ptr1, &data, 2);
    } else if (instr.size == b32){
        uint32_t data = _fetch_fptr32(instr.args, ptr1);
        data = std::byteswap(data);
        _write_instruction_result(instr, ptr1, &data, 4);
    }
    else return 1;
    
    return 0;
}