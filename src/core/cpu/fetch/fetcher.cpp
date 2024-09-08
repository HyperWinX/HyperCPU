#include <core/cpu/fetch/fetcher.hpp>
#include <core/memory_controller/i_memory_controller.hpp>


hypercpu::fetched_instruction hypercpu::fetcher::fetch() {
  fetched_instruction instr;
  instr.instruction = mem_controller->_fetch16(*ptr);
  instr.flags = mem_controller->_fetch8(*ptr);
  return instr;
}