#pragma once

#include "PCH/CStd.hpp"

namespace HyperCPU {
  enum class Version : std::uint8_t {
    PreRelease = 0x01,
    Release1_0 = 0x02
  };

  enum class IOSubsystem : std::uint8_t {
    NCurses = 0x01,
    Simple = 0x02
  };

  enum class FileType : std::uint8_t {
    Object = 0x01,
    Binary = 0x02
  };

  using Magic = std::uint64_t;

  static inline constexpr Magic magic = 0xb7a6457636cf6c3a;
  static inline constexpr Version current_version = Version::PreRelease;

  struct GenericHeader {
    Magic magic;
    Version version;
    FileType type;
    std::uint32_t code_size;
    std::uint32_t entry_point;
  };

  enum class ParseError {
    Empty,
    Invalid
  };

  std::uint64_t ParseMemoryString(const std::string& str);
} // namespace HyperCPU
