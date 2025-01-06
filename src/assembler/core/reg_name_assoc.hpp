#pragma once

#include <mapbox/eternal.hpp>
#include <emulator/core/cpu/instructions/registers.hpp>

extern const mapbox::eternal::impl::map<mapbox::eternal::impl::element_hash<mapbox::eternal::string, hypercpu::registers>, 24UL> registers_assoc;
