#pragma once

#include <cstdint>


namespace hypercpu {

  template<typename enum_type, enum_type... values>
  class check_valid_opcode;

  template<typename enum_type>
  class check_valid_opcode<enum_type> {
  public:
    template<typename int_type>
    static bool constexpr is_valid(int_type) { return false; }
  };

  template<typename enum_type, enum_type v, enum_type... next>
  class check_valid_opcode<enum_type, v, next...> : private check_valid_opcode<enum_type, next...> {
    using super = check_valid_opcode<enum_type, next...>;

  public:
    template<typename int_type>
    static bool constexpr is_valid(int_type value) {
      return value == static_cast<int_type>(value) || super::is_valid(value);
    }
  };

  enum opcode : std::uint_fast16_t {
    ADC = 0x0001,
    ADD = 0x0002,
    MOV = 0x007F
  };

  using op_validator = check_valid_opcode<opcode, MOV>;
}