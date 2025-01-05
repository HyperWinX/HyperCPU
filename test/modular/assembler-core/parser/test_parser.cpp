#include <fixtures.hpp>

TEST_F(asm_parser_test, TOKEN_STRING) {
    std::string str = "this is a string to test parser";
    std::string data = std::format("\"{}\" 50", str);
    pog::Parser<hcasm::value> prsr;
    
    prsr.token("\\s+");
    prsr.token(R"("[^"]*")")
        .symbol("string")
        .action([](std::string_view str) -> hcasm::value {
            return {std::string{str.begin() + 1, str.end() - 1}};
        });
    prsr.token("[0-9]+")
        .symbol("int")
        .action([](std::string_view str) -> hcasm::value {
            return {std::stoi(std::string{str})};
        });

    prsr.set_start_symbol("string_test");
    prsr.rule("string_test")
        .production("string", "int", [](auto&& args) -> hcasm::value {
            return std::move(args[0]);
        });

    auto report = prsr.prepare();
	if (!report)
	{
		fmt::print("{}\n", report.to_string());
		std::exit(0);
	}
    EXPECT_EQ(std::get<std::string>(prsr.parse(data).value().val), str);
}