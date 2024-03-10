#include <gtest/gtest.h>
#include <cpu.hpp>
#include <exitcodes.hpp>
#include <opcodes.hpp>

HyperCPU::CPU cpu;

// TEST(INSTRUCTIONS, ADDITION_WITH_CARRY){
//     cpu.Reset(1024);
//     cpu._memory[0x0100] = ADC;
    
// }

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
    EXPECT_EQ(cpu._fetch_word(), 0x6996);
    EXPECT_EQ(cpu._insp, 0x0102);
    cpu.CleanUp();
}

TEST(SUBFUNCTIONS, _fetch_dword){
    cpu.Reset(1024);
    cpu._memory[0x0100] = 0x69;
    cpu._memory[0x0102] = 0x96;
    EXPECT_EQ(cpu._fetch_dword(), 0x00960069);
    EXPECT_EQ(cpu._insp, 0x0104);
    cpu.CleanUp();
}

TEST(INSTRUCTIONS, HALT){
    cpu.Reset(1024);
    cpu._memory[0x0100] = HLT;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    cpu.CleanUp();
}
