#include <iostream>
#include <iomanip>
#include <sstream>

#include <Core/Compiler.hpp>


using HCAsm::Value;

[[gnu::visibility("hidden")]]
std::uint64_t BinaryStrToUint64(const std::string_view& binary_str) {
  if (binary_str.length() > 64) {
    throw std::invalid_argument("Binary string is too long to fit in a uint64_t");
  }

  std::uint64_t result = 0;
  for (char c : binary_str) {
    if (c != '0' && c != '1') {
      if (c == 'b') {
        break;
      }
      throw std::invalid_argument("Invalid character in binary string");
    }
    result = (result << 1) | (c - '0');
  }
  return result;
}

Value HCAsm::TokenizeSignedInt(std::string_view str) {
  return { std::stol(str.begin()) };
}

Value HCAsm::TokenizeUnsignedInt(std::string_view str) {
  return { std::stoul(str.begin()) };
}

Value HCAsm::TokenizeString(std::string_view str) {
  return { std::string{str.begin() + 1, str.end() - 1} };
}

Value HCAsm::TokenizeIdentifier(std::string_view str) {
  return {std::string{str}};
}

Value HCAsm::TokenizeHexadecimal(std::string_view str) {
  std::uint64_t x;
  std::stringstream ss;
  ss << std::hex << str.begin();
  ss >> x;
  return {x};
}

Value HCAsm::TokenizeBinary(std::string_view str) {
  return { BinaryStrToUint64(str) };
}