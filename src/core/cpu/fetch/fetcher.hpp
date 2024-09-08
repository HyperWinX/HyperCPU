#include <core/memory_controller/i_memory_controller.hpp>
#include <core/cpu/fetch/i_fetcher.hpp>


namespace hypercpu {
  class fetcher : public i_fetcher {
  private:
    i_memory_controller* mem_controller;
    std::size_t* ptr;
  
  public:
    explicit fetcher(i_memory_controller* mc, std::size_t* ptr) : mem_controller(mc), ptr(ptr) {}

    fetched_instruction fetch() override;
  };
}