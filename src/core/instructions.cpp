#include <cpu.hpp>

#include <cstdio>
#include <cstring>
#include <cstdint>

#include <iostream>
#include <functional>

#define RM_T(ptr, type) (*reinterpret_cast<type*>(memoryptr + *reinterpret_cast<uint32_t*>(ptr)))
#define R_T(ptr, type) (*reinterpret_cast<type*>(ptr))
#define M_T(ptr, type) (*reinterpret_cast<type*>(ptr))
#define IMM_T(ptr, type) (*reinterpret_cast<type*>(ptr))
#define CARRY_T() (static_cast<int>(carry_flag))
int HyperCPU::CPU::ins_adc_exec(HyperCPU::instruction_t &instr, void* ptr1, void* ptr2) {
    if (!verify_operand_types(instr)){
#ifndef INTERRUPTS_ENABLED
        return 1;
#else
        raise_exception_interrupt(INVALID_OPCODE);
        return 0;
#endif
    }
    if (instr.size == b8){
        std::tuple<uint8_t, uint8_t> parts = fetch_content8(instr.args, ptr1, ptr2);
        uint16_t result = 0;
        result = std::get<0>(parts) + std::get<1>(parts) + carry();
        if (result > UINT8_MAX) ovr = true;
        else ovr = false;
        write_instruction_result(instr, ptr1, &result, 1);
    }
    else if (instr.size == b16){
        std::tuple<uint16_t, uint16_t> parts = fetch_content16(instr.args, ptr1, ptr2);
        uint32_t result;
        result = std::get<0>(parts) + std::get<1>(parts) + carry();
        if (result > UINT16_MAX) ovr = true;
        else ovr = false;
        write_instruction_result(instr, ptr1, &result, 2);
    }
    else if (instr.size == b32){
        std::tuple<uint32_t, uint32_t> parts = fetch_content32(instr.args, ptr1, ptr2);
        uint64_t result;
        result = std::get<0>(parts) + std::get<1>(parts) + carry();
        if (result > UINT32_MAX) ovr = true;
        else ovr = false;
        write_instruction_result(instr, ptr1, &result, 4);
    }
    else return 1;
    return 0;
}

int HyperCPU::CPU::ins_add_exec(HyperCPU::instruction_t &instr, void* ptr1, void* ptr2) {
    if (!verify_operand_types(instr)){
#ifndef INTERRUPTS_ENABLED
        return 1;
#else
        raise_exception_interrupt(INVALID_OPCODE);
        return 0;
#endif
    }
    if (instr.size == b8){
        std::tuple<uint8_t, uint8_t> parts = fetch_content8(instr.args, ptr1, ptr2);
        uint16_t result = 0;
        result = std::get<0>(parts) + std::get<1>(parts);
        if (result > UINT8_MAX) ovr = true;
        else ovr = false;
        write_instruction_result(instr, ptr1, &result, 1);
    }
    else if (instr.size == b16){
        std::tuple<uint16_t, uint16_t> parts = fetch_content16(instr.args, ptr1, ptr2);
        uint32_t result;
        result = std::get<0>(parts) + std::get<1>(parts);
        if (result > UINT16_MAX) ovr = true;
        else ovr = false;
        write_instruction_result(instr, ptr1, &result, 2);
    }
    else if (instr.size == b32){
        std::tuple<uint32_t, uint32_t> parts = fetch_content32(instr.args, ptr1, ptr2);
        uint64_t result;
        result = std::get<0>(parts) + std::get<1>(parts);
        if (result > UINT32_MAX) ovr = true;
        else ovr = false;
        write_instruction_result(instr, ptr1, &result, 4);
    }
    else return 1;
    return 0;
}

int HyperCPU::CPU::ins_and_exec(HyperCPU::instruction_t &instr, void* ptr1, void* ptr2) {
    if (!verify_operand_types(instr)){
#ifndef INTERRUPTS_ENABLED
        return 1;
#else
        raise_exception_interrupt(INVALID_OPCODE);
        return 0;
#endif
    }
    if (instr.size == b8){
        std::tuple<uint8_t, uint8_t> parts = fetch_content8(instr.args, ptr1, ptr2);
        uint16_t result = 0;
        result = std::get<0>(parts) & std::get<1>(parts);
        if (result > UINT8_MAX) ovr = true;
        else ovr = false;
        write_instruction_result(instr, ptr1, &result, 1);
    }
    else if (instr.size == b16){
        std::tuple<uint16_t, uint16_t> parts = fetch_content16(instr.args, ptr1, ptr2);
        uint32_t result;
        result = std::get<0>(parts) & std::get<1>(parts);
        if (result > UINT16_MAX) ovr = true;
        else ovr = false;
        write_instruction_result(instr, ptr1, &result, 2);
    }
    else if (instr.size == b32){
        std::tuple<uint32_t, uint32_t> parts = fetch_content32(instr.args, ptr1, ptr2);
        uint64_t result;
        result = std::get<0>(parts) & std::get<1>(parts);
        if (result > UINT32_MAX) ovr = true;
        else ovr = false;
        write_instruction_result(instr, ptr1, &result, 4);
    }
    else return 1;
    return 0;
}

int HyperCPU::CPU::ins_andn_exec(HyperCPU::instruction_t &instr, void* ptr1, void* ptr2) {
    if (!verify_operand_types(instr)){
#ifndef INTERRUPTS_ENABLED
        return 1;
#else
        raise_exception_interrupt(INVALID_OPCODE);
        return 0;
#endif
    }
    if (instr.size == b8){
        std::tuple<uint8_t, uint8_t> parts = fetch_content8(instr.args, ptr1, ptr2);
        uint16_t result = 0;
        result = ~(std::get<0>(parts) & std::get<1>(parts));
        if (result > UINT8_MAX) ovr = true;
        else ovr = false;
        write_instruction_result(instr, ptr1, &result, 1);
    }
    else if (instr.size == b16){
        std::tuple<uint16_t, uint16_t> parts = fetch_content16(instr.args, ptr1, ptr2);
        uint32_t result;
        result = ~(std::get<0>(parts) & std::get<1>(parts));
        if (result > UINT16_MAX) ovr = true;
        else ovr = false;
        write_instruction_result(instr, ptr1, &result, 2);
    }
    else if (instr.size == b32){
        std::tuple<uint32_t, uint32_t> parts = fetch_content32(instr.args, ptr1, ptr2);
        uint64_t result;
        result = ~(std::get<0>(parts) & std::get<1>(parts));
        if (result > UINT16_MAX) ovr = true;
        else ovr = false;
        write_instruction_result(instr, ptr1, &result, 4);
    }
    else return 1;
    return 0;
}

void HyperCPU::CPU::ins_clc_exec(void){
    carry_flag = false;
}

int HyperCPU::CPU::ins_inc_exec(HyperCPU::instruction_t &instr, void *ptr1) {
    if (!verify_operand_types(instr)){
#ifndef INTERRUPTS_ENABLED
        return 1;
#else
        raise_exception_interrupt(INVALID_OPCODE);
        return 0;
#endif
    }
    if (instr.size == b8){
        uint8_t val = fetch_fptr8(instr.args, ptr1);
        uint16_t result = 0;
        result = val;
        result++;
        if (result > UINT8_MAX) ovr = true;
        else ovr = false;
        write_instruction_result(instr, ptr1, &result, 1);
    }
    else if (instr.size == b16){
        uint16_t val = fetch_fptr16(instr.args, ptr1);
        uint32_t result;
        result = val;
        result++;
        if (result > UINT16_MAX) ovr = true;
        else ovr = false;
        write_instruction_result(instr, ptr1, &result, 2);
    }
    else if (instr.size == b32){
        uint32_t val = fetch_fptr32(instr.args, ptr1);
        uint64_t result;
        result = val;
        result++;
        if (result > UINT16_MAX) ovr = true;
        else ovr = false;
        write_instruction_result(instr, ptr1, &result, 4);
    }
    else return 1;
    return 0;
}

int HyperCPU::CPU::ins_dec_exec(HyperCPU::instruction_t &instr, void *ptr1) {
    if (!verify_operand_types(instr)){
#ifndef INTERRUPTS_ENABLED
        return 1;
#else
        raise_exception_interrupt(INVALID_OPCODE);
        return 0;
#endif
    }
    if (instr.size == b8){
        uint8_t val = fetch_fptr8(instr.args, ptr1);
        uint16_t result = 0;
        result = val - 1;
        if (result > UINT8_MAX) ovr = true;
        else ovr = false;
        write_instruction_result(instr, ptr1, &result, 1);
    }
    else if (instr.size == b16){
        uint16_t val = fetch_fptr16(instr.args, ptr1);
        uint32_t result;
        result = val - 1;
        if (result > UINT16_MAX) ovr = true;
        else ovr = false;
        write_instruction_result(instr, ptr1, &result, 2);
    }
    else if (instr.size == b32){
        uint32_t val = fetch_fptr32(instr.args, ptr1);
        uint64_t result;
        result = val - 1;
        if (result > UINT16_MAX) ovr = true;
        else ovr = false;
        write_instruction_result(instr, ptr1, &result, 4);
    }
    else return 1;
    return 0;
}

int HyperCPU::CPU::ins_mov_exec(HyperCPU::instruction_t &instr, void* ptr1, void* ptr2) {
    if (!verify_operand_types(instr)){
#ifndef INTERRUPTS_ENABLED
        return 1;
#else
        raise_exception_interrupt(INVALID_OPCODE);
        return 0;
#endif
    }
    if (instr.size == b8){
        std::tuple<uint8_t, uint8_t> data = fetch_content8(instr.args, ptr1, ptr2);
        uint8_t value = std::get<1>(data);
        write_instruction_result(instr, ptr1, &value, 1);
    }
    else if (instr.size == b16){
        std::tuple<uint16_t, uint16_t> data = fetch_content16(instr.args, ptr1, ptr2);
        uint16_t value = std::get<1>(data);
        write_instruction_result(instr, ptr1, &value, 2);
    }
    else if (instr.size == b32){
        std::tuple<uint32_t, uint32_t> data = fetch_content32(instr.args, ptr1, ptr2);
        uint32_t value = std::get<1>(data);
        write_instruction_result(instr, ptr1, &value, 4);
    }
    else return 1;
    return 0;
}

int HyperCPU::CPU::ins_call_exec(HyperCPU::instruction_t &instr) {
    if (!verify_operand_types(instr)){
#ifndef INTERRUPTS_ENABLED
        return 1;
#else
        raise_exception_interrupt(INVALID_OPCODE);
        return 0;
#endif
    }
    uint32_t addr = fetch_dword();
    push_dword(insp);
    insp = addr;
    return 0;
}

int HyperCPU::CPU::ins_push_exec(HyperCPU::instruction_t &instr, void *ptr1) {
    if (!verify_operand_types(instr)){
#ifndef INTERRUPTS_ENABLED
        return 1;
#else
        raise_exception_interrupt(INVALID_OPCODE);
        return 0;
#endif
    }
    if (instr.size == b8){
        uint8_t data = fetch_fptr8(instr.args, ptr1);
        push_byte(data);
    } else if (instr.size == b16){
        uint16_t data = fetch_fptr16(instr.args, ptr1);
        push_word(data);
    } else if (instr.size == b32){
        uint32_t data = fetch_fptr32(instr.args, ptr1);
        push_dword(data);
    } else return 1;
    return 0;
}

int HyperCPU::CPU::ins_pop_exec(HyperCPU::instruction_t &instr, void *ptr1) {
    if (!verify_operand_types(instr)){
#ifndef INTERRUPTS_ENABLED
        return 1;
#else
        raise_exception_interrupt(INVALID_OPCODE);
        return 0;
#endif
    }
    if (instr.size == b8){
        uint8_t data = pop_byte();
        write_instruction_result(instr, ptr1, &data, 1);
    } else if (instr.size == b16){
        uint16_t data = pop_word();
        write_instruction_result(instr, ptr1, &data, 2);
    } else if (instr.size == b32){
        uint32_t data = pop_dword();
        write_instruction_result(instr, ptr1, &data, 4);
    } else return 1;
    return 0;
}

int HyperCPU::CPU::ins_cmp_exec(HyperCPU::instruction_t &instr, void *ptr1, void *ptr2) {
    if (!verify_operand_types(instr)){
#ifndef INTERRUPTS_ENABLED
        return 1;
#else
        raise_exception_interrupt(INVALID_OPCODE);
        return 0;
#endif
    }

    int64_t result = 0;

    if (instr.size == b8){
        std::tuple<uint8_t, uint8_t> data = fetch_content8(instr.args, ptr1, ptr2);
        result = static_cast<int16_t>(std::get<0>(data)) - static_cast<int16_t>(std::get<1>(data));
    } else if (instr.size == b16){
        std::tuple<uint16_t, uint16_t> data = fetch_content16(instr.args, ptr1, ptr2);
        result = static_cast<int32_t>(std::get<0>(data)) - static_cast<int32_t>(std::get<1>(data));
    } else if (instr.size == b32){
        std::tuple<uint32_t, uint32_t> data = fetch_content32(instr.args, ptr1, ptr2);
        result = static_cast<int64_t>(std::get<0>(data)) - static_cast<int64_t>(std::get<1>(data));
    } else return 1;

    if (!result){cmpr = true; carry_flag = false;}
    else if (result < 0){cmpr = false; carry_flag = false;}
    else {cmpr = false; carry_flag = true;}
    return 0;
}

int HyperCPU::CPU::ins_bswp_exec(HyperCPU::instruction_t &instr, void *ptr1){
    if (!verify_operand_types(instr)){
#ifndef INTERRUPTS_ENABLED
        return 1;
#else
        raise_exception_interrupt(INVALID_OPCODE);
        return 0;
#endif
    }
    if (instr.size == b16){
        uint16_t data = fetch_fptr16(instr.args, ptr1);
        data = std::byteswap(data);
        write_instruction_result(instr, ptr1, &data, 2);
    } else if (instr.size == b32){
        uint32_t data = fetch_fptr32(instr.args, ptr1);
        data = std::byteswap(data);
        write_instruction_result(instr, ptr1, &data, 4);
    }
    else return 1;
    
    return 0;
}