#include <gtest/gtest.h>
#include <test/tests.hpp>
#include <opcodes.hpp>
#include <exitcodes.hpp>

TEST_F(CPU_TESTING, POP_b8_R){
    cpu.bstp = 0x0200;
    cpu.stp = 0x0200;
    cpu.memoryptr[0x0100] = PUSH;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::IMM);
    cpu.memoryptr[0x0102] = 0xA0;
    cpu.memoryptr[0x0103] = POP;
    cpu.memoryptr[0x0104] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R);
    cpu.memoryptr[0x0105] = HyperCPU::xlh1;
    cpu.memoryptr[0x0106] = HLT;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.stp, 0x0200);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2), 0xA0);
}

TEST_F(CPU_TESTING, POP_b16_R){
    cpu.bstp = 0x0200;
    cpu.stp = 0x0200;
    cpu.memoryptr[0x0100] = PUSH;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::IMM);
    cpu.memoryptr[0x0102] = 0xA0;
    cpu.memoryptr[0x0103] = 0xA0;
    cpu.memoryptr[0x0104] = POP;
    cpu.memoryptr[0x0105] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R);
    cpu.memoryptr[0x0106] = HyperCPU::xl1;
    cpu.memoryptr[0x0107] = HLT;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.stp, 0x0200);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2), 0xA0A0);
}

TEST_F(CPU_TESTING, POP_b32_R){
    cpu.bstp = 0x0200;
    cpu.stp = 0x0200;
    cpu.memoryptr[0x0100] = PUSH;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::IMM);
    cpu.memoryptr[0x0102] = 0xA0;
    cpu.memoryptr[0x0103] = 0xA0;
    cpu.memoryptr[0x0104] = 0xA0;
    cpu.memoryptr[0x0105] = 0xA0;
    cpu.memoryptr[0x0106] = POP;
    cpu.memoryptr[0x0107] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R);
    cpu.memoryptr[0x0108] = HyperCPU::x1;
    cpu.memoryptr[0x0109] = HLT;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.stp, 0x0200);
    EXPECT_EQ(cpu.xRegs[1], 0xA0A0A0A0);
}