#include <gtest/gtest.h>
#include <test/tests.hpp>
#include <opcodes.hpp>
#include <exitcodes.hpp>

TEST_F(CPU_TESTING, BSWP_b16){
    cpu.memoryptr[0x0100] = BSWP;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R);
    cpu.memoryptr[0x0102] = static_cast<uint8_t>(HyperCPU::xl1);
    cpu.memoryptr[0x0103] = HLT;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 0x0102;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2), 0x0201);
}

TEST_F(CPU_TESTING, BSWP_b32){
    cpu.memoryptr[0x0100] = BSWP;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R);
    cpu.memoryptr[0x0102] = static_cast<uint8_t>(HyperCPU::x1);
    cpu.memoryptr[0x0103] = HLT;
    cpu.xRegs[1] = 0x01020304;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.xRegs[1], 0x04030201);
}