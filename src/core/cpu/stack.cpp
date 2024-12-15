#include <core/cpu/assert.hpp>
#include <core/cpu/cpu.hpp>


void hypercpu::cpu::stack_push8(std::uint8_t val) noexcept {
  h_assert(*xsp > 1, "Stack pointer too low!");

  *xsp -= 1;
  mem_controller->load8(*xsp, val);
}

void hypercpu::cpu::stack_push16(std::uint16_t val) noexcept {
  h_assert(*xsp > 2, "Stack pointer too low!");

  *xsp -= 2;
  mem_controller->load16(*xsp, val);
}

void hypercpu::cpu::stack_push32(std::uint32_t val) noexcept {
  h_assert(*xsp > 4, "Stack pointer too low!");

  *xsp -= 4;
  mem_controller->load32(*xsp, val);
}

void hypercpu::cpu::stack_push64(std::uint64_t val) noexcept {
  h_assert(*xsp > 8, "Stack pointer too low!");

  *xsp -= 8;
  mem_controller->load64(*xsp, val);
}

std::uint8_t hypercpu::cpu::stack_pop8() noexcept {
  h_assert((*xsp + 1) <= *xbp, "Stack pointer too high!");

  std::uint8_t val = mem_controller->read8(*xsp);
  *xsp += 1;
  return val;
}

std::uint16_t hypercpu::cpu::stack_pop16() noexcept {
  h_assert((*xsp + 2) <= *xbp, "Stack pointer too high!");

  std::uint16_t val = mem_controller->read16(*xsp);
  *xsp += 2;
  return val;
}

std::uint32_t hypercpu::cpu::stack_pop32() noexcept {
  h_assert((*xsp + 4) <= *xbp, "Stack pointer too high!");

  std::uint32_t val = mem_controller->read32(*xsp);
  *xsp += 4;
  return val;
}

std::uint64_t hypercpu::cpu::stack_pop64() noexcept {
  h_assert((*xsp + 8) <= *xbp, "Stack pointer too high!");

  std::uint64_t val = mem_controller->read64(*xsp);
  *xsp += 8;
  return val;
}