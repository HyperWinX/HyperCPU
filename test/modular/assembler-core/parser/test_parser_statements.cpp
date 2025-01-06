#include <fixtures.hpp>

TEST_F(asm_parser_test, OPERAND1) {
    std::string data = "[15FAh]";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<hcasm::operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, hcasm::operand_type::memaddr);
    EXPECT_EQ(operand.uint1, static_cast<std::uint64_t>(0x15FA));
}

TEST_F(asm_parser_test, OPERAND2) {
    std::string data = "[x0 + 15u]";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<hcasm::operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, hcasm::operand_type::mem_reg_add_int);
    EXPECT_EQ(operand.reg1, hypercpu::registers::X0);
    EXPECT_EQ(operand.uint1, static_cast<std::uint64_t>(15));
}

TEST_F(asm_parser_test, OPERAND3) {
    std::string data = "[x0 - 15u]";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<hcasm::operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, hcasm::operand_type::mem_reg_sub_int);
    EXPECT_EQ(operand.reg1, hypercpu::registers::X0);
    EXPECT_EQ(operand.uint1, static_cast<std::uint64_t>(15));
}

TEST_F(asm_parser_test, OPERAND2_2) {
    std::string data = "[x0 + 15h]";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<hcasm::operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, hcasm::operand_type::mem_reg_add_int);
    EXPECT_EQ(operand.reg1, hypercpu::registers::X0);
    EXPECT_EQ(operand.uint1, static_cast<std::uint64_t>(0x15));
}

TEST_F(asm_parser_test, OPERAND3_2) {
    std::string data = "[x0 - 15h]";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<hcasm::operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, hcasm::operand_type::mem_reg_sub_int);
    EXPECT_EQ(operand.reg1, hypercpu::registers::X0);
    EXPECT_EQ(operand.uint1, static_cast<std::uint64_t>(0x15));
}

TEST_F(asm_parser_test, OPERAND2_3) {
    std::string data = "[x0 + 0100110101b]";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<hcasm::operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, hcasm::operand_type::mem_reg_add_int);
    EXPECT_EQ(operand.reg1, hypercpu::registers::X0);
    EXPECT_EQ(operand.uint1, static_cast<std::uint64_t>(0b0100110101));
}

TEST_F(asm_parser_test, OPERAND3_3) {
    std::string data = "[x0 - 0100110101b]";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<hcasm::operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, hcasm::operand_type::mem_reg_sub_int);
    EXPECT_EQ(operand.reg1, hypercpu::registers::X0);
    EXPECT_EQ(operand.uint1, static_cast<std::uint64_t>(0b0100110101));
}

TEST_F(asm_parser_test, OPERAND4) {
    std::string data = "15s";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<hcasm::operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, hcasm::operand_type::sint);
    EXPECT_EQ(operand.sint2, static_cast<std::int64_t>(15));
}

TEST_F(asm_parser_test, OPERAND5_1) {
    std::string data = "15u";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<hcasm::operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, hcasm::operand_type::uint);
    EXPECT_EQ(operand.uint1, static_cast<std::uint64_t>(15));
}

TEST_F(asm_parser_test, OPERAND5_2) {
    std::string data = "15h";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<hcasm::operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, hcasm::operand_type::uint);
    EXPECT_EQ(operand.uint1, static_cast<std::uint64_t>(0x15));
}

TEST_F(asm_parser_test, OPERAND5_3) {
    std::string data = "010100101b";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<hcasm::operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, hcasm::operand_type::uint);
    EXPECT_EQ(operand.uint1, static_cast<std::uint64_t>(0b010100101));
}

TEST_F(asm_parser_test, OPERAND6) {
    std::string data = "x0";
    parser.set_start_symbol("operand");

    parser.prepare();

    auto operand = std::get<hcasm::operand>(parser.parse(data)->val);

    EXPECT_EQ(operand.type, hcasm::operand_type::reg);
    EXPECT_EQ(operand.reg1, hypercpu::registers::X0);
}