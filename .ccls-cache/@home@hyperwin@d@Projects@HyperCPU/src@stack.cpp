#include <cpu.hpp>

void HyperCPU::CPU::_push_byte(uint8_t byte) {
    _memory[--_stp] = byte;
}

void HyperCPU::CPU::_push_word(uint16_t word) {
    _stp -= 2;
    *reinterpret_cast<uint16_t*>(&_memory[_stp]) = word;
}

void HyperCPU::CPU::_push_dword(uint32_t dword) {
    _stp -= 4;
    *reinterpret_cast<uint32_t*>(&_memory[_stp]) = dword;
}

uint8_t HyperCPU::CPU::_pop_byte() {
    return _memory[_stp++];
}

uint16_t HyperCPU::CPU::_pop_word() {
    return *reinterpret_cast<uint16_t*>(&_memory[(_stp += 2) - 2]);
}

uint32_t HyperCPU::CPU::_pop_dword() {
    return *reinterpret_cast<uint32_t*>(&_memory[(_stp += 4) - 4]);
}