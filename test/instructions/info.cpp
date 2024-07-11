#include <gtest/gtest.h>
#include <test/tests.hpp>
#include <opcodes.hpp>
#include <exitcodes.hpp>

TEST_F(CPU_TESTING, TEST_F_DEV){
    cpu.memoryptr[0x0100] = INFO;
    cpu.memoryptr[0x0101] = HLT;
    cpu.xRegs[31] = 0;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_PRED2([](auto str, auto s1){
        return !strcmp(str, s1);
    }, reinterpret_cast<char*>(&cpu.xRegs[0]), "epyHniWr");
}

TEST_F(CPU_TESTING, TEST_F_VER){
    cpu.memoryptr[0x0100] = INFO;
    cpu.memoryptr[0x0101] = HLT;
    cpu.xRegs[31] = 1;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_PRED2([](auto str, auto s1){
        return !strcmp(str, s1);
    }, reinterpret_cast<char*>(&cpu.xRegs[0]), "a1.0");
}

TEST_F(CPU_TESTING, TEST_F_CPUNAME){
    cpu.memoryptr[0x0100] = INFO;
    cpu.memoryptr[0x0101] = HLT;
    cpu.xRegs[31] = 2;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_PRED2([](auto str, auto s1){
        return !strcmp(str, s1);
    }, reinterpret_cast<char*>(&cpu.xRegs[0]), "epyHUPCr");
}