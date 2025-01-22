#include <fixtures.hpp>

#include <Core/Compiler.hpp>

TEST_F(ASM_PARSER_STMT_TEST, STMT1) {
    std::string data = "adc x0, x1;";
    HCAsm::CompilerState state;

    state = compiler.TransformToIR(data);

    EXPECT_EQ(state.ir.size(), 1);
    EXPECT_EQ(state.labels.size(), 0);

    auto& instr = std::get<HCAsm::Instruction>(state.ir[0]);
    EXPECT_EQ(instr.opcode, HyperCPU::Opcode::ADC);
    
    EXPECT_EQ(instr.op1.type, HCAsm::OperandType::reg);
    EXPECT_EQ(instr.op1.reg, HyperCPU::Registers::X0);

    EXPECT_EQ(instr.op2.type, HCAsm::OperandType::reg);
    EXPECT_EQ(instr.op2.reg, HyperCPU::Registers::X1);
}

TEST_F(ASM_PARSER_STMT_TEST, STMT2) {
    std::string data = "adc x0;";
    HCAsm::CompilerState state;

    state = compiler.TransformToIR(data);

    EXPECT_EQ(state.ir.size(), 1);
    EXPECT_EQ(state.labels.size(), 0);

    auto& instr = std::get<HCAsm::Instruction>(state.ir[0]);
    EXPECT_EQ(instr.opcode, HyperCPU::Opcode::ADC);
    
    EXPECT_EQ(instr.op1.type, HCAsm::OperandType::reg);
    EXPECT_EQ(instr.op1.reg, HyperCPU::Registers::X0);

    EXPECT_EQ(instr.op2.type, HCAsm::OperandType::none);
}

TEST_F(ASM_PARSER_STMT_TEST, STMT3) {
    std::string data = "adc;";
    HCAsm::CompilerState state;

    state = compiler.TransformToIR(data);

    EXPECT_EQ(state.ir.size(), 1);
    EXPECT_EQ(state.labels.size(), 0);

    auto& instr = std::get<HCAsm::Instruction>(state.ir[0]);
    EXPECT_EQ(instr.opcode, HyperCPU::Opcode::ADC);
    
    EXPECT_EQ(instr.op1.type, HCAsm::OperandType::none);

    EXPECT_EQ(instr.op2.type, HCAsm::OperandType::none);
}

TEST_F(ASM_PARSER_STMT_TEST, LABEL) {
    std::string data = "test:";
    HCAsm::CompilerState state;

    state = compiler.TransformToIR(data);

    EXPECT_EQ(state.ir.size(), 1);
    EXPECT_EQ(state.labels.size(), 1);

    EXPECT_EQ(std::get<HCAsm::Label>(state.ir[0]).index, 0);
}