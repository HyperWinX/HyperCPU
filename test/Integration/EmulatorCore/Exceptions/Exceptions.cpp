#include <Core/CPU/Instructions/Registers.hpp>
#include <Core/CPU/Instructions/Flags.hpp>

#include <fixtures.hpp>


TEST_F(EXCEPTION_TEST, CPU_EXCEPTION_IO) {
  cpu.mem_controller->Load16(*cpu.xip, 8273);

  cpu.Run();

  ASSERT_EQ(*cpu.xip, 1539);
}

TEST_F(EXCEPTION_TEST, CPU_EXCEPTION_ZRDIV) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::DIV);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b8 << 4 | HyperCPU::OperandTypes::R);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XLLL0);
  *cpu.xlll0 = 0x55;
  *cpu.x2 = 0;

  cpu.Run();

  ASSERT_EQ(*cpu.xip, 1539);
}
