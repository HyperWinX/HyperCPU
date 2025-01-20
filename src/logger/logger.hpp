#pragma once

#include <cstdint>

#include <string>
#include <format>
#include <print>

#include <logger/colors.hpp>


namespace hypercpu {
  enum class loglevel : std::uint_fast8_t {
    DEBUG = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3
  };

  class logger {
  private:
    loglevel _loglevel;

    constexpr char define_msg_char(hypercpu::loglevel lvl) const noexcept {
      switch (lvl) {
        case hypercpu::loglevel::DEBUG:   return '-';
        case hypercpu::loglevel::INFO:    return '*';
        case hypercpu::loglevel::WARNING: return '=';
        case hypercpu::loglevel::ERROR:   return '!';
        default:
          std::unreachable();
      }
    }

    constexpr const char* define_bold_color(hypercpu::loglevel lvl) const noexcept {
      switch (lvl) {
        case hypercpu::loglevel::DEBUG:
        case hypercpu::loglevel::INFO:    return RESET;
        case hypercpu::loglevel::WARNING: return B_YELLOW;
        case hypercpu::loglevel::ERROR:   return B_RED;
        default:
          std::unreachable();
      }
    }

    constexpr const char* define_color(hypercpu::loglevel lvl) const noexcept {
      switch (lvl) {
        case hypercpu::loglevel::DEBUG:
        case hypercpu::loglevel::INFO:    return RESET;
        case hypercpu::loglevel::WARNING: return YELLOW;
        case hypercpu::loglevel::ERROR:   return RED;
        default:
          std::unreachable();
      }
    }

  public:
    logger(loglevel default_loglevel) : _loglevel(default_loglevel) { }

    template<typename... Args>
    void log(loglevel lvl, std::string_view fmt, Args&&... args) const noexcept {
      if (static_cast<std::uint_fast8_t>(lvl) < static_cast<std::uint_fast8_t>(_loglevel)) {
        return;
      }
      
      auto ch = define_msg_char(lvl);
      auto bold_col = define_bold_color(lvl);
      auto col = define_color(lvl);

      std::print("{}[{}]{} {}", bold_col, ch, RESET, col);
      std::puts(std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...)).c_str());
      std::print("{}\n", RESET);
    }
  };
}