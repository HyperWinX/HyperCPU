#include <gtest/gtest.h>
#include <test/tests.hpp>
#include <opcodes.hpp>
#include <exitcodes.hpp>

TEST_F(CPU_TESTING, INS_CALL){
    cpu.bstp = 0x0200;
    cpu.stp = 0x0200;
    cpu.memoryptr[0x0100] = CALL;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0101]) = 0x0110;
    cpu.memoryptr[0x0110] = HLT;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.insp, 0x0111);
    EXPECT_EQ(cpu.stp, 0x0200 - 4);
    EXPECT_EQ(*reinterpret_cast<uint32_t*>(&cpu.memoryptr[cpu.stp]), 0x0105);
}