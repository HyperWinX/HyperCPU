#pragma once

#include <oneapi/tbb/mutex.h>
#include <tbb/mutex.h>

#include <cstring>

#include <core/memory_controller/i_memory_controller.hpp>

namespace hypercpu {
  class memory_controller_st : i_memory_controller {
  private:
    char* memory;
    std::size_t total_mem;

  public:
    explicit memory_controller_st(std::size_t mem_size) : total_mem(mem_size) {
      memory = static_cast<char*>(malloc(total_mem));
      if (!memory)
        throw std::runtime_error("Failed to allocate memory!");
    }
    inline std::uint8_t _fetch8(std::size_t& ptr) override {
      std::uint8_t data;
      memcpy(&data, &memory[ptr], sizeof(std::uint8_t));
      ptr += sizeof(std::uint8_t);
      return data;
    }

    inline std::uint16_t _fetch16(std::size_t& ptr) override {
      std::uint16_t data;
      memcpy(&data, &memory[ptr], sizeof(std::uint16_t));
      ptr += sizeof(std::uint16_t);
      return data;
    }

    inline std::uint32_t _fetch32(std::size_t& ptr) override {
      std::uint32_t data;
      memcpy(&data, &memory[ptr], sizeof(std::uint32_t));
      ptr += sizeof(std::uint32_t);
      return data;
    }

    inline void _load8(std::size_t& ptr, std::uint8_t data) override {
      memcpy(&memory[ptr], &data, sizeof(std::uint8_t));
    }

    inline void _load16(std::size_t& ptr, std::uint16_t data) override {
      memcpy(&memory[ptr], &data, sizeof(std::uint16_t));
    }

    inline void _load32(std::size_t& ptr, std::uint32_t data) override {
      memcpy(&memory[ptr], &data, sizeof(std::uint32_t));
    }

    ~memory_controller_st() {
      free(memory);
    }
  };
}