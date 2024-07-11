#include <gtest/gtest.h>
#include <test/tests.hpp>
#include <opcodes.hpp>
#include <exitcodes.hpp>

TEST_F(CPU_TESTING, PUSH_b8_R){
    cpu.bstp = 0x0200;
    cpu.stp = 0x0200;
    cpu.memoryptr[0x0100] = PUSH;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R);
    cpu.memoryptr[0x0102] = HyperCPU::xlh0;
    cpu.memoryptr[0x0103] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[0] + 2) = 0xA6;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.stp, 0x0200 - 1);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(cpu.memoryptr + cpu.stp), 0xA6);
}

TEST_F(CPU_TESTING, PUSH_b16_R){
    cpu.bstp = 0x0200;
    cpu.stp = 0x0200;
    cpu.memoryptr[0x0100] = PUSH;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R);
    cpu.memoryptr[0x0102] = HyperCPU::xl0;
    cpu.memoryptr[0x0103] = HLT;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[0] + 2) = 0xA6A6;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.stp, 0x0200 - 2);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(cpu.memoryptr + cpu.stp), 0xA6A6);
}

TEST_F(CPU_TESTING, PUSH_b32_R){
    cpu.bstp = 0x0200;
    cpu.stp = 0x0200;
    cpu.memoryptr[0x0100] = PUSH;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R);
    cpu.memoryptr[0x0102] = HyperCPU::x0;
    cpu.memoryptr[0x0103] = HLT;
    cpu.xRegs[0] = 0xA6A6A6A6;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.stp, 0x0200 - 4);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(cpu.memoryptr + cpu.stp), 0xA6A6A6A6);
}

TEST_F(CPU_TESTING, PUSH_b8_IMM){
    cpu.bstp = 0x0200;
    cpu.stp = 0x0200;
    cpu.memoryptr[0x0100] = PUSH;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::IMM);
    *reinterpret_cast<uint8_t*>(cpu.memoryptr + 0x0102) = 0xA6;
    cpu.memoryptr[0x0103] = HLT;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.stp, 0x0200 - 1);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(cpu.memoryptr + cpu.stp), 0xA6);
}

TEST_F(CPU_TESTING, PUSH_b16_IMM){
    cpu.bstp = 0x0200;
    cpu.stp = 0x0200;
    cpu.memoryptr[0x0100] = PUSH;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::IMM);
    *reinterpret_cast<uint16_t*>(cpu.memoryptr + 0x0102) = 0xA6A6;
    cpu.memoryptr[0x0104] = HLT;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.stp, 0x0200 - 2);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(cpu.memoryptr + cpu.stp), 0xA6A6);
}

TEST_F(CPU_TESTING, PUSH_b32_IMM){
    cpu.bstp = 0x0200;
    cpu.stp = 0x0200;
    cpu.memoryptr[0x0100] = PUSH;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::IMM);
    *reinterpret_cast<uint32_t*>(cpu.memoryptr + 0x0102) = 0xA6A6A6A6;
    cpu.memoryptr[0x0106] = HLT;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.stp, 0x0200 - 4);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(cpu.memoryptr + cpu.stp), 0xA6A6A6A6);
}