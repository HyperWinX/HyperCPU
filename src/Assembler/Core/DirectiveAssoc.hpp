#include <Core/Compiler.hpp>

#include <mapbox/eternal.hpp>

static constexpr inline auto directive_assoc = mapbox::eternal::map<mapbox::eternal::string, ({
  { ".b8", HCAsm::DirectiveType::RawData_b8 },
  { ".b16", HCAsm::DirectiveType::RawData_b16 },
  { ".b32", HCAsm::DirectiveType::RawData_b32 },
  { ".b64", HCAsm::DirectiveType::RawData_b64 }
});
