#include <gtest/gtest.h>
#include <test/tests.hpp>
#include <opcodes.hpp>
#include <exitcodes.hpp>

TEST_F(CPU_TESTING, TEST_F_RET){
    cpu.stp = 0x0200;
    cpu.bstp = 0x0200;
    cpu.memoryptr[0x0100] = CALL;
    *reinterpret_cast<uint32_t*>(&cpu.memoryptr[0x0101]) = 0x0110;
    cpu.memoryptr[0x0105] = HLT;
    cpu.memoryptr[0x0110] = RET;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
    EXPECT_EQ(cpu.insp, 0x0106);
}