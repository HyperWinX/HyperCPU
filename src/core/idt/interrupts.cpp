#include <cpu.hpp>

#include <cstdlib>
#include <cstdio>

void HyperCPU::CPU::raise_exception_interrupt(HyperCPU::exception_t exception){
    switch(exception){
        case SEGMENTATION_FAULT:
            puts("VM segmentation fault has been detected");
            break;
        case INVALID_OPCODE:
            puts("INVALID OPCODE!");
            break;
        default: break;
    }
    CleanUp();
    exit(1);
}