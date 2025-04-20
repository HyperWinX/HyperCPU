cmake_minimum_required(VERSION 3.25)


add_library(
	emulator-core STATIC
	Core/StatementCompilers.cpp
	Core/Parsers.cpp
	Core/Tokenizers.cpp
	Core/Compiler.cpp
	Core/BinaryTransformer.cpp
	Utils/Extension.hpp
	Core/BinaryTransformer.hpp
	Core/OpcodeNameAssoc.hpp
	Core/RegNameAssoc.hpp
	Core/Compiler.hpp
	Core/ModeNameAssoc.hpp
)
target_include_directories(
	emulator-core PUBLIC
	${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(
	emulator-core PUBLIC
	fmt::fmt argparse::argparse pog eternal::eternal pch
)

add_executable(hcasm Main/Main.cpp)
target_link_libraries(hcasm PRIVATE assembler-core)