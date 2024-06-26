#include <cstdint>
#include <cstring>
#include <cpu.hpp>
#include <tuple>

std::tuple<uint8_t, uint8_t> HyperCPU::CPU::fetch_content8(HyperCPU::argtp_t type, void *ptr1, void *ptr2){
    switch (type){
        case RM_R:  return std::make_tuple(rm_8(ptr1), r_8(ptr2));
        case R_RM:  return std::make_tuple(r_8(ptr1), rm_8(ptr2));
        case RM_IMM:return std::make_tuple(rm_8(ptr1), imm_8(ptr2));
        case R_IMM: return std::make_tuple(r_8(ptr1), imm_8(ptr2));
        case RM_M:  return std::make_tuple(rm_8(ptr1), m_8(ptr2));
        case R_M:   return std::make_tuple(r_8(ptr1), m_8(ptr2));
        case M_R:   return std::make_tuple(m_8(ptr1), r_8(ptr2));
        case M_RM:  return std::make_tuple(m_8(ptr1), rm_8(ptr2));
        case R_R:   return std::make_tuple(r_8(ptr1), r_8(ptr2));
        default: return {};
    }
}

std::tuple<uint16_t, uint16_t> HyperCPU::CPU::fetch_content16(HyperCPU::argtp_t type, void *ptr1, void *ptr2){
    switch (type){
        case RM_R:  return std::make_tuple(rm_16(ptr1), r_16(ptr2));
        case R_RM:  return std::make_tuple(r_16(ptr1), rm_16(ptr2));
        case RM_IMM:return std::make_tuple(rm_16(ptr1), imm_16(ptr2));
        case R_IMM: return std::make_tuple(r_16(ptr1), imm_16(ptr2));
        case RM_M:  return std::make_tuple(rm_16(ptr1), m_16(ptr2));
        case R_M:   return std::make_tuple(r_16(ptr1), m_16(ptr2));
        case M_R:   return std::make_tuple(m_16(ptr1), r_16(ptr2));
        case M_RM:  return std::make_tuple(m_16(ptr1), rm_16(ptr2));
        case R_R:   return std::make_tuple(r_16(ptr1), r_16(ptr2));
        default:    return {};
    }
}

std::tuple<uint32_t, uint32_t> HyperCPU::CPU::fetch_content32(HyperCPU::argtp_t type, void *ptr1, void *ptr2){
    switch (type){
        case RM_R:  return std::make_tuple(rm_32(ptr1), r_32(ptr2));
        case R_RM:  return std::make_tuple(r_32(ptr1), rm_32(ptr2));
        case RM_IMM:return std::make_tuple(rm_32(ptr1), imm_32(ptr2));
        case R_IMM: return std::make_tuple(r_32(ptr1), imm_32(ptr2));
        case RM_M:  return std::make_tuple(rm_32(ptr1), m_32(ptr2));
        case R_M:   return std::make_tuple(r_32(ptr1), m_32(ptr2));
        case M_R:   return std::make_tuple(m_32(ptr1), r_32(ptr2));
        case M_RM:  return std::make_tuple(m_32(ptr1), rm_32(ptr2));
        case R_R:   return std::make_tuple(r_32(ptr1), r_32(ptr2));
        default:    return {};
    }
    return {};
}

uint8_t HyperCPU::CPU::fetch_fptr8(HyperCPU::argtp_t type, void *ptr){
    switch (type){
        case R: return r_8(ptr);
        case M: return m_8(ptr);
        case IMM: return imm_8(ptr);
        default: return {};
    }
}

uint16_t HyperCPU::CPU::fetch_fptr16(HyperCPU::argtp_t type, void *ptr){
    switch (type){
        case R: return r_16(ptr);
        case M: return m_16(ptr);
        case IMM: return imm_16(ptr);
        default: return {};
    }
}

uint32_t HyperCPU::CPU::fetch_fptr32(HyperCPU::argtp_t type, void *ptr){
    switch (type){
        case R: return r_32(ptr);
        case M: return m_32(ptr);
        case IMM: return imm_32(ptr);
        default: return {};
    }
}

inline uint8_t HyperCPU::CPU::rm_8(void* ptr){
    uint32_t addr;
    memcpy(&addr, ptr, 4);
    return memoryptr[addr];
}

inline uint16_t HyperCPU::CPU::rm_16(void* ptr){
    uint32_t addr;
    uint16_t v;
    memcpy(&addr, ptr, 4);
    memcpy(&v, memoryptr + addr, 2);
    return v;
}

inline uint32_t HyperCPU::CPU::rm_32(void* ptr){
    uint32_t addr, v;
    memcpy(&addr, ptr, 4);
    memcpy(&v, memoryptr + addr, 4);
    return v;
}

inline uint8_t HyperCPU::CPU::r_8(void* ptr){
    uint8_t v;
    memcpy(&v, ptr, 1);
    return v;
}

inline uint16_t HyperCPU::CPU::r_16(void* ptr){
    uint16_t v;
    memcpy(&v, ptr, 2);
    return v;
}

inline uint32_t HyperCPU::CPU::r_32(void* ptr){
    uint32_t v;
    memcpy(&v, ptr, 4);
    return v;
}

inline uint8_t HyperCPU::CPU::m_8(void* ptr){
    uint8_t v;
    memcpy(&v, ptr, 1);
    return v;
}

inline uint16_t HyperCPU::CPU::m_16(void* ptr){
    uint16_t v;
    memcpy(&v, ptr, 2);
    return v;
}

inline uint32_t HyperCPU::CPU::m_32(void* ptr){
    uint32_t v;
    memcpy(&v, ptr, 4);
    return v;
}

inline uint8_t HyperCPU::CPU::imm_8(void* ptr){
    uint8_t v;
    memcpy(&v, ptr, 1);
    return v;
}

inline uint16_t HyperCPU::CPU::imm_16(void* ptr){
    uint16_t v;
    memcpy(&v, ptr, 2);
    return v;
}

inline uint32_t HyperCPU::CPU::imm_32(void* ptr){
    uint32_t v;
    memcpy(&v, ptr, 4);
    return v;
}

int HyperCPU::CPU::carry(void){
    return static_cast<int>(carry_flag);
}

int HyperCPU::CPU::write_instruction_result(HyperCPU::instruction_t &instr, void *dst, void *src, int length){
    switch(instr.args){
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough" 
        case M:
        case M_R:
        case M_RM:{
            if (!is_access_allowed(static_cast<uint32_t>((char*)dst - memoryptr)))
                raise_exception_interrupt(SEGMENTATION_FAULT);
        }
#pragma GCC diagnostic pop
        case R_M:
        case R_R:
        case R_RM:
        case R_IMM:
        case R:
            memcpy(dst, src, length);
            break;
        case RM_M:
        case RM_R:
        case RM_IMM:{
            uint32_t addr;
            memcpy(&addr, dst, 4);
            if (!is_access_allowed(addr))
                raise_exception_interrupt(SEGMENTATION_FAULT);
            memcpy(memoryptr + addr, src, length);
            break;
        }
        default: return 1;
    }
    return 0;
}