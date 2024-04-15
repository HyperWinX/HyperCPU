#include <cstdint>

inline uint8_t HyperCPU::CPU::rm_8(char* ptr){
    uint32_t addr;
    memcpy(&addr, ptr, 4);
    return _memory[addr];
}

inline uint16_t rHyperCPU::CPU::m_16(char* ptr){
    uint32_t addr;
    uint16_t v;
    memcpy(&addr, ptr, 4);
    memcpy(&v, _memory + addr, 2);
    return v;
}

inline uint32_t HyperCPU::CPU::rm_32(char* ptr){
    uint32_t addr, v;
    memcpy(&addr, ptr, 4);
    memcpy(&v, _memory + addr, 4);
    return v;
}

inline uint8_t HyperCPU::CPU::r_8(char* ptr){
    return *ptr;
}

inline uint16_t HyperCPU::CPU::r_16(char* ptr){
    uint16_t v;
    memcpy(&v, ptr, 2);
    return v;
}

inline uint32_t HyperCPU::CPU::r_32(char* ptr){
    uint32_t v;
    memcpy(&v, ptr, 4);
    return v;
}

inline uint8_t HyperCPU::CPU::m_8(char* ptr){
    return *ptr;
}

inline uint16_t HyperCPU::CPU::m_16(char* ptr){
    uint16_t v;
    memcpy(&v, ptr, 2);
    return v;
}

inline uint32_t HyperCPU::CPU::m_32(char* ptr){
    uint32_t v;
    memcpy(&v, ptr, 4);
    return v;
}

inline uint8_t HyperCPU::CPU::imm_8(char* ptr){
    return *ptr;
}

inline uint16_t HyperCPU::CPU::imm_16(char* ptr){
    uint16_t v;
    memcpy(&v, ptr, 2);
    return v;
}

inline uint32_t HyperCPU::CPU::imm_32(char* ptr){
    uint32_t v;
    memcpy(&v, ptr, 4);
    return v;
}

inline int HyperCPU::CPU::carry(void){
    return static_cast<int>(_carry);
}