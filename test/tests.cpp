#include <gtest/gtest.h>
#include <cstdint>
#include <cpu.hpp>
#include <exitcodes.hpp>
#include <opcodes.hpp>

HyperCPU::CPU cpu;

TEST(SUBFUNCTIONS, _fetch_byte){
    cpu.Reset(1024);
    cpu._memory[0x0100] = 0x69;
    EXPECT_EQ(cpu._fetch_byte(), 0x69);
    EXPECT_EQ(cpu._insp, 0x0101);
    cpu.CleanUp();
}

TEST(SUBFUNCTIONS, _fetch_word){
    cpu.Reset(1024);
    cpu._memory[0x0100] = 0x96;
    cpu._memory[0x0101] = 0x69;
    EXPECT_EQ(cpu._fetch_word(), 0x9669);
    EXPECT_EQ(cpu._insp, 0x0102);
    cpu.CleanUp();
}

TEST(SUBFUNCTIONS, _fetch_dword){
    cpu.Reset(1024);
    cpu._memory[0x0100] = 0x69;
    cpu._memory[0x0102] = 0x96;
    EXPECT_EQ(cpu._fetch_dword(), 0x69009600);
    EXPECT_EQ(cpu._insp, 0x0104);
    cpu.CleanUp();
}

TEST(SUBFUNCTIONS, _define_instr){
    EXPECT_EQ(cpu._define_instr(ADC), HyperCPU::INS_ADC);
    EXPECT_EQ(cpu._define_instr(AND), HyperCPU::INS_AND);
    EXPECT_EQ(cpu._define_instr(HLT), HyperCPU::INS_HLT);
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
    *reinterpret_cast<uint8_t*>(&cpu._xRegs[0] + 3) = 0x17;
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
    cpu._memory[0x010B] = 5;
    *reinterpret_cast<uint16_t*>(&cpu._xRegs[0] + 2) = 0x0A0A;
    cpu._xRegs[1] = 0x010A;
    cpu._carry = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(*reinterpret_cast<uint16_t*>(&cpu._memory[0x010A]), 5 + 0x0A0A + 1);
    cpu.CleanUp();
}