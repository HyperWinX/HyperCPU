#include <cpu.hpp>

#include <cstdio>
#include <cstdlib>

constexpr auto RED_TEXT_START = "\033[31;1;4m";
constexpr auto COLOR_RESET = "\033[0m";

int HyperCPU::CPU::_raise_fatal_exception(HyperCPU::_exception_t exception){
    switch (exception){
        case GDT_READ_FAILURE:
            fprintf(stderr, "%sGDT entries read failure! Exiting now.\n%s", RED_TEXT_START, COLOR_RESET);
            break;
        case GDT_INVALID_ADDRESS:
            fprintf(stderr, "%sGDT invalid address! Exiting now.\n%s", RED_TEXT_START, COLOR_RESET);
            break;
        default:
            fprintf(stderr, "%sUnknown exception was raised! Exiting now.\n%s", RED_TEXT_START, COLOR_RESET);
            break;
    }
    free(_memory);
    exit(1);
}