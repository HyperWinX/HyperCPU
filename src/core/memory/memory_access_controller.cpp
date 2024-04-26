#include <cpu.hpp>

#include <cstring>

void HyperCPU::CPU::writememoryptr(uint32_t addr, void *ptr, int length){
    if (is_access_allowed(addr)) raise_exception_interrupt(SEGMENTATION_FAULT);

    memcpy(memoryptr + addr, ptr, length);
}