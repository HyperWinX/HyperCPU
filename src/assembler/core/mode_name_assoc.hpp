#pragma once

#include <mapbox/eternal.hpp>
#include <core/compiler.hpp>

constexpr inline const auto mode_assoc = mapbox::eternal::hash_map<mapbox::eternal::string, hcasm::mode>({
    {"b8", hcasm::mode::b8},
    {"b16", hcasm::mode::b16},
    {"b32", hcasm::mode::b32},
    {"b64", hcasm::mode::b64},
});