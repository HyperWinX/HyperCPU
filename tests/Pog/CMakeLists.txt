cmake_minimum_required(VERSION 3.25)

add_executable(
    pog_testing
        Automaton.cpp
        FilterView.cpp
        Grammar.cpp
        Item.cpp
        Parser.cpp
        ParsingTable.cpp
        PogTests.cpp
        Precedence.cpp
        Rule.cpp
        RuleBuilder.cpp
        State.cpp
        Symbol.cpp
        Token.cpp
        TokenBuilder.cpp
        Tokenizer.cpp
        Utils.cpp
)

target_link_libraries(
    pog_testing
    PRIVATE
        emulator-core
        assembler-core
        GTest::gtest
        pthread
        pch
        pog
)
target_include_directories(
    pog_testing
    PRIVATE
        ${CMAKE_SOURCE_DIR}/tests
)

gtest_add_tests(
    TARGET
        pog_testing
    EXTRA_ARGS
        --gtest_brief=1
)
