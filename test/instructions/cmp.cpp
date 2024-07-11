#include <gtest/gtest.h>
#include <test/tests.hpp>
#include <opcodes.hpp>
#include <exitcodes.hpp>

TEST_F(CPU_TESTING, CMP_b8_R_R_LESS){
    cpu.memoryptr[0x0100] = CMP;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_R);
    cpu.memoryptr[0x0102] = static_cast<uint8_t>(HyperCPU::xlh1);
    cpu.memoryptr[0x0103] = static_cast<uint8_t>(HyperCPU::xll0);
    cpu.memoryptr[0x0104] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2) = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[0] + 3) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.cmpr, false);
    EXPECT_EQ(cpu.carry_flag, false);
}

TEST_F(CPU_TESTING, CMP_b8_R_R_BIGGER){
    cpu.memoryptr[0x0100] = CMP;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_R);
    cpu.memoryptr[0x0102] = static_cast<uint8_t>(HyperCPU::xlh1);
    cpu.memoryptr[0x0103] = static_cast<uint8_t>(HyperCPU::xll0);
    cpu.memoryptr[0x0104] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2) = 50;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[0] + 3) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.cmpr, false);
    EXPECT_EQ(cpu.carry_flag, true);
}

TEST_F(CPU_TESTING, CMP_b8_R_R_EQ){
    cpu.memoryptr[0x0100] = CMP;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_R);
    cpu.memoryptr[0x0102] = static_cast<uint8_t>(HyperCPU::xlh1);
    cpu.memoryptr[0x0103] = static_cast<uint8_t>(HyperCPU::xll0);
    cpu.memoryptr[0x0104] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2) = 50;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[0] + 3) = 50;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.cmpr, true);
    EXPECT_EQ(cpu.carry_flag, false);
}

TEST_F(CPU_TESTING, CMP_b16_R_R_LESS){
    cpu.memoryptr[0x0100] = CMP;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_R);
    cpu.memoryptr[0x0102] = static_cast<uint8_t>(HyperCPU::xl1);
    cpu.memoryptr[0x0103] = static_cast<uint8_t>(HyperCPU::xl0);
    cpu.memoryptr[0x0104] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2) = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[0] + 2) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.cmpr, false);
    EXPECT_EQ(cpu.carry_flag, false);
}

TEST_F(CPU_TESTING, CMP_b16_R_R_BIGGER){
    cpu.memoryptr[0x0100] = CMP;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_R);
    cpu.memoryptr[0x0102] = static_cast<uint8_t>(HyperCPU::xl1);
    cpu.memoryptr[0x0103] = static_cast<uint8_t>(HyperCPU::xl0);
    cpu.memoryptr[0x0104] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2) = 50;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[0] + 2) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.cmpr, false);
    EXPECT_EQ(cpu.carry_flag, true);
}

TEST_F(CPU_TESTING, CMP_b16_R_R_EQ){
    cpu.memoryptr[0x0100] = CMP;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_R);
    cpu.memoryptr[0x0102] = static_cast<uint8_t>(HyperCPU::xl1);
    cpu.memoryptr[0x0103] = static_cast<uint8_t>(HyperCPU::xl0);
    cpu.memoryptr[0x0104] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2) = 50;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[0] + 2) = 50;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.cmpr, true);
    EXPECT_EQ(cpu.carry_flag, false);
}

TEST_F(CPU_TESTING, CMP_b32_R_R_LESS){
    cpu.memoryptr[0x0100] = CMP;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_R);
    cpu.memoryptr[0x0102] = static_cast<uint8_t>(HyperCPU::x1);
    cpu.memoryptr[0x0103] = static_cast<uint8_t>(HyperCPU::x0);
    cpu.memoryptr[0x0104] = HLT;
    cpu.xRegs[1] = 5;
    cpu.xRegs[0] = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.cmpr, false);
    EXPECT_EQ(cpu.carry_flag, false);
}

TEST_F(CPU_TESTING, CMP_b32_R_R_BIGGER){
    cpu.memoryptr[0x0100] = CMP;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_R);
    cpu.memoryptr[0x0102] = static_cast<uint8_t>(HyperCPU::x1);
    cpu.memoryptr[0x0103] = static_cast<uint8_t>(HyperCPU::x0);
    cpu.memoryptr[0x0104] = HLT;
    cpu.xRegs[1] = 50;
    cpu.xRegs[0] = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.cmpr, false);
    EXPECT_EQ(cpu.carry_flag, true);
}

TEST_F(CPU_TESTING, CMP_b32_R_R_EQ){
    cpu.memoryptr[0x0100] = CMP;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_R);
    cpu.memoryptr[0x0102] = static_cast<uint8_t>(HyperCPU::x1);
    cpu.memoryptr[0x0103] = static_cast<uint8_t>(HyperCPU::x0);
    cpu.memoryptr[0x0104] = HLT;
    cpu.xRegs[1] = 50;
    cpu.xRegs[0] = 50;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.cmpr, true);
    EXPECT_EQ(cpu.carry_flag, false);
}