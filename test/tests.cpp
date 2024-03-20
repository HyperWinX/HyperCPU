#include <gtest/gtest.h>
#include <cstdint>
#include <cpu.hpp>
#include <exitcodes.hpp>
#include <opcodes.hpp>

HyperCPU::CPU cpu;

TEST(SUBFUNCTIONS, _fetch_byte){
    cpu.Reset(1024);
    cpu._memory[0x0100] = 0x69;
    ASSERT_EQ(cpu._fetch_byte(), 0x69);
    ASSERT_EQ(cpu._insp, 0x0101);
    cpu.CleanUp();
}

TEST(SUBFUNCTIONS, _fetch_word){
    cpu.Reset(1024);
    cpu._memory[0x0100] = 0x96;
    cpu._memory[0x0101] = 0x69;
    ASSERT_EQ(cpu._fetch_word(), 0x9669);
    ASSERT_EQ(cpu._insp, 0x0102);
    cpu.CleanUp();
}

TEST(SUBFUNCTIONS, _fetch_dword){
    cpu.Reset(1024);
    *reinterpret_cast<uint32_t*>(&cpu._memory[0x0100]) = 0x69009600;
    ASSERT_EQ(cpu._fetch_dword(), 0x69009600);
    ASSERT_EQ(cpu._insp, 0x0104);
    cpu.CleanUp();
}

TEST(SUBFUNCTIONS, _define_instr){
    ASSERT_EQ(cpu._define_instr(ADC), HyperCPU::INS_ADC);
    ASSERT_EQ(cpu._define_instr(AND), HyperCPU::INS_AND);
    ASSERT_EQ(cpu._define_instr(HLT), HyperCPU::INS_HLT);
}

TEST(SUBFUNCTIONS, _set_datasize){

}

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
    *reinterpret_cast<uint8_t*>(&cpu._xRegs[0] + 2) = 0x17;
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
    *reinterpret_cast<uint16_t*>(&cpu._xRegs[0] + 2) = 0x0A0A;
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
    *reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 2) = 0x0A;
    cpu._xRegs[0] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 2), 5 + 0x0A + 1);
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
    *reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2) = 0x0A0A;
    cpu._xRegs[0] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2), 5 + 0x0A0A + 1);
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
    *reinterpret_cast<uint32_t*>(&cpu._xRegs[1]) = 0x0A0A0A0A;
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
    *reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 2) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 2), 5 + 0x0A + 1);
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
    *reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2), 5 + 0x0A0A + 1);
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
    *reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 3) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 3), 5 + 0x0A + 1);
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
    *reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2) = 0x0A0A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2), 5 + 0x0A0A + 1);
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
    *reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 3) = 5;
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
    *reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2) = 5;
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

TEST(INSTRUCTIONS, ADD_b8_RM_R){
    cpu.Reset(1024);
    cpu._memory[0x0100] = ADD;
    cpu._memory[0x0101] = (static_cast<uint8_t>(HyperCPU::b8) << 4) | static_cast<uint8_t>(HyperCPU::RM_R);
    cpu._memory[0x0102] = HyperCPU::x1;
    cpu._memory[0x0103] = HyperCPU::xlh0;
    cpu._memory[0x0104] = HLT;
    cpu._memory[0x010A] = 5;
    *reinterpret_cast<uint8_t*>(&cpu._xRegs[0] + 2) = 0x17;
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
    *reinterpret_cast<uint16_t*>(&cpu._xRegs[0] + 2) = 0x0A0A;
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
    *reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 2) = 0x0A;
    cpu._xRegs[0] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 2), 5 + 0x0A);
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
    *reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2) = 0x0A0A;
    cpu._xRegs[0] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2), 5 + 0x0A0A);
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
    *reinterpret_cast<uint32_t*>(&cpu._xRegs[1]) = 0x0A0A0A0A;
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
    *reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 2) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 2), 5 + 0x0A);
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
    *reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2), 5 + 0x0A0A);
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
    *reinterpret_cast<uint32_t*>(&cpu._xRegs[1]) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._xRegs[1]), 5 + 0x0A0A0A0A);
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
    *reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 3) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 3), 5 + 0x0A);
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
    *reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2) = 0x0A0A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2), 5 + 0x0A0A);
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
    *reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 3) = 5;
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
    *reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2) = 5;
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
    *reinterpret_cast<uint8_t*>(&cpu._xRegs[0] + 2) = 0x17;
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
    *reinterpret_cast<uint16_t*>(&cpu._xRegs[0] + 2) = 0x0A0A;
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
    *reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 2) = 0x0A;
    cpu._xRegs[0] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 2), 5 & 0x0A);
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
    *reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2) = 0x0A0A;
    cpu._xRegs[0] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2), 5 & 0x0A0A);
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
    *reinterpret_cast<uint32_t*>(&cpu._xRegs[1]) = 0x0A0A0A0A;
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
    *reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 2) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 2), 5 & 0x0A);
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
    *reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2), 5 & 0x0A0A);
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
    *reinterpret_cast<uint32_t*>(&cpu._xRegs[1]) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._xRegs[1]), 5 & 0x0A0A0A0A);
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
    *reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 3) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 3), 5 & 0x0A);
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
    *reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2) = 0x0A0A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2), 5 & 0x0A0A);
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
    *reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 3) = 5;
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
    *reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2) = 5;
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
    *reinterpret_cast<uint8_t*>(&cpu._xRegs[0] + 2) = 0x17;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu._memory[0x010A], ~(5 & 0x17));
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
    *reinterpret_cast<uint16_t*>(&cpu._xRegs[0] + 2) = 0x0A0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), ~(5 & 0x0A0A));
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
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._memory[0x010A]), ~(5 & 0x0A0A0A0A));
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
    *reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 2) = 0x0A;
    cpu._xRegs[0] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 2), ~(5 & 0x0A));
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
    *reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2) = 0x0A0A;
    cpu._xRegs[0] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2), ~(5 & 0x0A0A));
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
    *reinterpret_cast<uint32_t*>(&cpu._xRegs[1]) = 0x0A0A0A0A;
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
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._memory[0x010A]), ~(5 & 0x0A));
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
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), ~(5 & 0x0A0A));
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
    *reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 2) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 2), ~(5 & 0x0A));
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
    *reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2), ~(5 & 0x0A0A));
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
    *reinterpret_cast<uint32_t*>(&cpu._xRegs[1]) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu._xRegs[1]), ~(5 & 0x0A0A0A0A));
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
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), ~(5 & 0x0A0A));
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
    *reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 3) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 3), ~(5 & 0x0A));
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
    *reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2) = 0x0A0A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2), ~(5 & 0x0A0A));
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
    *reinterpret_cast<uint8_t*>(&cpu._xRegs[1] + 3) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._memory[0x010A]), ~(5 & 0x0A));
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
    *reinterpret_cast<uint16_t*>(&cpu._xRegs[1] + 2) = 5;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), ~(5 & 0x0A0A));
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
    EXPECT_EQ(*reinterpret_cast<uint8_t*>(&cpu._memory[0x010A]), ~(5 & 0x0A));
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
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), ~(5 & 0x0A0A));
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