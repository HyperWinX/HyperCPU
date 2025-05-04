#pragma once

#include <mapbox/eternal.hpp>

#include "PCH/CStd.hpp"
#include "Common/LanguageSpec/Registers.hpp"


constexpr inline const auto registers_assoc = mapbox::eternal::hash_map<mapbox::eternal::string, HyperCPU::Registers>({
    {"x0", HyperCPU::Registers::X0},
    {"x1", HyperCPU::Registers::X1},
    {"x2", HyperCPU::Registers::X2},
    {"x3", HyperCPU::Registers::X3},
    {"x4", HyperCPU::Registers::X4},
    {"x5", HyperCPU::Registers::X5},
    {"x6", HyperCPU::Registers::X6},
    {"x7", HyperCPU::Registers::X7},
    {"xh0", HyperCPU::Registers::XH0},
    {"xh1", HyperCPU::Registers::XH1},
    {"xh2", HyperCPU::Registers::XH2},
    {"xh3", HyperCPU::Registers::XH3},
    {"xh4", HyperCPU::Registers::XH4},
    {"xh5", HyperCPU::Registers::XH5},
    {"xh6", HyperCPU::Registers::XH6},
    {"xh7", HyperCPU::Registers::XH7},
    {"xl0", HyperCPU::Registers::XL0},
    {"xl1", HyperCPU::Registers::XL1},
    {"xl2", HyperCPU::Registers::XL2},
    {"xl3", HyperCPU::Registers::XL3},
    {"xl4", HyperCPU::Registers::XL4},
    {"xl5", HyperCPU::Registers::XL5},
    {"xl6", HyperCPU::Registers::XL6},
    {"xl7", HyperCPU::Registers::XL7},
    {"xll0", HyperCPU::Registers::XLL0},
    {"xll1", HyperCPU::Registers::XLL1},
    {"xll2", HyperCPU::Registers::XLL2},
    {"xll3", HyperCPU::Registers::XLL3},
    {"xllh0", HyperCPU::Registers::XLLH0},
    {"xllh1", HyperCPU::Registers::XLLH1},
    {"xllh2", HyperCPU::Registers::XLLH2},
    {"xllh3", HyperCPU::Registers::XLLH3},
    {"xlll0", HyperCPU::Registers::XLLL0},
    {"xlll1", HyperCPU::Registers::XLLL1},
    {"xlll2", HyperCPU::Registers::XLLL2},
    {"xlll3", HyperCPU::Registers::XLLL3},
    {"xbp", HyperCPU::Registers::XBP},
    {"xsp", HyperCPU::Registers::XSP},
    {"xip", HyperCPU::Registers::XIP},
    {"xgdp", HyperCPU::Registers::XGDP},
    {"xivt", HyperCPU::Registers::XIVT}
});
