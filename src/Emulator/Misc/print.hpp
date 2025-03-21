#pragma once

#include <iostream>
#include <format>

namespace HyperCPU {
  template<typename... Args>
  constexpr void print(std::format_string<Args...> form, Args&&... args) {
    std::cout << std::format(form, std::forward<Args>(args)...);
  }

  template<typename... Args>
    constexpr void println(std::format_string<Args...> form, Args&&... args) {
      std::cout << std::format(form, std::forward<Args>(args)...) << '\n';
    }
}
