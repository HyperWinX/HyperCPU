#pragma once

#include <stdexcept>
#include <mutex>

#include <cassert>
#include <cstring>

#include <core/memory_controller/i_memory_controller.hpp>

namespace hypercpu {
  class memory_controller_mt final : public i_memory_controller {
  private:
    char* memory;
    std::size_t total_mem;
    std::mutex mutex;
  
  public:
    explicit memory_controller_mt(std::size_t mem_size) : total_mem(mem_size) {
      memory  = static_cast<char*>(calloc(total_mem, 1));
      if (!memory)
        throw std::runtime_error("Failed to allocate memory!");
    }

    inline std::uint8_t fetch8(std::size_t& ptr) override {
      assert(ptr + sizeof(std::uint8_t) - 1 < total_mem);
      std::scoped_lock lock(mutex);
      std::uint8_t data;
      memcpy(&data, &memory[ptr], sizeof(std::uint8_t));
      ptr += sizeof(std::uint8_t);
      return data;
    }

    inline std::uint16_t fetch16(std::size_t& ptr) override {
      assert(ptr + sizeof(std::uint16_t) - 1 < total_mem);
      std::scoped_lock lock(mutex);
      std::uint16_t data;
      memcpy(&data, &memory[ptr], sizeof(std::uint16_t));
      ptr += sizeof(std::uint16_t);
      return data;
    }

    inline std::uint32_t fetch32(std::size_t& ptr) override {
      assert(ptr + sizeof(std::uint32_t) - 1 < total_mem);
      std::scoped_lock lock(mutex);
      std::uint32_t data;
      memcpy(&data, &memory[ptr], sizeof(std::uint32_t));
      ptr += sizeof(std::uint32_t);
      return data;
    }

    inline std::uint64_t fetch64(std::size_t& ptr) override {
      assert(ptr + sizeof(std::uint64_t) - 1 < total_mem);
      std::scoped_lock lock(mutex);
      std::uint64_t data;
      memcpy(&data, &memory[ptr], sizeof(std::uint64_t));
      ptr += sizeof(std::uint64_t);
      return data;
    }

    inline std::uint8_t read8(std::size_t& ptr) override {
      assert(ptr + sizeof(std::uint8_t) - 1 < total_mem);
      std::scoped_lock lock(mutex);
      std::uint8_t data;
      memcpy(&data, &memory[ptr], sizeof(std::uint8_t));
      return data;
    }

    inline std::uint16_t read16(std::size_t& ptr) override {
      assert(ptr + sizeof(std::uint16_t) - 1 < total_mem);
      std::scoped_lock lock(mutex);
      std::uint16_t data;
      memcpy(&data, &memory[ptr], sizeof(std::uint16_t));
      return data;
    }

    inline std::uint32_t read32(std::size_t& ptr) override {
      assert(ptr + sizeof(std::uint32_t) - 1 < total_mem);
      std::scoped_lock lock(mutex);
      std::uint32_t data;
      memcpy(&data, &memory[ptr], sizeof(std::uint32_t));
      return data;
    }

    inline std::uint64_t read64(std::size_t& ptr) override {
      assert(ptr + sizeof(std::uint64_t) - 1 < total_mem);
      std::scoped_lock lock(mutex);
      std::uint64_t data;
      memcpy(&data, &memory[ptr], sizeof(std::uint64_t));
      return data;
    }

    inline void load8(std::size_t& ptr, std::uint8_t data) override {
      assert(ptr + sizeof(std::uint8_t) - 1 < total_mem);
      std::scoped_lock lock(mutex);
      memcpy(&memory[ptr], &data, sizeof(std::uint8_t));
    }

    inline void load16(std::size_t& ptr, std::uint16_t data) override {
      assert(ptr + sizeof(std::uint16_t) - 1 < total_mem);
      std::scoped_lock lock(mutex);
      memcpy(&memory[ptr], &data, sizeof(std::uint16_t));
    }

    inline void load32(std::size_t& ptr, std::uint32_t data) override {
      assert(ptr + sizeof(std::uint32_t) - 1 < total_mem);
      std::scoped_lock lock(mutex);
      memcpy(&memory[ptr], &data, sizeof(std::uint32_t));
    }

    inline void load64(std::size_t& ptr, std::uint64_t data) override {
      assert(ptr + sizeof(std::uint64_t) - 1 < total_mem);
      std::scoped_lock lock(mutex);
      memcpy(&memory[ptr], &data, sizeof(std::uint64_t));
    }

    std::uint8_t* get_ptr() const noexcept override { return reinterpret_cast<uint8_t*>(memory); }

    ~memory_controller_mt() {
      free(memory);
    }
  };
}