#include <gtest/gtest.h>
#include <test/tests.hpp>
#include <opcodes.hpp>
#include <exitcodes.hpp>

TEST_F(CPU_TESTING, DEC_b8_M){
    cpu.memoryptr[0x0100] = DEC;
    cpu.memoryptr[0x0101] = ((static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M));
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x0107;
    cpu.memoryptr[0x0106] = HLT;
    cpu.memoryptr[0x0107] = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.memoryptr[0x0107], 9);
}

TEST_F(CPU_TESTING, DEC_b16_M){
    cpu.memoryptr[0x0100] = DEC;
    cpu.memoryptr[0x0101] = ((static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M));
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x0107;
    cpu.memoryptr[0x0106] = HLT;
    *reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x0107]) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x0107]), 9);
}

TEST_F(CPU_TESTING, DEC_b32_M){
    cpu.memoryptr[0x0100] = DEC;
    cpu.memoryptr[0x0101] = ((static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M));
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x0107;
    cpu.memoryptr[0x0106] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0107]) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0107]), 9);
}

TEST_F(CPU_TESTING, DEC_b8_R){
    cpu.memoryptr[0x0100] = DEC;
    cpu.memoryptr[0x0101] = ((static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R));
    cpu.memoryptr[0x0102] = HyperCPU::xlh0;
    cpu.memoryptr[0x0103] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[0] + 2) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[0] + 2), 9);
}

TEST_F(CPU_TESTING, DEC_b16_R){
    cpu.memoryptr[0x0100] = DEC;
    cpu.memoryptr[0x0101] = ((static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R));
    cpu.memoryptr[0x0102] = HyperCPU::xl0;
    cpu.memoryptr[0x0103] = HLT;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[0] + 2) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[0] + 2), 9);
}

TEST_F(CPU_TESTING, DEC_b32_R){
    cpu.memoryptr[0x0100] = DEC;
    cpu.memoryptr[0x0101] = ((static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R));
    cpu.memoryptr[0x0102] = HyperCPU::x0;
    cpu.memoryptr[0x0103] = HLT;
    cpu.xRegs[0] = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.xRegs[0], 9);
}