#include <gtest/gtest.h>
#include <test/tests.hpp>
#include <opcodes.hpp>
#include <exitcodes.hpp>

TEST_F(CPU_TESTING, MOV_b8_RM_R){
    cpu.memoryptr[0x0100] = MOV;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = HyperCPU::xlh0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[0] + 2) = 0x17;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.memoryptr[0x010A], 0x17);
}

TEST_F(CPU_TESTING, MOV_b16_RM_R){
    cpu.memoryptr[0x0100] = MOV;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = HyperCPU::xl0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[0] + 2) = 0x0A0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), 0x0A0A);
}

TEST_F(CPU_TESTING, MOV_b32_RM_R){
    cpu.memoryptr[0x0100] = MOV;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = HyperCPU::x0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[0] = 0x0A0A0A0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), 0x0A0A0A0A);
}

TEST_F(CPU_TESTING, MOV_b8_R_RM){
    cpu.memoryptr[0x0100] = MOV;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu.memoryptr[0x0102] = HyperCPU::xlh1;
    cpu.memoryptr[0x0103] = HyperCPU::x0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2) = 0x0A;
    cpu.xRegs[0] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2), 5);
}

TEST_F(CPU_TESTING, MOV_b16_R_RM){
    cpu.memoryptr[0x0100] = MOV;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu.memoryptr[0x0102] = HyperCPU::xl1;
    cpu.memoryptr[0x0103] = HyperCPU::x0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 0x0A0A;
    cpu.xRegs[0] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2), 5);
}

TEST_F(CPU_TESTING, MOV_b32_R_RM){
    cpu.memoryptr[0x0100] = MOV;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = HyperCPU::x0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[1] = 0x0A0A0A0A;
    cpu.xRegs[0] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.xRegs[1], 5);
}

TEST_F(CPU_TESTING, MOV_b8_RM_IMM){
    cpu.memoryptr[0x0100] = MOV;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu.memoryptr[0x010A]), 0x0A);
}

TEST_F(CPU_TESTING, MOV_b16_RM_IMM){
    cpu.memoryptr[0x0100] = MOV;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0104] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), 0x0A0A);
}

TEST_F(CPU_TESTING, MOV_b32_RM_IMM){
    cpu.memoryptr[0x0100] = MOV;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0104] = 0x0A;
    cpu.memoryptr[0x0105] = 0x0A;
    cpu.memoryptr[0x0106] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), 0x0A0A0A0A);
}

TEST_F(CPU_TESTING, MOV_b8_R_IMM){
    cpu.memoryptr[0x0100] = MOV;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::xlh1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2), 0x0A);
}

TEST_F(CPU_TESTING, MOV_b16_R_IMM){
    cpu.memoryptr[0x0100] = MOV;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::xl1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0104] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2), 0x0A0A);
}

TEST_F(CPU_TESTING, MOV_b32_R_IMM){
    cpu.memoryptr[0x0100] = MOV;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0104] = 0x0A;
    cpu.memoryptr[0x0105] = 0x0A;
    cpu.memoryptr[0x0106] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.xRegs[1] = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.xRegs[1], 0x0A0A0A0A);
}

TEST_F(CPU_TESTING, MOV_b8_RM_M){
    cpu.memoryptr[0x0100] = MOV;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010B;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.memoryptr[0x010B] = 0x0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.memoryptr[0x010A], 0x0A);
}

TEST_F(CPU_TESTING, MOV_b16_RM_M){
    cpu.memoryptr[0x0100] = MOV;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010C;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010C]) = 0x0A0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), 0x0A0A);
}

TEST_F(CPU_TESTING, MOV_b32_RM_M){
    cpu.memoryptr[0x0100] = MOV;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010E;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010E]) = 0x0A0A0A0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), 0x0A0A0A0A);
}

TEST_F(CPU_TESTING, MOV_b8_R_M){
    cpu.memoryptr[0x0100] = MOV;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu.memoryptr[0x0102] = HyperCPU::xll1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 0x0A;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 3) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 3), 0x0A);
}

TEST_F(CPU_TESTING, MOV_b16_R_M){
    cpu.memoryptr[0x0100] = MOV;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu.memoryptr[0x0102] = HyperCPU::xl1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 0x0A0A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2), 5);
}

TEST_F(CPU_TESTING, MOV_b32_R_M){
    cpu.memoryptr[0x0100] = MOV;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[1] = 0x0A0A0A0A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.xRegs[1], 5);
}

TEST_F(CPU_TESTING, MOV_b8_M_R){
    cpu.memoryptr[0x0100] = MOV;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::xll1;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 0x0A;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 3) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu.memoryptr[0x010A]), 5);
}

TEST_F(CPU_TESTING, MOV_b16_M_R){
    cpu.memoryptr[0x0100] = MOV;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::xl1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]) = 0x0A0A;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), 5);
}

TEST_F(CPU_TESTING, MOV_b32_M_R){
    cpu.memoryptr[0x0100] = MOV;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::x1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]) = 0x0A0A0A0A;
    cpu.xRegs[1] = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), 5);
}

TEST_F(CPU_TESTING, MOV_b8_M_RM){
    cpu.memoryptr[0x0100] = MOV;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::x1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]) = 0x0A;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010E]) = 5;
    cpu.xRegs[1] = 0x010E;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu.memoryptr[0x010A]), 5);
}

TEST_F(CPU_TESTING, MOV_b16_M_RM){
    cpu.memoryptr[0x0100] = MOV;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::x1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]) = 0x0A0A;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010E]) = 5;
    cpu.xRegs[1] = 0x010E;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), 5);
}

TEST_F(CPU_TESTING, MOV_b32_M_RM){
    cpu.memoryptr[0x0100] = MOV;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::x1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]) = 0x0A0A0A0A;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010E]) = 5;
    cpu.xRegs[1] = 0x010E;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), 5);
}