#include <cpu.hpp>

#include <cstring>

void HyperCPU::CPU::_write_memory(uint32_t addr, void *ptr, int length){
    if (!_is_access_allowed(addr)) _raise_exception_interrupt(SEGMENTATION_FAULT);

    memcpy(_memory + addr, ptr, length);
}