#pragma once

#include <cstdint>

namespace hypercpu {
  template<typename enum_type, enum_type... values>
  class check_valid_register;

  template<typename enum_type>
  class check_valid_register<enum_type> {
  public:
    template<typename int_type>
    static bool constexpr is_valid(int_type) { return false; }
  };

  template<typename enum_type, enum_type v, enum_type... next>
  class check_valid_register<enum_type, v, next...> : private check_valid_register<enum_type, next...> {
    using super = check_valid_register<enum_type, next...>;

  public:
    template<typename int_type>
    static bool constexpr is_valid(int_type value) {
      return value == static_cast<int_type>(value) || super::is_valid(value);
    }
  };

  enum registers : std::uint_fast8_t {
    X0 = 0, X1, X2, X3, X4, X5, X6, X7,
    XH0, XH1, XH2, XH3, XH4, XH5, XH6, XH7,
    XL0, XL1, XL2, XL3, XL4, XL5, XL6, XL7,
    XLL0, XLL1, XLL2, XLL3,
    XLLH0, XLLH1, XLLH2, XLLH3,
    XLLL0, XLLL1, XLLL2, XLLL3,
    XBP, XSP, XIP,
    XGDP, XIDP
  };

  using register_validator = check_valid_register<registers,
    X0, X1, X2, X3, X4, X5, X6, X7,
    XH0, XH1, XH2, XH3, XH4, XH5, XH6, XH7,
    XL0, XL1, XL2, XL3, XL4, XL5, XL6, XL7,
    XLL0, XLL1, XLL2, XLL3,
    XLLH0, XLLH1, XLLH2, XLLH3,
    XLLL0, XLLL1, XLLL2, XLLL3,
    XBP, XSP, XIP,
    XGDP, XIDP>;
}