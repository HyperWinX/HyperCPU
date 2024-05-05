#include <gtest/gtest.h>
#include <cpu.hpp>
#include <exitcodes.hpp>
#include <opcodes.hpp>

HyperCPU::CPU cpu;

TEST(INSTRUCTIONS, HALT){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = HLT;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b8_RM_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = HyperCPU::xlh0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[0] + 2) = 0x17;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.memoryptr[0x010A], 5 + 0x17 + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b16_RM_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = HyperCPU::xl0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[0] + 2) = 0x0A0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), 5 + 0x0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b32_RM_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = HyperCPU::x0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[0] = 0x0A0A0A0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), 5 + 0x0A0A0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b8_R_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu.memoryptr[0x0102] = HyperCPU::xlh1;
    cpu.memoryptr[0x0103] = HyperCPU::x0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2) = 0x0A;
    cpu.xRegs[0] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2), 5 + 0x0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b16_R_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu.memoryptr[0x0102] = HyperCPU::xl1;
    cpu.memoryptr[0x0103] = HyperCPU::x0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 0x0A0A;
    cpu.xRegs[0] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2), 5 + 0x0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b32_R_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = HyperCPU::x0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[1] = 0x0A0A0A0A;
    cpu.xRegs[0] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.xRegs[1], 5 + 0x0A0A0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b8_RM_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu.memoryptr[0x010A]), 5 + 0x0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b16_RM_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0104] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), 5 + 0x0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b32_RM_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
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
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), 5 + 0x0A0A0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b8_R_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::xlh1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2), 5 + 0x0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b16_R_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::xl1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0104] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2), 5 + 0x0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b32_R_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0104] = 0x0A;
    cpu.memoryptr[0x0105] = 0x0A;
    cpu.memoryptr[0x0106] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.xRegs[1]) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.xRegs[1]), 5 + 0x0A0A0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b8_RM_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010B;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.memoryptr[0x010B] = 0x0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.memoryptr[0x010A], 5 + 0x0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b16_RM_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010C;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010C]) = 0x0A0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), 5 + 0x0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b32_RM_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010E;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010E]) = 0x0A0A0A0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), 5 + 0x0A0A0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b8_R_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu.memoryptr[0x0102] = HyperCPU::xll1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 0x0A;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 3) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 3), 5 + 0x0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b16_R_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu.memoryptr[0x0102] = HyperCPU::xl1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 0x0A0A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2), 5 + 0x0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b32_R_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[1] = 0x0A0A0A0A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.xRegs[1], 5 + 0x0A0A0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b8_M_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::xll1;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 0x0A;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 3) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu.memoryptr[0x010A]), 5 + 0x0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b16_M_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::xl1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]) = 0x0A0A;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), 5 + 0x0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b32_M_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::x1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]) = 0x0A0A0A0A;
    cpu.xRegs[1] = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), 5 + 0x0A0A0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b8_M_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::x1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]) = 0x0A;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010E]) = 5;
    cpu.xRegs[1] = 0x010E;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu.memoryptr[0x010A]), 5 + 0x0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b16_M_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::x1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]) = 0x0A0A;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010E]) = 5;
    cpu.xRegs[1] = 0x010E;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), 5 + 0x0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b32_M_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::x1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]) = 0x0A0A0A0A;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010E]) = 5;
    cpu.xRegs[1] = 0x010E;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), 5 + 0x0A0A0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b8_R_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_R);
    cpu.memoryptr[0x0102] = HyperCPU::xlh1;
    cpu.memoryptr[0x0103] = HyperCPU::xll0;
    cpu.memoryptr[0x0104] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2) = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[0] + 3) = 10;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2), 16);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b16_R_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_R);
    cpu.memoryptr[0x0102] = HyperCPU::xl1;
    cpu.memoryptr[0x0103] = HyperCPU::xh0;
    cpu.memoryptr[0x0104] = HLT;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 5;
    *reinterpret_cast<uint16_t*>(&cpu.xRegs[0]) = 10;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2), 16);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b32_R_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADC;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_R);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = HyperCPU::x0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.xRegs[1] = 5;
    cpu.xRegs[0] = 10;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.xRegs[1], 16);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b8_RM_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADD;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = HyperCPU::xlh0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[0] + 2) = 0x17;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.memoryptr[0x010A], 5 + 0x17);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b16_RM_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADD;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = HyperCPU::xl0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[0] + 2) = 0x0A0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), 5 + 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b32_RM_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADD;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = HyperCPU::x0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[0] = 0x0A0A0A0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), 5 + 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b8_R_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADD;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu.memoryptr[0x0102] = HyperCPU::xlh1;
    cpu.memoryptr[0x0103] = HyperCPU::x0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2) = 0x0A;
    cpu.xRegs[0] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2), 5 + 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b16_R_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADD;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu.memoryptr[0x0102] = HyperCPU::xl1;
    cpu.memoryptr[0x0103] = HyperCPU::x0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 0x0A0A;
    cpu.xRegs[0] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2), 5 + 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b32_R_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADD;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = HyperCPU::x0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[1] = 0x0A0A0A0A;
    cpu.xRegs[0] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.xRegs[1], 5 + 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b8_RM_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADD;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu.memoryptr[0x010A]), 5 + 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b16_RM_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADD;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0104] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), 5 + 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b32_RM_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADD;
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
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), 5 + 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b8_R_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADD;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::xlh1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2), 5 + 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b16_R_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADD;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::xl1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0104] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2), 5 + 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b32_R_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADD;
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
    EXPECT_EQ(cpu.xRegs[1], 5 + 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b8_RM_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADD;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010B;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.memoryptr[0x010B] = 0x0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.memoryptr[0x010A], 5 + 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b16_RM_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADD;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010C;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010C]) = 0x0A0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), 5 + 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b32_RM_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADD;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010E;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010E]) = 0x0A0A0A0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), 5 + 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b8_R_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADD;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu.memoryptr[0x0102] = HyperCPU::xll1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 0x0A;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 3) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 3), 5 + 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b16_R_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADD;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu.memoryptr[0x0102] = HyperCPU::xl1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 0x0A0A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2), 5 + 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b32_R_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADD;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[1] = 0x0A0A0A0A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.xRegs[1], 5 + 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b8_M_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADD;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::xll1;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 0x0A;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 3) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu.memoryptr[0x010A]), 5 + 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b16_M_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADD;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::xl1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]) = 0x0A0A;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), 5 + 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b32_M_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADD;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::x1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]) = 0x0A0A0A0A;
    cpu.xRegs[1] = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), 5 + 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b8_M_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADD;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::x1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]) = 0x0A;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010E]) = 5;
    cpu.xRegs[1] = 0x010E;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu.memoryptr[0x010A]), 5 + 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b16_M_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADD;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::x1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]) = 0x0A0A;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010E]) = 5;
    cpu.xRegs[1] = 0x010E;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), 5 + 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b32_M_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ADD;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::x1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]) = 0x0A0A0A0A;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010E]) = 5;
    cpu.xRegs[1] = 0x010E;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), 5 + 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b8_RM_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = AND;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = HyperCPU::xlh0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[0] + 2) = 0x17;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.memoryptr[0x010A], 5 & 0x17);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b16_RM_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = AND;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = HyperCPU::xl0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[0] + 2) = 0x0A0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), 5 & 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b32_RM_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = AND;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = HyperCPU::x0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[0] = 0x0A0A0A0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), 5 & 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b8_R_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = AND;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu.memoryptr[0x0102] = HyperCPU::xlh1;
    cpu.memoryptr[0x0103] = HyperCPU::x0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2) = 0x0A;
    cpu.xRegs[0] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2), 5 & 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b16_R_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = AND;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu.memoryptr[0x0102] = HyperCPU::xl1;
    cpu.memoryptr[0x0103] = HyperCPU::x0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 0x0A0A;
    cpu.xRegs[0] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2), 5 & 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b32_R_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = AND;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = HyperCPU::x0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[1] = 0x0A0A0A0A;
    cpu.xRegs[0] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.xRegs[1], 5 & 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b8_RM_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = AND;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu.memoryptr[0x010A]), 5 & 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b16_RM_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = AND;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0104] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), 5 & 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b32_RM_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = AND;
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
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), 5 & 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b8_R_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = AND;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::xlh1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2), 5 & 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b16_R_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = AND;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::xl1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0104] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2), 5 & 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b32_R_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = AND;
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
    EXPECT_EQ(cpu.xRegs[1], 5 & 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b8_RM_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = AND;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010B;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.memoryptr[0x010B] = 0x0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.memoryptr[0x010A], 5 & 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b16_RM_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = AND;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010C;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010C]) = 0x0A0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), 5 & 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b32_RM_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = AND;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010E;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010E]) = 0x0A0A0A0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), 5 & 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b8_R_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = AND;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu.memoryptr[0x0102] = HyperCPU::xll1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 0x0A;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 3) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 3), 5 & 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b16_R_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = AND;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu.memoryptr[0x0102] = HyperCPU::xl1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 0x0A0A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2), 5 & 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b32_R_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = AND;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[1] = 0x0A0A0A0A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.xRegs[1], 5 & 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b8_M_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = AND;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::xll1;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 0x0A;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 3) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu.memoryptr[0x010A]), 5 & 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b16_M_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = AND;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::xl1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]) = 0x0A0A;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), 5 & 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b32_M_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = AND;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::x1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]) = 0x0A0A0A0A;
    cpu.xRegs[1] = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), 5 & 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b8_M_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = AND;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::x1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]) = 0x0A;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010E]) = 5;
    cpu.xRegs[1] = 0x010E;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu.memoryptr[0x010A]), 5 & 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b16_M_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = AND;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::x1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]) = 0x0A0A;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010E]) = 5;
    cpu.xRegs[1] = 0x010E;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), 5 & 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b32_M_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = AND;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::x1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]) = 0x0A0A0A0A;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010E]) = 5;
    cpu.xRegs[1] = 0x010E;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), 5 & 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b8_RM_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ANDN;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = HyperCPU::xlh0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[0] + 2) = 0x17;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.memoryptr[0x010A], static_cast<unsigned>(~(5 & 0x17)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b16_RM_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ANDN;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = HyperCPU::xl0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[0] + 2) = 0x0A0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), static_cast<uint16_t>(~(5 & 0x0A0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b32_RM_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ANDN;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = HyperCPU::x0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[0] = 0x0A0A0A0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), static_cast<uint32_t>(~(5 & 0x0A0A0A0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b8_R_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ANDN;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu.memoryptr[0x0102] = HyperCPU::xlh1;
    cpu.memoryptr[0x0103] = HyperCPU::x0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2) = 0x0A;
    cpu.xRegs[0] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2), static_cast<uint8_t>(~(5 & 0x0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b16_R_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ANDN;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu.memoryptr[0x0102] = HyperCPU::xl1;
    cpu.memoryptr[0x0103] = HyperCPU::x0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 0x0A0A;
    cpu.xRegs[0] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2), static_cast<uint16_t>(~(5 & 0x0A0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b32_R_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ANDN;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = HyperCPU::x0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[1] = 0x0A0A0A0A;
    cpu.xRegs[0] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.xRegs[1], ~(5 & 0x0A0A0A0A));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b8_RM_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ANDN;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu.memoryptr[0x010A]), static_cast<uint8_t>(~(5 & 0x0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b16_RM_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ANDN;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0104] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), static_cast<uint16_t>(~(5 & 0x0A0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b32_RM_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ANDN;
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
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), ~(5 & 0x0A0A0A0A));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b8_R_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ANDN;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::xlh1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2), static_cast<uint8_t>(~(5 & 0x0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b16_R_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ANDN;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::xl1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0104] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2), static_cast<uint16_t>(~(5 & 0x0A0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b32_R_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ANDN;
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
    EXPECT_EQ(cpu.xRegs[1], ~(5 & 0x0A0A0A0A));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b8_RM_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ANDN;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010B;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.memoryptr[0x010B] = 0x0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.memoryptr[0x010A], ~(5 & 0x0A));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b16_RM_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ANDN;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010C;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010C]) = 0x0A0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), static_cast<uint16_t>(~(5 & 0x0A0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b32_RM_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ANDN;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010E;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010E]) = 0x0A0A0A0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), ~(5 & 0x0A0A0A0A));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b8_R_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ANDN;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu.memoryptr[0x0102] = HyperCPU::xll1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 0x0A;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 3) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 3), static_cast<uint8_t>(~(5 & 0x0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b16_R_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ANDN;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu.memoryptr[0x0102] = HyperCPU::xl1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 0x0A0A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2), static_cast<uint16_t>(~(5 & 0x0A0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b32_R_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ANDN;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[1] = 0x0A0A0A0A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.xRegs[1], ~(5 & 0x0A0A0A0A));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b8_M_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ANDN;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::xll1;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 0x0A;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 3) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu.memoryptr[0x010A]), static_cast<uint8_t>(~(5 & 0x0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b16_M_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ANDN;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::xl1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]) = 0x0A0A;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), static_cast<uint16_t>(~(5 & 0x0A0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b32_M_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ANDN;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::x1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]) = 0x0A0A0A0A;
    cpu.xRegs[1] = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), ~(5 & 0x0A0A0A0A));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b8_M_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ANDN;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::x1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]) = 0x0A;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010E]) = 5;
    cpu.xRegs[1] = 0x010E;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu.memoryptr[0x010A]), static_cast<uint8_t>(~(5 & 0x0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b16_M_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ANDN;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::x1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]) = 0x0A0A;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010E]) = 5;
    cpu.xRegs[1] = 0x010E;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), static_cast<uint16_t>(~(5 & 0x0A0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b32_M_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = ANDN;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::x1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]) = 0x0A0A0A0A;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010E]) = 5;
    cpu.xRegs[1] = 0x010E;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), ~(5 & 0x0A0A0A0A));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, INS_CLC){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = CLC;
    cpu.memoryptr[0x0101] = HLT;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.carry_flag, false);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, INC_b8_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = INC;
    cpu.memoryptr[0x0101] = ((static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M));
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x0107;
    cpu.memoryptr[0x0106] = HLT;
    cpu.memoryptr[0x0107] = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.memoryptr[0x0107], 11);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, INC_b16_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = INC;
    cpu.memoryptr[0x0101] = ((static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M));
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x0107;
    cpu.memoryptr[0x0106] = HLT;
    *reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x0107]) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x0107]), 11);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, INC_b32_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = INC;
    cpu.memoryptr[0x0101] = ((static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M));
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x0107;
    cpu.memoryptr[0x0106] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0107]) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0107]), 11);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, INC_b8_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = INC;
    cpu.memoryptr[0x0101] = ((static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R));
    cpu.memoryptr[0x0102] = HyperCPU::xlh0;
    cpu.memoryptr[0x0103] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[0] + 2) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[0] + 2), 11);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, INC_b16_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = INC;
    cpu.memoryptr[0x0101] = ((static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R));
    cpu.memoryptr[0x0102] = HyperCPU::xl0;
    cpu.memoryptr[0x0103] = HLT;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[0] + 2) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[0] + 2), 11);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, INC_b32_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = INC;
    cpu.memoryptr[0x0101] = ((static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R));
    cpu.memoryptr[0x0102] = HyperCPU::x0;
    cpu.memoryptr[0x0103] = HLT;
    cpu.xRegs[0] = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.xRegs[0], 11);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, DEC_b8_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = DEC;
    cpu.memoryptr[0x0101] = ((static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M));
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x0107;
    cpu.memoryptr[0x0106] = HLT;
    cpu.memoryptr[0x0107] = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.memoryptr[0x0107], 9);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, DEC_b16_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = DEC;
    cpu.memoryptr[0x0101] = ((static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M));
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x0107;
    cpu.memoryptr[0x0106] = HLT;
    *reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x0107]) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x0107]), 9);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, DEC_b32_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = DEC;
    cpu.memoryptr[0x0101] = ((static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M));
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x0107;
    cpu.memoryptr[0x0106] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0107]) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0107]), 9);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, DEC_b8_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = DEC;
    cpu.memoryptr[0x0101] = ((static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R));
    cpu.memoryptr[0x0102] = HyperCPU::xlh0;
    cpu.memoryptr[0x0103] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[0] + 2) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[0] + 2), 9);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, DEC_b16_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = DEC;
    cpu.memoryptr[0x0101] = ((static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R));
    cpu.memoryptr[0x0102] = HyperCPU::xl0;
    cpu.memoryptr[0x0103] = HLT;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[0] + 2) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[0] + 2), 9);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, DEC_b32_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = DEC;
    cpu.memoryptr[0x0101] = ((static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R));
    cpu.memoryptr[0x0102] = HyperCPU::x0;
    cpu.memoryptr[0x0103] = HLT;
    cpu.xRegs[0] = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.xRegs[0], 9);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b8_RM_R){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b16_RM_R){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b32_RM_R){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b8_R_RM){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b16_R_RM){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b32_R_RM){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b8_RM_IMM){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b16_RM_IMM){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b32_RM_IMM){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b8_R_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = MOV;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::xlh1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2) = 5;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2), 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b16_R_IMM){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b32_R_IMM){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b8_RM_M){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b16_RM_M){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b32_RM_M){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b8_R_M){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b16_R_M){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b32_R_M){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b8_M_R){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b16_M_R){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b32_M_R){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b8_M_RM){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b16_M_RM){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b32_M_RM){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, INS_CALL){
    cpu.Reset(1024);
    cpu.bstp = 0x0200;
    cpu.stp = 0x0200;
    cpu.memoryptr[0x0100] = CALL;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0101]) = 0x0110;
    cpu.memoryptr[0x0110] = HLT;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.insp, 0x0111);
    EXPECT_EQ(cpu.stp, 0x0200 - 4);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[cpu.stp]), 0x0105);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, PUSH_b8_R){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, PUSH_b16_R){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, PUSH_b32_R){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, PUSH_b8_IMM){
    cpu.Reset(1024);
    cpu.bstp = 0x0200;
    cpu.stp = 0x0200;
    cpu.memoryptr[0x0100] = PUSH;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::IMM);
    *reinterpret_cast<uint8_t*>(cpu.memoryptr + 0x0102) = 0xA6;
    cpu.memoryptr[0x0103] = HLT;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.stp, 0x0200 - 1);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(cpu.memoryptr + cpu.stp), 0xA6);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, PUSH_b16_IMM){
    cpu.Reset(1024);
    cpu.bstp = 0x0200;
    cpu.stp = 0x0200;
    cpu.memoryptr[0x0100] = PUSH;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::IMM);
    *reinterpret_cast<uint16_t*>(cpu.memoryptr + 0x0102) = 0xA6A6;
    cpu.memoryptr[0x0104] = HLT;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.stp, 0x0200 - 2);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(cpu.memoryptr + cpu.stp), 0xA6A6);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, PUSH_b32_IMM){
    cpu.Reset(1024);
    cpu.bstp = 0x0200;
    cpu.stp = 0x0200;
    cpu.memoryptr[0x0100] = PUSH;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::IMM);
    *reinterpret_cast<uint32_t*>(cpu.memoryptr + 0x0102) = 0xA6A6A6A6;
    cpu.memoryptr[0x0106] = HLT;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.stp, 0x0200 - 4);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(cpu.memoryptr + cpu.stp), 0xA6A6A6A6);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, POP_b8_R){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, POP_b16_R){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, POP_b32_R){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, CMP_b8_R_R_LESS){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, CMP_b8_R_R_BIGGER){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, CMP_b8_R_R_EQ){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, CMP_b16_R_R_LESS){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, CMP_b16_R_R_BIGGER){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, CMP_b16_R_R_EQ){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, CMP_b32_R_R_LESS){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, CMP_b32_R_R_BIGGER){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, CMP_b32_R_R_EQ){
    cpu.Reset(1024);
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
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, BSWP_b16){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = BSWP;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R);
    cpu.memoryptr[0x0102] = static_cast<uint8_t>(HyperCPU::xl1);
    cpu.memoryptr[0x0103] = HLT;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 0x0102;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2), 0x0201);
    cpu.CleanUp();  
}

TEST(INSTRUCTIONS, BSWP_b32){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = BSWP;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R);
    cpu.memoryptr[0x0102] = static_cast<uint8_t>(HyperCPU::x1);
    cpu.memoryptr[0x0103] = HLT;
    cpu.xRegs[1] = 0x01020304;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.xRegs[1], 0x04030201);
    cpu.CleanUp();  
}

TEST(INSTRUCTIONS, TEST_DEV){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = INFO;
    cpu.memoryptr[0x0101] = HLT;
    cpu.xRegs[31] = 0;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_PRED2([](auto str, auto s1){
        return !strcmp(str, s1);
    }, reinterpret_cast<char*>(&cpu.xRegs[0]), "epyHniWr");
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, TEST_VER){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = INFO;
    cpu.memoryptr[0x0101] = HLT;
    cpu.xRegs[31] = 1;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_PRED2([](auto str, auto s1){
        return !strcmp(str, s1);
    }, reinterpret_cast<char*>(&cpu.xRegs[0]), "a1.0");
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, TEST_CPUNAME){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = INFO;
    cpu.memoryptr[0x0101] = HLT;
    cpu.xRegs[31] = 2;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_PRED2([](auto str, auto s1){
        return !strcmp(str, s1);
    }, reinterpret_cast<char*>(&cpu.xRegs[0]), "epyHUPCr");
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, TEST_JMP){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = JMP;
    cpu.memoryptr[0x0101] = static_cast<uint8_t>(HyperCPU::IMM);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x0110;
    cpu.memoryptr[0x0110] = HLT;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.insp, 0x0111);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, TEST_JGE){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = JGE;
    cpu.memoryptr[0x0101] = static_cast<uint8_t>(HyperCPU::IMM);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x0110;
    cpu.memoryptr[0x0110] = HLT;
    cpu.cmpr = false;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.insp, 0x0111);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, TEST_JLE){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = JLE;
    cpu.memoryptr[0x0101] = static_cast<uint8_t>(HyperCPU::IMM);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x0110;
    cpu.memoryptr[0x0110] = HLT;
    cpu.cmpr = false;
    cpu.carry_flag = false;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.insp, 0x0111);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, TEST_JE){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = JE;
    cpu.memoryptr[0x0101] = static_cast<uint8_t>(HyperCPU::IMM);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x0110;
    cpu.memoryptr[0x0110] = HLT;
    cpu.cmpr = true;
    cpu.carry_flag = false;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.insp, 0x0111);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, TEST_JG){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = JG;
    cpu.memoryptr[0x0101] = static_cast<uint8_t>(HyperCPU::IMM);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x0110;
    cpu.memoryptr[0x0110] = HLT;
    cpu.cmpr = false;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.insp, 0x0111);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, TEST_JL){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = JL;
    cpu.memoryptr[0x0101] = static_cast<uint8_t>(HyperCPU::IMM);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x0110;
    cpu.memoryptr[0x0110] = HLT;
    cpu.cmpr = false;
    cpu.carry_flag = false;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.insp, 0x0111);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, TEST_RET){
    cpu.Reset(1024);
    cpu.stp = 0x0200;
    cpu.bstp = 0x0200;
    cpu.memoryptr[0x0100] = CALL;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0101]) = 0x0110;
    cpu.memoryptr[0x0105] = HLT;
    cpu.memoryptr[0x0110] = RET;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.insp, 0x0106);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, SUB_b8_RM_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = SUB;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = HyperCPU::xlh0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 0x20;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[0] + 2) = 0x17;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.memoryptr[0x010A], 0x20 - 0x17);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, SUB_b16_RM_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = SUB;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = HyperCPU::xl0;
    cpu.memoryptr[0x0104] = HLT;
    *reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]) = 0x2020;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[0] + 2) = 0x0A0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), 0x2020 - 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, SUB_b32_RM_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = SUB;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = HyperCPU::x0;
    cpu.memoryptr[0x0104] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]) = 0x20202020;
    cpu.xRegs[0] = 0x0A0A0A0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), 0x20202020 - 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, SUB_b8_R_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = SUB;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu.memoryptr[0x0102] = HyperCPU::xlh1;
    cpu.memoryptr[0x0103] = HyperCPU::x0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2) = 0x20;
    cpu.xRegs[0] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2), 0x20 - 5);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, SUB_b16_R_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = SUB;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu.memoryptr[0x0102] = HyperCPU::xl1;
    cpu.memoryptr[0x0103] = HyperCPU::x0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 0x2020;
    cpu.xRegs[0] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2), 0x2020 - 5);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, SUB_b32_R_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = SUB;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = HyperCPU::x0;
    cpu.memoryptr[0x0104] = HLT;
    cpu.memoryptr[0x010A] = 5;
    cpu.xRegs[1] = 0x20202020;
    cpu.xRegs[0] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.xRegs[1], 0x20202020 - 5);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, SUB_b8_RM_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = SUB;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 0x20;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu.memoryptr[0x010A]), 0x20 - 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, SUB_b16_RM_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = SUB;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0104] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]) = 0x2020;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), 0x2020 - 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, SUB_b32_RM_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = SUB;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0104] = 0x0A;
    cpu.memoryptr[0x0105] = 0x0A;
    cpu.memoryptr[0x0106] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]) = 0x20202020;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), 0x20202020 - 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, SUB_b8_R_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = SUB;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::xlh1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2) = 0x20;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 2), 0x20 - 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, SUB_b16_R_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = SUB;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::xl1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0104] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 0x2020;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2), 0x2020 - 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, SUB_b32_R_IMM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = SUB;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    cpu.memoryptr[0x0103] = 0x0A;
    cpu.memoryptr[0x0104] = 0x0A;
    cpu.memoryptr[0x0105] = 0x0A;
    cpu.memoryptr[0x0106] = 0x0A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.xRegs[1] = 0x20202020;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.xRegs[1], 0x20202020 - 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, SUB_b8_RM_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = SUB;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010B;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 0x20;
    cpu.memoryptr[0x010B] = 0x0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.memoryptr[0x010A], 0x20 - 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, SUB_b16_RM_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = SUB;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010C;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]) = 0x2020;
    *reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010C]) = 0x0A0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), 0x2020 - 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, SUB_b32_RM_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = SUB;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010E;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]) = 0x20202020;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010E]) = 0x0A0A0A0A;
    cpu.xRegs[1] = 0x010A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), 0x20202020 - 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, SUB_b8_R_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = SUB;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu.memoryptr[0x0102] = HyperCPU::xll1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010A;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 0x0A;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 3) = 0x20;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 3), 0x20 - 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, SUB_b16_R_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = SUB;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu.memoryptr[0x0102] = HyperCPU::xl1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010A;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]) = 0x0A0A;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 0x2020;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2), 0x2020 - 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, SUB_b32_R_M){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = SUB;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu.memoryptr[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0103]) = 0x010A;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]) = 0x0A0A0A0A;
    cpu.xRegs[1] = 0x20202020;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.xRegs[1], 0x20202020 - 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, SUB_b8_M_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = SUB;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::xll1;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 0x20;
    *reinterpret_cast<uint8_t*>((char*)&cpu.xRegs[1] + 3) = 0x0A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu.memoryptr[0x010A]), 0x20 - 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, SUB_b16_M_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = SUB;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::xl1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]) = 0x2020;
    *reinterpret_cast<uint16_t*>((char*)&cpu.xRegs[1] + 2) = 0x0A0A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), 0x2020 - 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, SUB_b32_M_R){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = SUB;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::x1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]) = 0x20202020;
    cpu.xRegs[1] = 0x0A0A0A0A;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), 0x20202020 - 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, SUB_b8_M_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = SUB;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::x1;
    cpu.memoryptr[0x0107] = HLT;
    cpu.memoryptr[0x010A] = 0x20;
    cpu.memoryptr[0x010B] = 0x0A;
    cpu.xRegs[1] = 0x010B;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.memoryptr[0x010A], 0x20 - 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, SUB_b16_M_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = SUB;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::x1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]) = 0x2020;
    *reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010C]) = 0x0A0A;
    cpu.xRegs[1] = 0x010C;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu.memoryptr[0x010A]), 0x2020 - 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, SUB_b32_M_RM){
    cpu.Reset(1024);
    cpu.memoryptr[0x0100] = SUB;
    cpu.memoryptr[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0102]) = 0x010A;
    cpu.memoryptr[0x0106] = HyperCPU::x1;
    cpu.memoryptr[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]) = 0x20202020;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010E]) = 0x0A0A0A0A;
    cpu.xRegs[1] = 0x010E;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x010A]), 0x20202020 - 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(IDT, EXCEPTIONS){
    cpu.Reset(16384);
    cpu.CleanUp();    
}