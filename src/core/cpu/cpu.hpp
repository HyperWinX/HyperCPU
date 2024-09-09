#pragma once

#include <cstddef>

#include <core/memory_controller/i_memory_controller.hpp>
#include <core/memory_controller/memory_controller_st.hpp>
#include <core/memory_controller/memory_controller_mt.hpp>


namespace hypercpu {
  class cpu {
  private:
    // Components
    i_memory_controller* mem_controller;

    // Data
    std::size_t core_count;
    std::size_t total_mem;

    // General space for registers
    std::uint64_t data[13];

    // GP Registers
    std::uint64_t *x0, *x1, *x2, *x3, *x4, *x5, *x6, *x7;
    std::uint32_t *xh0, *xh1, *xh2, *xh3, *xh4, *xh5, *xh6, *xh7;
    std::uint32_t *xl0, *xl1,* xl2, *xl3, *xl4, *xl5, *xl6, *xl7;
    std::uint16_t *xll0, *xll1, *xll2, *xll3;
    std::uint8_t *xllh0, *xllh1, *xllh2, *xllh3;
    std::uint8_t *xlll0, *xlll1, *xlll2, *xlll3;

    // Specific registers
    std::uint64_t *xbp, *xsp, *xip, *xgdp, *xidp;
    
  public:
    explicit inline cpu(std::size_t core_count, std::size_t mem_size) :
      mem_controller(core_count == 1 ?
        dynamic_cast<i_memory_controller*>(new memory_controller_st(mem_size)) : 
        dynamic_cast<i_memory_controller*>(new memory_controller_mt(mem_size))),
      core_count(core_count),
      total_mem(mem_size) {
        // Initializing all register pointers
        x0 = &data[0];
        x1 = &data[1];
        x2 = &data[2];
        x3 = &data[3];
        x4 = &data[4];
        x5 = &data[5];
        x6 = &data[6];
        x7 = &data[7];

        xh0 = reinterpret_cast<std::uint32_t*>(&data[0]);
        xh1 = reinterpret_cast<std::uint32_t*>(&data[1]);
        xh2 = reinterpret_cast<std::uint32_t*>(&data[2]);
        xh3 = reinterpret_cast<std::uint32_t*>(&data[3]);
        xh4 = reinterpret_cast<std::uint32_t*>(&data[4]);
        xh5 = reinterpret_cast<std::uint32_t*>(&data[5]);
        xh6 = reinterpret_cast<std::uint32_t*>(&data[6]);
        xh7 = reinterpret_cast<std::uint32_t*>(&data[7]);

        xl0 = reinterpret_cast<std::uint32_t*>(&data[0]) + 1;
        xl1 = reinterpret_cast<std::uint32_t*>(&data[1]) + 1;
        xl2 = reinterpret_cast<std::uint32_t*>(&data[2]) + 1;
        xl3 = reinterpret_cast<std::uint32_t*>(&data[3]) + 1;
        xl4 = reinterpret_cast<std::uint32_t*>(&data[4]) + 1;
        xl5 = reinterpret_cast<std::uint32_t*>(&data[5]) + 1;
        xl6 = reinterpret_cast<std::uint32_t*>(&data[6]) + 1;
        xl7 = reinterpret_cast<std::uint32_t*>(&data[7]) + 1;

        xll0 = reinterpret_cast<std::uint16_t*>(&data[0]) + 3;
        xll1 = reinterpret_cast<std::uint16_t*>(&data[1]) + 3;
        xll2 = reinterpret_cast<std::uint16_t*>(&data[2]) + 3;
        xll3 = reinterpret_cast<std::uint16_t*>(&data[3]) + 3;

        xllh0 = reinterpret_cast<std::uint8_t*>(&data[0]) + 6;
        xllh1 = reinterpret_cast<std::uint8_t*>(&data[1]) + 6;
        xllh2 = reinterpret_cast<std::uint8_t*>(&data[2]) + 6;
        xllh3 = reinterpret_cast<std::uint8_t*>(&data[3]) + 6;

        xlll0 = reinterpret_cast<std::uint8_t*>(&data[0]) + 7;
        xlll1 = reinterpret_cast<std::uint8_t*>(&data[1]) + 7;
        xlll2 = reinterpret_cast<std::uint8_t*>(&data[2]) + 7;
        xlll3 = reinterpret_cast<std::uint8_t*>(&data[3]) + 7;

        xbp = &data[8];
        xsp = &data[9];
        xip = &data[10];
        xgdp = &data[11];
        xidp = &data[12];
      }

    void run();
  };
}