#pragma once

#include <pch.hpp>

#include <Core/CPU/CPU.hpp>
#include <Core/CPU/Interrupts/ReservedInterrupts.hpp>
#include <Core/MemoryController/IMemoryController.hpp>


namespace HyperCPU {
  class MemoryControllerST final : public IMemoryController {
  private:
    char* memory;
    class CPU* cpu;
    std::size_t total_mem;

  public:
    explicit MemoryControllerST(std::size_t mem_size, class CPU* cpu = nullptr) : cpu(cpu), total_mem(mem_size) {
      memory = static_cast<char*>(calloc(total_mem, 1));
      if (!memory)
        throw std::runtime_error("Failed to allocate memory!");
    }
    inline std::uint8_t Fetch8(std::uint64_t& ptr) override {
      mem_ctlr_assert(ptr + sizeof(std::uint8_t) - 1 < total_mem);
      std::uint8_t data;
      memcpy(&data, &memory[ptr], sizeof(std::uint8_t));
      ptr += sizeof(std::uint8_t);
      return data;
    }

    inline std::uint16_t Fetch16(std::uint64_t& ptr) override {
      mem_ctlr_assert(ptr + sizeof(std::uint16_t) - 1 < total_mem);
      std::uint16_t data;
      memcpy(&data, &memory[ptr], sizeof(std::uint16_t));
      ptr += sizeof(std::uint16_t);
      return data;
    }

    inline std::uint32_t Fetch32(std::uint64_t& ptr) override {
      mem_ctlr_assert(ptr + sizeof(std::uint32_t) - 1 < total_mem);
      std::uint32_t data;
      memcpy(&data, &memory[ptr], sizeof(std::uint32_t));
      ptr += sizeof(std::uint32_t);
      return data;
    }

    inline std::uint64_t Fetch64(std::uint64_t& ptr) override {
      mem_ctlr_assert(ptr + sizeof(std::uint64_t) - 1 < total_mem);
      std::uint64_t data;
      memcpy(&data, &memory[ptr], sizeof(std::uint64_t));
      ptr += sizeof(std::uint64_t);
      return data;
    }

    inline std::uint8_t Read8(std::uint64_t ptr) override {
      mem_ctlr_assert(ptr + sizeof(std::uint8_t) - 1 < total_mem);
      std::uint8_t data;
      memcpy(&data, &memory[ptr], sizeof(std::uint8_t));
      return data;
    }

    inline std::uint16_t Read16(std::uint64_t ptr) override {
      mem_ctlr_assert(ptr + sizeof(std::uint16_t) - 1 < total_mem);
      std::uint16_t data;
      memcpy(&data, &memory[ptr], sizeof(std::uint16_t));
      return data;
    }

    inline std::uint32_t Read32(std::uint64_t ptr) override {
      mem_ctlr_assert(ptr + sizeof(std::uint32_t) - 1 < total_mem);
      std::uint32_t data;
      memcpy(&data, &memory[ptr], sizeof(std::uint32_t));
      return data;
    }

    inline std::uint64_t Read64(std::uint64_t ptr) override {
      mem_ctlr_assert(ptr + sizeof(std::uint64_t) - 1 < total_mem);
      std::uint64_t data;
      memcpy(&data, &memory[ptr], sizeof(std::uint64_t));
      return data;
    }

    inline void Load8(std::uint64_t ptr, std::uint8_t data) override {
      mem_ctlr_assert(ptr + sizeof(std::uint8_t) - 1 < total_mem);
      memcpy(&memory[ptr], &data, sizeof(std::uint8_t));
    }

    inline void Load16(std::uint64_t ptr, std::uint16_t data) override {
      mem_ctlr_assert(ptr + sizeof(std::uint16_t) - 1 < total_mem);
      memcpy(&memory[ptr], &data, sizeof(std::uint16_t));
    }

    inline void Load32(std::uint64_t ptr, std::uint32_t data) override {
      mem_ctlr_assert(ptr + sizeof(std::uint32_t) - 1 < total_mem);
      memcpy(&memory[ptr], &data, sizeof(std::uint32_t));
    }

    inline void Load64(std::uint64_t ptr, std::uint64_t data) override {
      mem_ctlr_assert(ptr + sizeof(std::uint64_t) - 1 < total_mem);
      memcpy(&memory[ptr], &data, sizeof(std::uint64_t));
    }

    std::uint8_t* get_ptr() const noexcept override { return reinterpret_cast<std::uint8_t*>(memory); }

    ~MemoryControllerST() {
      free(memory);
    }
  };
}
