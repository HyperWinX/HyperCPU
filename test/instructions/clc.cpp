#include <gtest/gtest.h>
#include <test/tests.hpp>
#include <opcodes.hpp>
#include <exitcodes.hpp>

TEST_F(CPU_TESTING, INS_CLC){
    cpu.memoryptr[0x0100] = CLC;
    cpu.memoryptr[0x0101] = HLT;
    cpu.carry_flag = true;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.carry_flag, false);
}