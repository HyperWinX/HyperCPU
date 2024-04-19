#include <cpu.hpp>

int HyperCPU::CPU::_raise_fatal_exception(HyperCPU::_exception_t exception){
    switch (exception){
        case INVALID_OPCODE:
            
            break;
        default:
            return 1;
    }
}