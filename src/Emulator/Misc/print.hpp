#pragma once

#include <iostream>
#include <fmt/format.h>

namespace HyperCPU {
  template<typename... Args>
  constexpr void print(std::string_view form, Args... args) {
    std::cout << fmt::vformat(form, fmt::make_format_args(args...));
  }

  template<typename... Args>
  constexpr void println(std::string_view form, Args... args) {
    std::cout << fmt::vformat(form, fmt::make_format_args(args...)) << '\n';
  }
}
