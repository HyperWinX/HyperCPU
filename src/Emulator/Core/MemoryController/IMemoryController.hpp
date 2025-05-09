#pragma once

#include <spdlog/spdlog.h>

#include "PCH/CStd.hpp"

// TODO: позор партии, убрать и переделать в функцию
#define mem_ctlr_assert(expr)                                             \
  do {                                                                    \
    if (!(expr) && (!cpu || !cpu->CanExecuteInterrupts())) [[unlikely]] { \
      spdlog::error("Assertion failed: {}", #expr);                       \
      std::abort();                                                       \
    } else if (!(expr) && cpu && cpu->CanExecuteInterrupts()) {           \
      cpu->TriggerInterrupt(HyperCPU::cpu_exceptions::SEGF);              \
    } else [[likely]] {                                                   \
    }                                                                     \
  } while (false)

namespace HyperCPU {
  class IMemoryController {
  public:
    virtual std::uint8_t Fetch8(std::uint64_t&) = 0;
    virtual std::uint16_t Fetch16(std::uint64_t&) = 0;
    virtual std::uint32_t Fetch32(std::uint64_t&) = 0;
    virtual std::uint64_t Fetch64(std::uint64_t&) = 0;

    virtual std::uint8_t Read8(std::uint64_t) = 0;
    virtual std::uint16_t Read16(std::uint64_t) = 0;
    virtual std::uint32_t Read32(std::uint64_t) = 0;
    virtual std::uint64_t Read64(std::uint64_t) = 0;

    template<typename T>
    void Load8(std::uint64_t, T);
    template<typename T>
    void Load16(std::uint64_t, T);
    template<typename T>
    void Load32(std::uint64_t, T);
    template<typename T>
    void Load64(std::uint64_t, T);

    virtual std::uint8_t* get_ptr() const noexcept = 0;
    virtual ~IMemoryController() = default;

  protected:
    virtual void load8(std::uint64_t, std::uint8_t) = 0;
    virtual void load16(std::uint64_t, std::uint16_t) = 0;
    virtual void load32(std::uint64_t, std::uint32_t) = 0;
    virtual void load64(std::uint64_t, std::uint64_t) = 0;
  };

} // namespace HyperCPU

template<typename T>
void HyperCPU::IMemoryController::Load8(std::uint64_t address, T value) {
    using ActualFrom = std::conditional_t<std::is_enum_v<T>, std::underlying_type_t<T>, T>;
    static_assert(std::is_convertible_v<ActualFrom, std::uint8_t>, "Value must be convertable to integer type");

    load8(address, static_cast<std::uint8_t>(value));
}

template<typename T>
void HyperCPU::IMemoryController::Load16(std::uint64_t address, T value) {
    using ActualFrom = std::conditional_t<std::is_enum_v<T>, std::underlying_type_t<T>, T>;
    static_assert(std::is_convertible_v<ActualFrom, std::uint16_t>, "Value must be convertable to integer type");

    load16(address, static_cast<std::uint16_t>(value));
}

template<typename T>
void HyperCPU::IMemoryController::Load32(std::uint64_t address, T value) {
    using ActualFrom = std::conditional_t<std::is_enum_v<T>, std::underlying_type_t<T>, T>;
    static_assert(std::is_convertible_v<ActualFrom, std::uint32_t>, "Value must be convertable to integer type");

    load32(address, static_cast<std::uint32_t>(value));
}

template<typename T>
void HyperCPU::IMemoryController::Load64(std::uint64_t address, T value) {
    using ActualFrom = std::conditional_t<std::is_enum_v<T>, std::underlying_type_t<T>, T>;
    static_assert(std::is_convertible_v<ActualFrom, std::uint64_t>, "Value must be convertable to integer type");

    load64(address, static_cast<std::uint64_t>(value));
}
