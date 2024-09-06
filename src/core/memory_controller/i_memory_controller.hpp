#pragma once

#include <cstddef>
#include <cstdint>


namespace hypercpu {
  class i_memory_controller {
  public:
    virtual std::uint8_t _fetch8(std::size_t&) = 0;
    virtual std::uint16_t _fetch16(std::size_t&) = 0;
    virtual std::uint32_t _fetch32(std::size_t&) = 0;

    virtual void _load8(std::size_t&, std::uint8_t) = 0;
    virtual void _load16(std::size_t&, std::uint16_t) = 0;
    virtual void _load32(std::size_t&, std::uint32_t) = 0;
  };
}