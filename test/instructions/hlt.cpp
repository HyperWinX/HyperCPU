#include <gtest/gtest.h>
#include <test/tests.hpp>
#include <opcodes.hpp>
#include <exitcodes.hpp>

TEST_F(CPU_TESTING, HALT){
    cpu.memoryptr[0x0100] = HLT;
    EXPECT_EQ(cpu.Execute(), EXIT_HALT);
}