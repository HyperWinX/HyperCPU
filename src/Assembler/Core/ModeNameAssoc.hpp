#pragma once

#include <Core/Compiler.hpp>

#include <mapbox/eternal.hpp>

constexpr inline const auto mode_assoc = mapbox::eternal::hash_map<mapbox::eternal::string, hcasm::mode>({
    {"b8", hcasm::mode::b8},
    {"b16", hcasm::mode::b16},
    {"b32", hcasm::mode::b32},
    {"b64", hcasm::mode::b64},
});