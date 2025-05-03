#pragma once

#include "pch.hpp"

#include <Core/Compiler.hpp>

#include <mapbox/eternal.hpp>

constexpr inline const auto mode_assoc = mapbox::eternal::hash_map<mapbox::eternal::string, HCAsm::Mode>({
    {"b8", HCAsm::Mode::b8},
    {"b16", HCAsm::Mode::b16},
    {"b32", HCAsm::Mode::b32},
    {"b64", HCAsm::Mode::b64},
});
