#pragma once

#include <cstdint>


#define REGISTER_CASE(reg) case static_cast<std::uint8_t>(reg):
#define REGISTER_DEFAULT_CASE() default: return false;

namespace hypercpu {

  enum registers : std::uint_fast8_t {
    X0 = 0, X1, X2, X3, X4, X5, X6, X7,
    XH0, XH1, XH2, XH3, XH4, XH5, XH6, XH7,
    XL0, XL1, XL2, XL3, XL4, XL5, XL6, XL7,
    XLL0, XLL1, XLL2, XLL3,
    XLLH0, XLLH1, XLLH2, XLLH3,
    XLLL0, XLLL1, XLLL2, XLLL3,
    XBP, XSP, XIP,
    XGDP, XIVT
  };

  namespace validator {
    static constexpr inline bool is_valid_register(std::uint8_t reg) {
      switch (reg) {
        REGISTER_CASE(X0)
        REGISTER_CASE(X1)
        REGISTER_CASE(X2)
        REGISTER_CASE(X3)
        REGISTER_CASE(X4)
        REGISTER_CASE(X5)
        REGISTER_CASE(X6)
        REGISTER_CASE(X7)
        REGISTER_CASE(XH0)
        REGISTER_CASE(XH1)
        REGISTER_CASE(XH2)
        REGISTER_CASE(XH3)
        REGISTER_CASE(XH4)
        REGISTER_CASE(XH5)
        REGISTER_CASE(XH6)
        REGISTER_CASE(XH7)
        REGISTER_CASE(XL0)
        REGISTER_CASE(XL1)
        REGISTER_CASE(XL2)
        REGISTER_CASE(XL3)
        REGISTER_CASE(XL4)
        REGISTER_CASE(XL5)
        REGISTER_CASE(XL6)
        REGISTER_CASE(XL7)
        REGISTER_CASE(XLL0)
        REGISTER_CASE(XLL1)
        REGISTER_CASE(XLL2)
        REGISTER_CASE(XLL3)
        REGISTER_CASE(XLLH0)
        REGISTER_CASE(XLLH1)
        REGISTER_CASE(XLLH2)
        REGISTER_CASE(XLLH3)
        REGISTER_CASE(XLLL0)
        REGISTER_CASE(XLLL1)
        REGISTER_CASE(XLLL2)
        REGISTER_CASE(XLLL3)
        REGISTER_CASE(XBP)
        REGISTER_CASE(XSP)
        REGISTER_CASE(XIP)
        REGISTER_CASE(XGDP)
        REGISTER_CASE(XIVT)
          return true;
        REGISTER_DEFAULT_CASE()
      }
    }
  }
}