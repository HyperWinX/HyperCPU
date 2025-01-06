#include <mapbox/eternal.hpp>

#include <emulator/core/cpu/instructions/opcodes.hpp>

using namespace mapbox::eternal;

[[gnu::used]]
const static std::unordered_map<std::string, hypercpu::opcode> opcode_assoc{
    {"adc",   hypercpu::opcode::ADC},
    {"add",   hypercpu::opcode::ADD},
    {"and",   hypercpu::opcode::AND},
    {"andn",  hypercpu::opcode::ANDN},
    {"bswap", hypercpu::opcode::BSWAP},
    {"call",  hypercpu::opcode::CALL},
    {"ccrf",  hypercpu::opcode::CCRF},
    {"covf",  hypercpu::opcode::COVF},
    {"cudf",  hypercpu::opcode::CUDF},
    {"hid",   hypercpu::opcode::HID},
    {"inc",   hypercpu::opcode::INC},
    {"dec",   hypercpu::opcode::DEC},
    {"div",   hypercpu::opcode::DIV},
    {"mul",   hypercpu::opcode::MUL},
    {"sub",   hypercpu::opcode::SUB},
    {"shfr",  hypercpu::opcode::SHFR},
    {"shfl",  hypercpu::opcode::SHFL},
    {"or",    hypercpu::opcode::OR},
    {"halt",  hypercpu::opcode::HALT},
    {"loivt", hypercpu::opcode::LOIVT},
    {"intr",  hypercpu::opcode::INTR},
    {"ret",   hypercpu::opcode::RET},
    {"iret",  hypercpu::opcode::IRET},
    {"mov",   hypercpu::opcode::MOV}
};
