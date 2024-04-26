#include <cpu.hpp>

int HyperCPU::CPU::is_access_allowed(uint32_t addr) {
  if (!gdt_initialized)
    return 1;

  unsigned int count = 0;
  unsigned int insp_index = 0;
  unsigned int addr_index = 0;
  gdt_table_t *gdt = reinterpret_cast<gdt_table_t *>(memoryptr + gdtr);
  gdt_entry_t *entries = reinterpret_cast<gdt_entry_t *>(memoryptr + gdt->base);

  if (gdt->length % sizeof(gdt_entry_t) != 0)
    raise_fatal_exception(GDT_READ_FAILURE);

  for (; insp_index < count; ++insp_index)
    if (reinterpret_cast<std::uintptr_t>(memoryptr + entries[insp_index].base) <
            addr &&
        reinterpret_cast<std::uintptr_t>(memoryptr + entries[insp_index].base +
                                         entries[insp_index].limit) > addr)
      break;
    else
      raise_fatal_exception(GDT_INVALID_ADDRESS);

  for (; addr_index < count; ++addr_index)
    if (reinterpret_cast<std::uintptr_t>(memoryptr + entries[addr_index].base) <
            addr &&
        reinterpret_cast<std::uintptr_t>(memoryptr + entries[addr_index].base +
                                         entries[addr_index].limit) > addr)
      break;
    else
      raise_fatal_exception(GDT_INVALID_ADDRESS);

  if (entries[insp_index].type == 0 || insp_index == addr_index)
    return 1;
  else
    return 0;
}