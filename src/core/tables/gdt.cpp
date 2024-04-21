#include <cpu.hpp>

int HyperCPU::CPU::_is_access_allowed(uint32_t addr){
    if (!_gdt_init) return 1;

    unsigned int count = 0;
    unsigned int insp_index = 0;
    unsigned int addr_index = 0;
    _gdt_table_t* gdt = reinterpret_cast<_gdt_table_t*>(_memory + _gdtr);
    _gdt_entry_t* entries = reinterpret_cast<_gdt_entry_t*>(_memory + gdt->base);

    if (gdt->length % sizeof(_gdt_entry_t) != 0) _raise_fatal_exception(GDT_READ_FAILURE);
    
    for (; insp_index < count; ++insp_index)
        if (reinterpret_cast<std::uintptr_t>(_memory + entries[insp_index].base) < addr &&
            reinterpret_cast<std::uintptr_t>(_memory + entries[insp_index].base + entries[insp_index].limit) > addr)
            break;
    else _raise_fatal_exception(GDT_INVALID_ADDRESS);

    for (; addr_index < count; ++addr_index)
        if (reinterpret_cast<std::uintptr_t>(_memory + entries[addr_index].base) < addr &&
            reinterpret_cast<std::uintptr_t>(_memory + entries[addr_index].base + entries[addr_index].limit) > addr)
            break;
    else _raise_fatal_exception(GDT_INVALID_ADDRESS);

    if (entries[insp_index].type == 0 ||
        insp_index == addr_index)
        return 1;
    else return 0;
}