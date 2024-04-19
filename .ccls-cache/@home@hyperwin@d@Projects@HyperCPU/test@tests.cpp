#include <gtest/gtest.h>
#include <cpu.hpp>
#include <exitcodes.hpp>
#include <opcodes.hpp>

HyperCPU::CPU cpu;

TEST(INSTRUCTIONS, HALT){
    cpu.Reset(1024);
    cpu._memory[0x0100] = HLT;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b8_RM_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = HyperCPU::xlh0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[0] + 2) = 0x17;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._memory[0x010A], 5 + 0x17 + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b16_RM_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = HyperCPU::xl0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[0] + 2) = 0x0A0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), 5 + 0x0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b32_RM_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = HyperCPU::x0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[0] = 0x0A0A0A0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]), 5 + 0x0A0A0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b8_R_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu._memory[0x0102] = HyperCPU::xlh1;
    cpu._memory[0x0103] = HyperCPU::x0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2) = 0x0A;
    cpu._xRegs[0] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2), 5 + 0x0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b16_R_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu._memory[0x0102] = HyperCPU::xl1;
    cpu._memory[0x0103] = HyperCPU::x0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2) = 0x0A0A;
    cpu._xRegs[0] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2), 5 + 0x0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b32_R_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = HyperCPU::x0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[1] = 0x0A0A0A0A;
    cpu._xRegs[0] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._xRegs[1], 5 + 0x0A0A0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b8_RM_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._memory[0x010A]), 5 + 0x0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b16_RM_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0104] = 0x0A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), 5 + 0x0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b32_RM_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0104] = 0x0A;
    cpu._memory[0x0105] = 0x0A;
    cpu._memory[0x0106] = 0x0A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]), 5 + 0x0A0A0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b8_R_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu._memory[0x0102] = HyperCPU::xlh1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2), 5 + 0x0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b16_R_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu._memory[0x0102] = HyperCPU::xl1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0104] = 0x0A;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2), 5 + 0x0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b32_R_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0104] = 0x0A;
    cpu._memory[0x0105] = 0x0A;
    cpu._memory[0x0106] = 0x0A;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu._xRegs[1]) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._xRegs[1]), 5 + 0x0A0A0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b8_RM_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu._memory[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010B;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._memory[0x010B] = 0x0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._memory[0x010A], 5 + 0x0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b16_RM_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu._memory[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010C;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint16_t*>(&cpu._memory[0x010C]) = 0x0A0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), 5 + 0x0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b32_RM_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu._memory[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010E;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010E]) = 0x0A0A0A0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]), 5 + 0x0A0A0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b8_R_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu._memory[0x0102] = HyperCPU::xll1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 0x0A;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 3) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 3), 5 + 0x0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b16_R_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu._memory[0x0102] = HyperCPU::xl1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2) = 0x0A0A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2), 5 + 0x0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b32_R_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu._memory[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[1] = 0x0A0A0A0A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._xRegs[1], 5 + 0x0A0A0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b8_M_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::xll1;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 0x0A;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 3) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._memory[0x010A]), 5 + 0x0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b16_M_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::xl1;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]) = 0x0A0A;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), 5 + 0x0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b32_M_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::x1;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]) = 0x0A0A0A0A;
    cpu._xRegs[1] = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]), 5 + 0x0A0A0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b8_M_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::x1;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]) = 0x0A;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010E]) = 5;
    cpu._xRegs[1] = 0x010E;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._memory[0x010A]), 5 + 0x0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b16_M_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::x1;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]) = 0x0A0A;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010E]) = 5;
    cpu._xRegs[1] = 0x010E;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), 5 + 0x0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b32_M_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::x1;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]) = 0x0A0A0A0A;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010E]) = 5;
    cpu._xRegs[1] = 0x010E;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]), 5 + 0x0A0A0A0A + 1);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b8_R_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_R);
    cpu._memory[0x0102] = HyperCPU::xlh1;
    cpu._memory[0x0103] = HyperCPU::xll0;
    cpu._memory[0x0104] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2) = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[0] + 3) = 10;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2), 16);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b16_R_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_R);
    cpu._memory[0x0102] = HyperCPU::xl1;
    cpu._memory[0x0103] = HyperCPU::xh0;
    cpu._memory[0x0104] = HLT;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2) = 5;
    *reinterpret_cast<uint16_t*>(&cpu._xRegs[0]) = 10;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2), 16);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADDWITHCARRY_b32_R_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADC;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_R);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = HyperCPU::x0;
    cpu._memory[0x0104] = HLT;
    cpu._xRegs[1] = 5;
    cpu._xRegs[0] = 10;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._xRegs[1], 16);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b8_RM_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADD;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = HyperCPU::xlh0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[0] + 2) = 0x17;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._memory[0x010A], 5 + 0x17);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b16_RM_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADD;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = HyperCPU::xl0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[0] + 2) = 0x0A0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), 5 + 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b32_RM_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADD;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = HyperCPU::x0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[0] = 0x0A0A0A0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]), 5 + 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b8_R_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADD;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu._memory[0x0102] = HyperCPU::xlh1;
    cpu._memory[0x0103] = HyperCPU::x0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2) = 0x0A;
    cpu._xRegs[0] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2), 5 + 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b16_R_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADD;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu._memory[0x0102] = HyperCPU::xl1;
    cpu._memory[0x0103] = HyperCPU::x0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2) = 0x0A0A;
    cpu._xRegs[0] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2), 5 + 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b32_R_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADD;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = HyperCPU::x0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[1] = 0x0A0A0A0A;
    cpu._xRegs[0] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._xRegs[1], 5 + 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b8_RM_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADD;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._memory[0x010A]), 5 + 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b16_RM_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADD;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0104] = 0x0A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), 5 + 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b32_RM_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADD;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0104] = 0x0A;
    cpu._memory[0x0105] = 0x0A;
    cpu._memory[0x0106] = 0x0A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]), 5 + 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b8_R_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADD;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu._memory[0x0102] = HyperCPU::xlh1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2), 5 + 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b16_R_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADD;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu._memory[0x0102] = HyperCPU::xl1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0104] = 0x0A;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2), 5 + 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b32_R_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADD;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0104] = 0x0A;
    cpu._memory[0x0105] = 0x0A;
    cpu._memory[0x0106] = 0x0A;
    cpu._memory[0x0107] = HLT;
    cpu._xRegs[1] = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._xRegs[1], 5 + 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b8_RM_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADD;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu._memory[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010B;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._memory[0x010B] = 0x0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._memory[0x010A], 5 + 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b16_RM_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADD;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu._memory[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010C;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint16_t*>(&cpu._memory[0x010C]) = 0x0A0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), 5 + 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b32_RM_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADD;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu._memory[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010E;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010E]) = 0x0A0A0A0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]), 5 + 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b8_R_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADD;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu._memory[0x0102] = HyperCPU::xll1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 0x0A;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 3) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 3), 5 + 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b16_R_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADD;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu._memory[0x0102] = HyperCPU::xl1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2) = 0x0A0A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2), 5 + 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b32_R_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADD;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu._memory[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[1] = 0x0A0A0A0A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._xRegs[1], 5 + 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b8_M_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADD;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::xll1;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 0x0A;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 3) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._memory[0x010A]), 5 + 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b16_M_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADD;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::xl1;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]) = 0x0A0A;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), 5 + 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b32_M_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADD;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::x1;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]) = 0x0A0A0A0A;
    cpu._xRegs[1] = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]), 5 + 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b8_M_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADD;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::x1;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]) = 0x0A;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010E]) = 5;
    cpu._xRegs[1] = 0x010E;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._memory[0x010A]), 5 + 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b16_M_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADD;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::x1;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]) = 0x0A0A;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010E]) = 5;
    cpu._xRegs[1] = 0x010E;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), 5 + 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ADD_b32_M_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADD;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::x1;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]) = 0x0A0A0A0A;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010E]) = 5;
    cpu._xRegs[1] = 0x010E;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]), 5 + 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b8_RM_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = AND;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = HyperCPU::xlh0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[0] + 2) = 0x17;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._memory[0x010A], 5 & 0x17);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b16_RM_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = AND;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = HyperCPU::xl0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[0] + 2) = 0x0A0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), 5 & 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b32_RM_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = AND;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = HyperCPU::x0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[0] = 0x0A0A0A0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]), 5 & 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b8_R_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = AND;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu._memory[0x0102] = HyperCPU::xlh1;
    cpu._memory[0x0103] = HyperCPU::x0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2) = 0x0A;
    cpu._xRegs[0] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2), 5 & 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b16_R_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = AND;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu._memory[0x0102] = HyperCPU::xl1;
    cpu._memory[0x0103] = HyperCPU::x0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2) = 0x0A0A;
    cpu._xRegs[0] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2), 5 & 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b32_R_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = AND;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = HyperCPU::x0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[1] = 0x0A0A0A0A;
    cpu._xRegs[0] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._xRegs[1], 5 & 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b8_RM_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = AND;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._memory[0x010A]), 5 & 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b16_RM_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = AND;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0104] = 0x0A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), 5 & 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b32_RM_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = AND;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0104] = 0x0A;
    cpu._memory[0x0105] = 0x0A;
    cpu._memory[0x0106] = 0x0A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]), 5 & 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b8_R_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = AND;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu._memory[0x0102] = HyperCPU::xlh1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2), 5 & 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b16_R_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = AND;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu._memory[0x0102] = HyperCPU::xl1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0104] = 0x0A;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2), 5 & 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b32_R_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = AND;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0104] = 0x0A;
    cpu._memory[0x0105] = 0x0A;
    cpu._memory[0x0106] = 0x0A;
    cpu._memory[0x0107] = HLT;
    cpu._xRegs[1] = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._xRegs[1], 5 & 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b8_RM_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = AND;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu._memory[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010B;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._memory[0x010B] = 0x0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._memory[0x010A], 5 & 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b16_RM_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = AND;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu._memory[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010C;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint16_t*>(&cpu._memory[0x010C]) = 0x0A0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), 5 & 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b32_RM_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = AND;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu._memory[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010E;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010E]) = 0x0A0A0A0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]), 5 & 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b8_R_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = AND;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu._memory[0x0102] = HyperCPU::xll1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 0x0A;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 3) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 3), 5 & 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b16_R_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = AND;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu._memory[0x0102] = HyperCPU::xl1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2) = 0x0A0A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2), 5 & 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b32_R_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = AND;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu._memory[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[1] = 0x0A0A0A0A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._xRegs[1], 5 & 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b8_M_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = AND;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::xll1;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 0x0A;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 3) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._memory[0x010A]), 5 & 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b16_M_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = AND;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::xl1;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]) = 0x0A0A;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), 5 & 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b32_M_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = AND;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::x1;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]) = 0x0A0A0A0A;
    cpu._xRegs[1] = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]), 5 & 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b8_M_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = AND;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::x1;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]) = 0x0A;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010E]) = 5;
    cpu._xRegs[1] = 0x010E;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._memory[0x010A]), 5 & 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b16_M_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = AND;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::x1;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]) = 0x0A0A;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010E]) = 5;
    cpu._xRegs[1] = 0x010E;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), 5 & 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, AND_b32_M_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = AND;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::x1;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]) = 0x0A0A0A0A;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010E]) = 5;
    cpu._xRegs[1] = 0x010E;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]), 5 & 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b8_RM_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ANDN;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = HyperCPU::xlh0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[0] + 2) = 0x17;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._memory[0x010A], static_cast<unsigned>(~(5 & 0x17)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b16_RM_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ANDN;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = HyperCPU::xl0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[0] + 2) = 0x0A0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), static_cast<uint16_t>(~(5 & 0x0A0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b32_RM_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ANDN;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = HyperCPU::x0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[0] = 0x0A0A0A0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]), static_cast<uint32_t>(~(5 & 0x0A0A0A0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b8_R_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ANDN;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu._memory[0x0102] = HyperCPU::xlh1;
    cpu._memory[0x0103] = HyperCPU::x0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2) = 0x0A;
    cpu._xRegs[0] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2), static_cast<uint8_t>(~(5 & 0x0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b16_R_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ANDN;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu._memory[0x0102] = HyperCPU::xl1;
    cpu._memory[0x0103] = HyperCPU::x0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2) = 0x0A0A;
    cpu._xRegs[0] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2), static_cast<uint16_t>(~(5 & 0x0A0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b32_R_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ANDN;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = HyperCPU::x0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[1] = 0x0A0A0A0A;
    cpu._xRegs[0] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._xRegs[1], ~(5 & 0x0A0A0A0A));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b8_RM_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ANDN;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._memory[0x010A]), static_cast<uint8_t>(~(5 & 0x0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b16_RM_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ANDN;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0104] = 0x0A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), static_cast<uint16_t>(~(5 & 0x0A0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b32_RM_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ANDN;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0104] = 0x0A;
    cpu._memory[0x0105] = 0x0A;
    cpu._memory[0x0106] = 0x0A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]), ~(5 & 0x0A0A0A0A));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b8_R_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ANDN;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu._memory[0x0102] = HyperCPU::xlh1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2), static_cast<uint8_t>(~(5 & 0x0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b16_R_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ANDN;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu._memory[0x0102] = HyperCPU::xl1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0104] = 0x0A;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2), static_cast<uint16_t>(~(5 & 0x0A0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b32_R_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ANDN;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0104] = 0x0A;
    cpu._memory[0x0105] = 0x0A;
    cpu._memory[0x0106] = 0x0A;
    cpu._memory[0x0107] = HLT;
    cpu._xRegs[1] = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._xRegs[1], ~(5 & 0x0A0A0A0A));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b8_RM_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ANDN;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu._memory[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010B;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._memory[0x010B] = 0x0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._memory[0x010A], ~(5 & 0x0A));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b16_RM_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ANDN;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu._memory[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010C;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint16_t*>(&cpu._memory[0x010C]) = 0x0A0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), static_cast<uint16_t>(~(5 & 0x0A0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b32_RM_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ANDN;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu._memory[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010E;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010E]) = 0x0A0A0A0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]), ~(5 & 0x0A0A0A0A));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b8_R_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ANDN;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu._memory[0x0102] = HyperCPU::xll1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 0x0A;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 3) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 3), static_cast<uint8_t>(~(5 & 0x0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b16_R_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ANDN;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu._memory[0x0102] = HyperCPU::xl1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2) = 0x0A0A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2), static_cast<uint16_t>(~(5 & 0x0A0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b32_R_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ANDN;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu._memory[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[1] = 0x0A0A0A0A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._xRegs[1], ~(5 & 0x0A0A0A0A));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b8_M_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ANDN;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::xll1;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 0x0A;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 3) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._memory[0x010A]), static_cast<uint8_t>(~(5 & 0x0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b16_M_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ANDN;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::xl1;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]) = 0x0A0A;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), static_cast<uint16_t>(~(5 & 0x0A0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b32_M_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ANDN;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::x1;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]) = 0x0A0A0A0A;
    cpu._xRegs[1] = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]), ~(5 & 0x0A0A0A0A));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b8_M_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ANDN;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::x1;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]) = 0x0A;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010E]) = 5;
    cpu._xRegs[1] = 0x010E;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._memory[0x010A]), static_cast<uint8_t>(~(5 & 0x0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b16_M_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ANDN;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::x1;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]) = 0x0A0A;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010E]) = 5;
    cpu._xRegs[1] = 0x010E;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), static_cast<uint16_t>(~(5 & 0x0A0A)));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, ANDN_b32_M_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ANDN;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::x1;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]) = 0x0A0A0A0A;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010E]) = 5;
    cpu._xRegs[1] = 0x010E;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]), ~(5 & 0x0A0A0A0A));
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, INS_CLC){
    cpu.Reset(1024);
    cpu._memory[0x0100] = CLC;
    cpu._memory[0x0101] = HLT;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._carry, false);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, INC_b8_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = INC;
    cpu._memory[0x0101] = ((static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M));
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x0107;
    cpu._memory[0x0106] = HLT;
    cpu._memory[0x0107] = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._memory[0x0107], 11);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, INC_b16_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = INC;
    cpu._memory[0x0101] = ((static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M));
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x0107;
    cpu._memory[0x0106] = HLT;
    *reinterpret_cast<uint16_t*>(&cpu._memory[0x0107]) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x0107]), 11);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, INC_b32_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = INC;
    cpu._memory[0x0101] = ((static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M));
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x0107;
    cpu._memory[0x0106] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0107]) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x0107]), 11);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, INC_b8_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = INC;
    cpu._memory[0x0101] = ((static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R));
    cpu._memory[0x0102] = HyperCPU::xlh0;
    cpu._memory[0x0103] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[0] + 2) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[0] + 2), 11);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, INC_b16_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = INC;
    cpu._memory[0x0101] = ((static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R));
    cpu._memory[0x0102] = HyperCPU::xl0;
    cpu._memory[0x0103] = HLT;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[0] + 2) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[0] + 2), 11);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, INC_b32_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = INC;
    cpu._memory[0x0101] = ((static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R));
    cpu._memory[0x0102] = HyperCPU::x0;
    cpu._memory[0x0103] = HLT;
    cpu._xRegs[0] = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._xRegs[0], 11);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, DEC_b8_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = DEC;
    cpu._memory[0x0101] = ((static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M));
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x0107;
    cpu._memory[0x0106] = HLT;
    cpu._memory[0x0107] = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._memory[0x0107], 9);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, DEC_b16_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = DEC;
    cpu._memory[0x0101] = ((static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M));
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x0107;
    cpu._memory[0x0106] = HLT;
    *reinterpret_cast<uint16_t*>(&cpu._memory[0x0107]) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x0107]), 9);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, DEC_b32_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = DEC;
    cpu._memory[0x0101] = ((static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M));
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x0107;
    cpu._memory[0x0106] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0107]) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x0107]), 9);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, DEC_b8_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = DEC;
    cpu._memory[0x0101] = ((static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R));
    cpu._memory[0x0102] = HyperCPU::xlh0;
    cpu._memory[0x0103] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[0] + 2) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[0] + 2), 9);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, DEC_b16_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = DEC;
    cpu._memory[0x0101] = ((static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R));
    cpu._memory[0x0102] = HyperCPU::xl0;
    cpu._memory[0x0103] = HLT;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[0] + 2) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[0] + 2), 9);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, DEC_b32_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = DEC;
    cpu._memory[0x0101] = ((static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R));
    cpu._memory[0x0102] = HyperCPU::x0;
    cpu._memory[0x0103] = HLT;
    cpu._xRegs[0] = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._xRegs[0], 9);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b8_RM_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = MOV;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = HyperCPU::xlh0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[0] + 2) = 0x17;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._memory[0x010A], 0x17);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b16_RM_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = MOV;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = HyperCPU::xl0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[0] + 2) = 0x0A0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b32_RM_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = MOV;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = HyperCPU::x0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[0] = 0x0A0A0A0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]), 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b8_R_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = MOV;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu._memory[0x0102] = HyperCPU::xlh1;
    cpu._memory[0x0103] = HyperCPU::x0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2) = 0x0A;
    cpu._xRegs[0] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2), 5);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b16_R_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = MOV;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu._memory[0x0102] = HyperCPU::xl1;
    cpu._memory[0x0103] = HyperCPU::x0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2) = 0x0A0A;
    cpu._xRegs[0] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2), 5);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b32_R_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = MOV;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_RM);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = HyperCPU::x0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[1] = 0x0A0A0A0A;
    cpu._xRegs[0] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._xRegs[1], 5);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b8_RM_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = MOV;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._memory[0x010A]), 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b16_RM_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = MOV;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0104] = 0x0A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b32_RM_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = MOV;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_IMM);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0104] = 0x0A;
    cpu._memory[0x0105] = 0x0A;
    cpu._memory[0x0106] = 0x0A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]), 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b8_R_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = MOV;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu._memory[0x0102] = HyperCPU::xlh1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2), 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b16_R_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = MOV;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu._memory[0x0102] = HyperCPU::xl1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0104] = 0x0A;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2), 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b32_R_IMM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = MOV;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_IMM);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = 0x0A;
    cpu._memory[0x0104] = 0x0A;
    cpu._memory[0x0105] = 0x0A;
    cpu._memory[0x0106] = 0x0A;
    cpu._memory[0x0107] = HLT;
    cpu._xRegs[1] = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._xRegs[1], 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b8_RM_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = MOV;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu._memory[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010B;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._memory[0x010B] = 0x0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._memory[0x010A], 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b16_RM_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = MOV;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu._memory[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010C;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint16_t*>(&cpu._memory[0x010C]) = 0x0A0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), 0x0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b32_RM_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = MOV;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::RM_M);
    cpu._memory[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010E;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010E]) = 0x0A0A0A0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]), 0x0A0A0A0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b8_R_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = MOV;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu._memory[0x0102] = HyperCPU::xll1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 0x0A;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 3) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 3), 0x0A);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b16_R_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = MOV;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu._memory[0x0102] = HyperCPU::xl1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2) = 0x0A0A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2), 5);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b32_R_M){
    cpu.Reset(1024);
    cpu._memory[0x0100] = MOV;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_M);
    cpu._memory[0x0102] = HyperCPU::x1;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0103]) = 0x010A;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 5;
    cpu._xRegs[1] = 0x0A0A0A0A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._xRegs[1], 5);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b8_M_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = MOV;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::xll1;
    cpu._memory[0x0107] = HLT;
    cpu._memory[0x010A] = 0x0A;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 3) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._memory[0x010A]), 5);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b16_M_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = MOV;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::xl1;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]) = 0x0A0A;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), 5);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b32_M_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = MOV;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M_R);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::x1;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]) = 0x0A0A0A0A;
    cpu._xRegs[1] = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]), 5);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b8_M_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = MOV;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::x1;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]) = 0x0A;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010E]) = 5;
    cpu._xRegs[1] = 0x010E;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._memory[0x010A]), 5);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b16_M_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = MOV;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::x1;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]) = 0x0A0A;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010E]) = 5;
    cpu._xRegs[1] = 0x010E;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), 5);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, MOV_b32_M_RM){
    cpu.Reset(1024);
    cpu._memory[0x0100] = MOV;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::M_RM);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0102]) = 0x010A;
    cpu._memory[0x0106] = HyperCPU::x1;
    cpu._memory[0x0107] = HLT;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]) = 0x0A0A0A0A;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x010E]) = 5;
    cpu._xRegs[1] = 0x010E;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]), 5);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, INS_CALL){
    cpu.Reset(1024);
    cpu._bstp = 0x0200;
    cpu._stp = 0x0200;
    cpu._memory[0x0100] = CALL;
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0101]) = 0x0110;
    cpu._memory[0x0110] = HLT;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._insp, 0x0111);
    EXPECT_EQ(cpu._stp, 0x0200 - 4);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[cpu._stp]), 0x0105);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, PUSH_b8_R){
    cpu.Reset(1024);
    cpu._bstp = 0x0200;
    cpu._stp = 0x0200;
    cpu._memory[0x0100] = PUSH;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R);
    cpu._memory[0x0102] = HyperCPU::xlh0;
    cpu._memory[0x0103] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[0] + 2) = 0xA6;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._stp, 0x0200 - 1);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(cpu._memory + cpu._stp), 0xA6);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, PUSH_b16_R){
    cpu.Reset(1024);
    cpu._bstp = 0x0200;
    cpu._stp = 0x0200;
    cpu._memory[0x0100] = PUSH;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R);
    cpu._memory[0x0102] = HyperCPU::xl0;
    cpu._memory[0x0103] = HLT;
    *reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[0] + 2) = 0xA6A6;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._stp, 0x0200 - 2);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(cpu._memory + cpu._stp), 0xA6A6);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, PUSH_b32_R){
    cpu.Reset(1024);
    cpu._bstp = 0x0200;
    cpu._stp = 0x0200;
    cpu._memory[0x0100] = PUSH;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R);
    cpu._memory[0x0102] = HyperCPU::x0;
    cpu._memory[0x0103] = HLT;
    cpu._xRegs[0] = 0xA6A6A6A6;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._stp, 0x0200 - 4);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(cpu._memory + cpu._stp), 0xA6A6A6A6);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, PUSH_b8_IMM){
    cpu.Reset(1024);
    cpu._bstp = 0x0200;
    cpu._stp = 0x0200;
    cpu._memory[0x0100] = PUSH;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::IMM);
    *reinterpret_cast<uint8_t*>(cpu._memory + 0x0102) = 0xA6;
    cpu._memory[0x0103] = HLT;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._stp, 0x0200 - 1);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(cpu._memory + cpu._stp), 0xA6);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, PUSH_b16_IMM){
    cpu.Reset(1024);
    cpu._bstp = 0x0200;
    cpu._stp = 0x0200;
    cpu._memory[0x0100] = PUSH;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::IMM);
    *reinterpret_cast<uint16_t*>(cpu._memory + 0x0102) = 0xA6A6;
    cpu._memory[0x0104] = HLT;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._stp, 0x0200 - 2);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(cpu._memory + cpu._stp), 0xA6A6);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, PUSH_b32_IMM){
    cpu.Reset(1024);
    cpu._bstp = 0x0200;
    cpu._stp = 0x0200;
    cpu._memory[0x0100] = PUSH;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::IMM);
    *reinterpret_cast<uint32_t*>(cpu._memory + 0x0102) = 0xA6A6A6A6;
    cpu._memory[0x0106] = HLT;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._stp, 0x0200 - 4);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(cpu._memory + cpu._stp), 0xA6A6A6A6);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, POP_b8_R){
    cpu.Reset(1024);
    cpu._bstp = 0x0200;
    cpu._stp = 0x0200;
    cpu._memory[0x0100] = PUSH;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::IMM);
    cpu._memory[0x0102] = 0xA0;
    cpu._memory[0x0103] = POP;
    cpu._memory[0x0104] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R);
    cpu._memory[0x0105] = HyperCPU::xlh1;
    cpu._memory[0x0106] = HLT;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._stp, 0x0200);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2), 0xA0);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, POP_b16_R){
    cpu.Reset(1024);
    cpu._bstp = 0x0200;
    cpu._stp = 0x0200;
    cpu._memory[0x0100] = PUSH;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::IMM);
    cpu._memory[0x0102] = 0xA0;
    cpu._memory[0x0103] = 0xA0;
    cpu._memory[0x0104] = POP;
    cpu._memory[0x0105] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R);
    cpu._memory[0x0106] = HyperCPU::xl1;
    cpu._memory[0x0107] = HLT;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._stp, 0x0200);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>((char*)&cpu._xRegs[1] + 2), 0xA0A0);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, POP_b32_R){
    cpu.Reset(1024);
    cpu._bstp = 0x0200;
    cpu._stp = 0x0200;
    cpu._memory[0x0100] = PUSH;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::IMM);
    cpu._memory[0x0102] = 0xA0;
    cpu._memory[0x0103] = 0xA0;
    cpu._memory[0x0104] = 0xA0;
    cpu._memory[0x0105] = 0xA0;
    cpu._memory[0x0106] = POP;
    cpu._memory[0x0107] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R);
    cpu._memory[0x0108] = HyperCPU::x1;
    cpu._memory[0x0109] = HLT;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._stp, 0x0200);
    EXPECT_EQ(cpu._xRegs[1], 0xA0A0A0A0);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, CMP_b8_R_R_LESS){
    cpu.Reset(1024);
    cpu._memory[0x0100] = CMP;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_R);
    cpu._memory[0x0102] = static_cast<uint8_t>(HyperCPU::xlh1);
    cpu._memory[0x0103] = static_cast<uint8_t>(HyperCPU::xll0);
    cpu._memory[0x0104] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2) = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[0] + 3) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._cmpr, false);
    EXPECT_EQ(cpu._carry, false);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, CMP_b8_R_R_BIGGER){
    cpu.Reset(1024);
    cpu._memory[0x0100] = CMP;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_R);
    cpu._memory[0x0102] = static_cast<uint8_t>(HyperCPU::xlh1);
    cpu._memory[0x0103] = static_cast<uint8_t>(HyperCPU::xll0);
    cpu._memory[0x0104] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2) = 50;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[0] + 3) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._cmpr, false);
    EXPECT_EQ(cpu._carry, true);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, CMP_b8_R_R_EQ){
    cpu.Reset(1024);
    cpu._memory[0x0100] = CMP;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::R_R);
    cpu._memory[0x0102] = static_cast<uint8_t>(HyperCPU::xlh1);
    cpu._memory[0x0103] = static_cast<uint8_t>(HyperCPU::xll0);
    cpu._memory[0x0104] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2) = 50;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[0] + 3) = 50;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._cmpr, true);
    EXPECT_EQ(cpu._carry, false);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, CMP_b16_R_R_LESS){
    cpu.Reset(1024);
    cpu._memory[0x0100] = CMP;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_R);
    cpu._memory[0x0102] = static_cast<uint8_t>(HyperCPU::xl1);
    cpu._memory[0x0103] = static_cast<uint8_t>(HyperCPU::xl0);
    cpu._memory[0x0104] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2) = 5;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[0] + 2) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._cmpr, false);
    EXPECT_EQ(cpu._carry, false);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, CMP_b16_R_R_BIGGER){
    cpu.Reset(1024);
    cpu._memory[0x0100] = CMP;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_R);
    cpu._memory[0x0102] = static_cast<uint8_t>(HyperCPU::xl1);
    cpu._memory[0x0103] = static_cast<uint8_t>(HyperCPU::xl0);
    cpu._memory[0x0104] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2) = 50;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[0] + 2) = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._cmpr, false);
    EXPECT_EQ(cpu._carry, true);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, CMP_b16_R_R_EQ){
    cpu.Reset(1024);
    cpu._memory[0x0100] = CMP;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b16) << 4) | static_cast<uint8_t>(HyperCPU::R_R);
    cpu._memory[0x0102] = static_cast<uint8_t>(HyperCPU::xl1);
    cpu._memory[0x0103] = static_cast<uint8_t>(HyperCPU::xl0);
    cpu._memory[0x0104] = HLT;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[1] + 2) = 50;
    *reinterpret_cast<uint8_t*>((char*)&cpu._xRegs[0] + 2) = 50;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._cmpr, true);
    EXPECT_EQ(cpu._carry, false);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, CMP_b32_R_R_LESS){
    cpu.Reset(1024);
    cpu._memory[0x0100] = CMP;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_R);
    cpu._memory[0x0102] = static_cast<uint8_t>(HyperCPU::x1);
    cpu._memory[0x0103] = static_cast<uint8_t>(HyperCPU::x0);
    cpu._memory[0x0104] = HLT;
    cpu._xRegs[1] = 5;
    cpu._xRegs[0] = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._cmpr, false);
    EXPECT_EQ(cpu._carry, false);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, CMP_b32_R_R_BIGGER){
    cpu.Reset(1024);
    cpu._memory[0x0100] = CMP;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_R);
    cpu._memory[0x0102] = static_cast<uint8_t>(HyperCPU::x1);
    cpu._memory[0x0103] = static_cast<uint8_t>(HyperCPU::x0);
    cpu._memory[0x0104] = HLT;
    cpu._xRegs[1] = 50;
    cpu._xRegs[0] = 10;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._cmpr, false);
    EXPECT_EQ(cpu._carry, true);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, CMP_b32_R_R_EQ){
    cpu.Reset(1024);
    cpu._memory[0x0100] = CMP;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b32) << 4) | static_cast<uint8_t>(HyperCPU::R_R);
    cpu._memory[0x0102] = static_cast<uint8_t>(HyperCPU::x1);
    cpu._memory[0x0103] = static_cast<uint8_t>(HyperCPU::x0);
    cpu._memory[0x0104] = HLT;
    cpu._xRegs[1] = 50;
    cpu._xRegs[0] = 50;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._cmpr, true);
    EXPECT_EQ(cpu._carry, false);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, BSWP_b16){
    cpu.Reset(1024);
    cpu._memory[0x0100] = BSWP;
    cpu.CleanUp();  
}