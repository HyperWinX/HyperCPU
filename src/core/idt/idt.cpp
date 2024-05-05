#include <cpu.hpp>

static uint8_t exception_depth = 0;

void HyperCPU::CPU::execute_IDT_entry(uint8_t entry){
    if (entry < 17){
        if (exception_depth == 3)
            raise_fatal_exception(TRIPLE_FAULT);
        else ++exception_depth;
    }
    void** idt = reinterpret_cast<void**>(idtr);
    push_dword(insp);
    insp = reinterpret_cast<std::uintptr_t>(idt[entry]);
}