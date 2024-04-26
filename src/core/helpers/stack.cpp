#include <cpu.hpp>

void HyperCPU::CPU::push_byte(uint8_t byte) {
    memoryptr[--stp] = byte;
}

void HyperCPU::CPU::push_word(uint16_t word) {
    stp -= 2;
    *reinterpret_cast<uint16_t*>(&memoryptr[stp]) = word;
}

void HyperCPU::CPU::push_dword(uint32_t dword) {
    stp -= 4;
    *reinterpret_cast<uint32_t*>(&memoryptr[stp]) = dword;
}

uint8_t HyperCPU::CPU::pop_byte() {
    return memoryptr[stp++];
}

uint16_t HyperCPU::CPU::pop_word() {
    return *reinterpret_cast<uint16_t*>(&memoryptr[(stp += 2) - 2]);
}

uint32_t HyperCPU::CPU::pop_dword() {
    return *reinterpret_cast<uint32_t*>(&memoryptr[(stp += 4) - 4]);
}