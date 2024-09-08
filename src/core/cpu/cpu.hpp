#include <cstddef>

#include <core/cpu/fetch/fetcher.hpp>
#include <core/memory_controller/i_memory_controller.hpp>
#include <core/memory_controller/memory_controller_st.hpp>
#include <core/memory_controller/memory_controller_mt.hpp>


namespace hypercpu {
  class cpu {
  private:
    // Components
    i_memory_controller* mem_controller;
    fetcher fetcher;

    // Data
    std::size_t core_count;
    std::size_t total_mem;

    // Registers
    std::size_t rip;

    
  public:
    explicit inline cpu(std::size_t core_count, std::size_t mem_size) :
      mem_controller(core_count == 1 ?
        dynamic_cast<i_memory_controller*>(new memory_controller_st(mem_size)) : 
        dynamic_cast<i_memory_controller*>(new memory_controller_mt(mem_size))),
      fetcher(mem_controller, &rip),
      core_count(core_count),
      total_mem(mem_size) {}

    void run();
  };
}