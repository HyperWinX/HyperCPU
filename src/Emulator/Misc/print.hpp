#pragma once

#include <iostream>
#include <format>

namespace HyperCPU {
  template<typename... Args>
  constexpr void print(std::string_view form, Args... args) {
    std::cout << std::vformat(form, std::make_format_args(args...));
  }

  template<typename... Args>
  constexpr void println(std::string_view form, Args... args) {
    std::cout << std::vformat(form, std::make_format_args(args...)) << '\n';
  }
}
