#pragma once

#include <cstdint>
#include <type_traits>

namespace HCAsm {

struct CompilerState;

}

namespace pog {

struct LineSpecialization {
  LineSpecialization(std::uint32_t line, std::uint16_t offset, std::uint16_t length)
    : line(line)
    , offset(offset)
    , length(length) { }
  LineSpecialization()
    : line(1)
    , offset(0)
    , length(0) { }
  
  std::uint32_t line;
  std::uint16_t offset;
  std::uint16_t length;
};

template <typename ValueT>
struct TokenWithLineSpec {
  TokenWithLineSpec() = default;
  TokenWithLineSpec(ValueT& val, LineSpecialization spec) : value(val), line_spec(spec) { }

  ValueT value;
  LineSpecialization line_spec;
};

}