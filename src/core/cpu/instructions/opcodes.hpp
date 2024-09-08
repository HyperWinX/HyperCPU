#pragma once

#include <cstdint>


namespace hypercpu {

  template<typename enum_type, enum_type... values>
  class check_valid_opcode;

  template<typename enum_type>
  class check_valid_opcode<enum_type> {
  public:
    template<typename int_type>
    static bool constexpr is_value(int_type) { return false; }
  };

  template<typename enum_type, enum_type v, enum_type... next>
  class check_valid_opcode<enum_type, v, next...> : private check_valid_opcode<enum_type, next...> {
    using super = check_valid_opcode<enum_type, next...>;

  public:
    template<typename int_type>
    static bool constexpr is_value(int_type value) {
      return value == static_cast<int_type>(value) || super::is_value(value);
    }
  };

  enum opcode : std::uint_fast16_t {
    MOV = 0x0001
  };

  using valid_opcode = check_valid_opcode<opcode, MOV>;
}