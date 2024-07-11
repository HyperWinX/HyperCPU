#include <gtest/gtest.h>
#include <cpu.hpp>

class CPU_TESTING : public ::testing::Test {
    protected:
    HyperCPU::CPU cpu;

    CPU_TESTING() {
        cpu.Reset(16384);
    }
    virtual ~CPU_TESTING() {
        cpu.CleanUp();
    }

    virtual void SetUp(){}
    virtual void TearDown(){}
};