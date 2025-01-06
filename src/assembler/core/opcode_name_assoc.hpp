#pragma once

#include <mapbox/eternal.hpp>
#include <emulator/core/cpu/instructions/opcodes.hpp>

using namespace mapbox::eternal;

extern const std::unordered_map<std::string, hypercpu::opcode> opcode_assoc;
