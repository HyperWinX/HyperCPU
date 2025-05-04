cmake_minimum_required(VERSION 3.22)

add_library(
    hcpu::pog
    INTERFACE
        Pog.hpp
        Action.hpp
        Automaton.hpp
        DigraphAlgo.hpp
        Errors.hpp
        FilterView.hpp
        Grammar.hpp
        HTMLReport.hpp
        Item.hpp
        LineSpecialization.hpp
        Operations/Follow.hpp
        Operations/Lookahead.hpp
        Operations/Operation.hpp
        Operations/Read.hpp
        Parser.hpp
        ParserReport.hpp
        ParsingTable.hpp
        Pog.hpp
        Precedence.hpp
        Relations/Includes.hpp
        Relations/Lookback.hpp
        Relations/Relation.hpp
        RuleBuilder.hpp
        Rule.hpp
        State.hpp
        Symbol.hpp
        TokenBuilder.hpp
        Token.hpp
        Tokenizer.hpp
        Types/StateAndRule.hpp
        Types/StateAndSymbol.hpp
        Utils.hpp
)

target_precompile_headers(hcpu::pog INTERFACE Pog.hpp)
target_include_directories(hcpu::pog INTERFACE ${CMAKE_SOURCE_DIR}/src)
