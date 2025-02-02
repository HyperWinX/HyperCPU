#include "pog/line_spec.h"
#include <fixtures.hpp>

TEST_F(ASM_PARSER_TEST, TOKEN_STRING) {
    std::string str = "this is a string to test parser";
    std::string data = std::format("\"{}\" \\", str);

    // Token, created only for testing
    parser.token("\\\\")
        .symbol("\\");
    
    parser.set_start_symbol("string_test");
    parser.rule("string_test")
        .production("string", "\\", [](pog::Parser<HCAsm::Value>&, std::vector<pog::TokenWithLineSpec<HCAsm::Value>> args) -> HCAsm::Value {
            return std::move(args[0].value);
        });
    
    parser.prepare();
    
    EXPECT_EQ(std::get<std::string>(parser.parse(data).value().val), str);
}

TEST_F(ASM_PARSER_TEST, TOKEN_SINT) {
    std::string data = "1234s \\";

    // Token, created only for testing
    parser.token("\\\\")
        .symbol("\\");
    
    parser.set_start_symbol("sint_test");
    parser.rule("sint_test")
        .production("sint", "\\", [](pog::Parser<HCAsm::Value>&, std::vector<pog::TokenWithLineSpec<HCAsm::Value>> args) -> HCAsm::Value {
            return std::move(args[0].value);
        });
    
    parser.prepare();
    
    EXPECT_EQ(std::get<std::int64_t>(parser.parse(data).value().val), static_cast<std::int64_t>(1234));
}

TEST_F(ASM_PARSER_TEST, TOKEN_UINT) {
    std::string data = "1234u \\";

    // Token, created only for testing
    parser.token("\\\\")
        .symbol("\\");
    
    parser.set_start_symbol("uint_test");
    parser.rule("uint_test")
        .production("uint", "\\", [](pog::Parser<HCAsm::Value>&, std::vector<pog::TokenWithLineSpec<HCAsm::Value>> args) -> HCAsm::Value {
            return std::move(args[0].value);
        });
    
    parser.prepare();
    
    EXPECT_EQ(std::get<std::uint64_t>(parser.parse(data).value().val), static_cast<std::uint64_t>(1234));
}

TEST_F(ASM_PARSER_TEST, TOKEN_HEX) {
    std::string data = "15FAh \\";

    // Token, created only for testing
    parser.token("\\\\")
        .symbol("\\");
    
    parser.set_start_symbol("hex_test");
    parser.rule("hex_test")
        .production("hex", "\\", [](pog::Parser<HCAsm::Value>&, std::vector<pog::TokenWithLineSpec<HCAsm::Value>> args) -> HCAsm::Value {
            return std::move(args[0].value);
        });
    
    parser.prepare();
    
    EXPECT_EQ(std::get<std::uint64_t>(parser.parse(data).value().val), static_cast<std::uint64_t>(0x15FA));
}

TEST_F(ASM_PARSER_TEST, TOKEN_BINARY) {
    std::string data = "0001010111111010b \\";

    // Token, created only for testing
    parser.token("\\\\")
        .symbol("\\");
    
    parser.set_start_symbol("binary_test");
    parser.rule("binary_test")
        .production("binary", "\\", [](pog::Parser<HCAsm::Value>&, std::vector<pog::TokenWithLineSpec<HCAsm::Value>> args) -> HCAsm::Value {
            return std::move(args[0].value);
        });

    parser.prepare();
    
    EXPECT_EQ(std::get<std::uint64_t>(parser.parse(data).value().val), static_cast<std::uint64_t>(0x15FA));
}