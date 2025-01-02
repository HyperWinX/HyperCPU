#include <iostream>
#include <iomanip>
#include <sstream>

#include <core/compiler.hpp>


using hcasm::value;

[[gnu::visibility("hidden")]]
std::uint64_t binary_string_to_uint64(const std::string_view& binary_str) {
  if (binary_str.length() > 64) {
    throw std::invalid_argument("Binary string is too long to fit in a uint64_t");
  }

  std::uint64_t result = 0;
  for (char c : binary_str) {
    if (c != '0' && c != '1') {
      throw std::invalid_argument("Invalid character in binary string");
    }
    result = (result << 1) | (c - '0');
  }
  return result;
}

value hcasm::tokenize_sint(std::string_view str) {
  return { std::stol(str.begin()) };
}

value hcasm::tokenize_uint(std::string_view str) {
  return { std::stoul(str.begin()) };
}

value hcasm::tokenize_str(std::string_view str) {
  return { std::string{str.begin() + 1, str.end() - 1} };
}

value hcasm::tokenize_hex(std::string_view str) {
  std::uint64_t x;
  std::stringstream ss;
  ss << std::hex << str.begin() + 2;
  ss >> x;
  return {x};
}

value hcasm::tokenize_binary(std::string_view str) {
  return { binary_string_to_uint64(str) };
}