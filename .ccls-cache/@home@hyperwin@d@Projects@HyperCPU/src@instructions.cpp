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

static uint8_t tmp8;
static uint16_t tmp16;
static uint32_t tmp32;

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
    switch (instr.args){
        case RM_R:
            if (instr.size == b8)
                RM_T(ptr1, uint8_t) = R_T(ptr2, uint8_t);
            else if (instr.size == b16)
                RM_T(ptr1, uint16_t) = R_T(ptr2, uint16_t);
            else if (instr.size == b32)
                RM_T(ptr1, uint32_t) = R_T(ptr2, uint32_t);
            else return 1;
            break;
        case R_RM:
            if (instr.size == b8)
                R_T(ptr1, uint8_t) = RM_T(ptr2, uint8_t);
            else if (instr.size == b16)
                R_T(ptr1, uint16_t) = RM_T(ptr2, uint16_t);
            else if (instr.size == b32)
                R_T(ptr1, uint32_t) = RM_T(ptr2, uint32_t);
            else return 1;
            break;
        case RM_IMM:
            if (instr.size == b8)
                RM_T(ptr1, uint8_t) = IMM_T(ptr2, uint8_t);
            else if (instr.size == b16)
                RM_T(ptr1, uint16_t) = IMM_T(ptr2, uint16_t);
            else if (instr.size == b32)
                RM_T(ptr1, uint32_t) = IMM_T(ptr2, uint32_t);
            else return 1;
            break;
        case R_IMM:
            if (instr.size == b8)
                R_T(ptr1, uint8_t) = IMM_T(ptr2, uint8_t);
            else if (instr.size == b16)
                R_T(ptr1, uint16_t) = IMM_T(ptr2, uint16_t);
            else if (instr.size == b32)
                R_T(ptr1, uint32_t) = IMM_T(ptr2, uint32_t);
            else return 1;
            break;
        case RM_M:
            if (instr.size == b8)
                RM_T(ptr1, uint8_t) = M_T(ptr2, uint8_t);
            else if (instr.size == b16)
                RM_T(ptr1, uint16_t) = M_T(ptr2, uint16_t);
            else if (instr.size == b32)
                RM_T(ptr1, uint32_t) = M_T(ptr2, uint32_t);
            else return 1;
            break;
        case R_M:
            if (instr.size == b8)
                R_T(ptr1, uint8_t) = M_T(ptr2, uint8_t);
            else if (instr.size == b16)
                R_T(ptr1, uint16_t) = M_T(ptr2, uint16_t);
            else if (instr.size == b32)
                R_T(ptr1, uint32_t) = M_T(ptr2, uint32_t);
            else return 1;
            break;
        case M_R:
            if (instr.size == b8)
                M_T(ptr1, uint8_t) = R_T(ptr2, uint8_t);
            else if (instr.size == b16)
                M_T(ptr1, uint16_t) = R_T(ptr2, uint16_t);
            else if (instr.size == b32)
                M_T(ptr1, uint32_t) = R_T(ptr2, uint32_t);
            else return 1;
            break;
        case M_RM:
            if (instr.size == b8)
                M_T(ptr1, uint8_t) = RM_T(ptr2, uint8_t);
            else if (instr.size == b16)
                M_T(ptr1, uint16_t) = RM_T(ptr2, uint16_t);
            else if (instr.size == b32)
                M_T(ptr1, uint32_t) = RM_T(ptr2, uint32_t);
            else return 1;
            break;
        default: return 1;
    }
    return 0;
}

void HyperCPU::CPU::_ins_call_exec(void *ptr1) {
    uint32_t addr = _fetch_dword();
    _push_dword(_insp);
    _insp = addr;
}

int HyperCPU::CPU::_ins_push_exec(HyperCPU::_instruction_t &instr, void *ptr1) {
    switch (instr.args){
        case R:
            if (instr.size == b8) _push_byte(*reinterpret_cast<uint8_t*>(ptr1));
            else if (instr.size == b16) _push_word(*reinterpret_cast<uint16_t*>(ptr1));
            else if (instr.size == b32) _push_dword(*reinterpret_cast<uint32_t*>(ptr1));
            else return 1;
            break;
        case IMM:
            if (instr.size == b8) _push_byte(*reinterpret_cast<uint8_t*>(ptr1));
            else if (instr.size == b16) _push_word(*reinterpret_cast<uint16_t*>(ptr1));
            else if (instr.size == b32) _push_dword(*reinterpret_cast<uint32_t*>(ptr1));
            else return 1;
            break;
        default: return 1;
    }
    return 0;
}

int HyperCPU::CPU::_ins_pop_exec(HyperCPU::_instruction_t &instr, void *ptr1) {
    switch (instr.args) {
        case R:
            if (instr.size == b8) R_T(ptr1, uint8_t) = _pop_byte();
            else if (instr.size == b16) R_T(ptr1, uint16_t) = _pop_word();
            else if (instr.size == b32) R_T(ptr1, uint32_t) = _pop_dword();
            else return 1;
            break;
        default: return 1;
    }
    return 0;
}

int HyperCPU::CPU::_ins_cmp_exec(HyperCPU::_instruction_t &instr, void *ptr1, void *ptr2) {
    int64_t result = 0;
    switch (instr.args){
        case R_R:
            if (instr.size == b8) result = R_T(ptr1, uint8_t) - R_T(ptr2, uint8_t);
            else if (instr.size == b16) result = R_T(ptr1, uint16_t) - R_T(ptr2, uint16_t);
            else if (instr.size == b32) result = R_T(ptr1, uint32_t) - R_T(ptr2, uint32_t);
            else return 1;
            break;
        case R_RM:
            if (instr.size == b8) result = R_T(ptr1, uint8_t) - RM_T(ptr2, uint8_t);
            else if (instr.size == b16) result = R_T(ptr1, uint16_t) - RM_T(ptr2, uint16_t);
            else if (instr.size == b32) result = R_T(ptr1, uint32_t) - RM_T(ptr2, uint32_t);
            else return 1;
            break;
        case R_IMM:
            if (instr.size == b8) result = R_T(ptr1, uint8_t) - IMM_T(ptr2, uint8_t);
            else if (instr.size == b16) result = R_T(ptr1, uint16_t) - IMM_T(ptr2, uint16_t);
            else if (instr.size == b32) result = R_T(ptr1, uint32_t) - IMM_T(ptr2, uint32_t);
            else return 1;
            break;
        default: printf("WTF is this mode code 0x%X", static_cast<int>(instr.args)); return 1;
    }
    std::cout << result << std::endl;
    if (!result){_cmpr = true; _carry = false;puts("0");}
    else if (result < 0){_cmpr = false; _carry = false;puts("<");}
    else {_cmpr = false; _carry = true;puts(">");}
    return 0;
}