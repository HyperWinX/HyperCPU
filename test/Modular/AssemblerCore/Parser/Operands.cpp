#include <fixtures.hpp>

TEST_F(ASM_PARSER_TEST, OPERAND1) {
    std::string data = "[15FAh]";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, HCAsm::OperandType::memaddr_int);
    EXPECT_EQ(operand.uint1, static_cast<std::uint64_t>(0x15FA));
}

TEST_F(ASM_PARSER_TEST, OPERAND2) {
    std::string data = "[x0]";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, HCAsm::OperandType::memaddr_reg);
    EXPECT_EQ(operand.reg, HyperCPU::Registers::X0);
}

TEST_F(ASM_PARSER_TEST, OPERAND3_1) {
    std::string data = "[x0 + 15u]";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, HCAsm::OperandType::mem_reg_add_int);
    EXPECT_EQ(operand.reg, HyperCPU::Registers::X0);
    EXPECT_EQ(operand.uint1, static_cast<std::uint64_t>(15));
}

TEST_F(ASM_PARSER_TEST, OPERAND3_2) {
    std::string data = "[x0 + 15h]";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, HCAsm::OperandType::mem_reg_add_int);
    EXPECT_EQ(operand.reg, HyperCPU::Registers::X0);
    EXPECT_EQ(operand.uint1, static_cast<std::uint64_t>(0x15));
}

TEST_F(ASM_PARSER_TEST, OPERAND3_3) {
    std::string data = "[x0 + 00110101b]";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, HCAsm::OperandType::mem_reg_add_int);
    EXPECT_EQ(operand.reg, HyperCPU::Registers::X0);
    EXPECT_EQ(operand.uint1, static_cast<std::uint64_t>(0b00110101));
}

TEST_F(ASM_PARSER_TEST, OPERAND4) {
    std::string data = "b8 ptr [15FAh]";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, HCAsm::OperandType::memaddr_int);
    EXPECT_EQ(operand.mode, HCAsm::Mode::b8);
    EXPECT_EQ(operand.uint1, static_cast<std::uint64_t>(0x15FA));
}

TEST_F(ASM_PARSER_TEST, OPERAND5) {
    std::string data = "b16 ptr [x0]";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, HCAsm::OperandType::memaddr_reg);
    EXPECT_EQ(operand.mode, HCAsm::Mode::b16);
    EXPECT_EQ(operand.reg, HyperCPU::Registers::X0);
}

TEST_F(ASM_PARSER_TEST, OPERAND6_1) {
    std::string data = "b32 ptr [x0 + 15u]";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, HCAsm::OperandType::mem_reg_add_int);
    EXPECT_EQ(operand.reg, HyperCPU::Registers::X0);
    EXPECT_EQ(operand.mode, HCAsm::Mode::b32);
    EXPECT_EQ(operand.uint1, static_cast<std::uint64_t>(15));
}

TEST_F(ASM_PARSER_TEST, OPERAND6_2) {
    std::string data = "b8 ptr [x0 + 15h]";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, HCAsm::OperandType::mem_reg_add_int);
    EXPECT_EQ(operand.reg, HyperCPU::Registers::X0);
    EXPECT_EQ(operand.mode, HCAsm::Mode::b8);
    EXPECT_EQ(operand.uint1, static_cast<std::uint64_t>(0x15));
}

TEST_F(ASM_PARSER_TEST, OPERAND6_3) {
    std::string data = "b32 ptr [x0 + 00110101b]";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, HCAsm::OperandType::mem_reg_add_int);
    EXPECT_EQ(operand.reg, HyperCPU::Registers::X0);
    EXPECT_EQ(operand.mode, HCAsm::Mode::b32);
    EXPECT_EQ(operand.uint1, static_cast<std::uint64_t>(0b00110101));
}

TEST_F(ASM_PARSER_TEST, OPERAND7) {
    std::string data = "15s";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, HCAsm::OperandType::sint);
    EXPECT_EQ(operand.mode, HCAsm::Mode::none);
    EXPECT_EQ(operand.sint2, static_cast<std::int64_t>(15));
}

TEST_F(ASM_PARSER_TEST, OPERAND8_1) {
    std::string data = "15u";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, HCAsm::OperandType::uint);
    EXPECT_EQ(operand.mode, HCAsm::Mode::none);
    EXPECT_EQ(operand.uint1, static_cast<std::uint64_t>(15));
}

TEST_F(ASM_PARSER_TEST, OPERAND8_2) {
    std::string data = "15h";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, HCAsm::OperandType::uint);
    EXPECT_EQ(operand.mode, HCAsm::Mode::none);
    EXPECT_EQ(operand.uint1, static_cast<std::uint64_t>(0x15));
}

TEST_F(ASM_PARSER_TEST, OPERAND8_3) {
    std::string data = "00110101b";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, HCAsm::OperandType::uint);
    EXPECT_EQ(operand.mode, HCAsm::Mode::none);
    EXPECT_EQ(operand.uint1, static_cast<std::uint64_t>(0b00110101));
}

TEST_F(ASM_PARSER_TEST, OPERAND9) {
    std::string data = "x0";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, HCAsm::OperandType::reg);
    EXPECT_EQ(operand.mode, HCAsm::Mode::b64);
    EXPECT_EQ(operand.reg, HyperCPU::Registers::X0);
}