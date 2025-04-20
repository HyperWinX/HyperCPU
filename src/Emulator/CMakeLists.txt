cmake_minimum_required(VERSION 3.25)


add_library(
    assembler-core STATIC
    Core/CPU/Instructions/AllowedFlags.cpp
    Core/CPU/Interrupts/InterruptHandler.cpp
    Core/CPU/CPU.cpp
    Core/CPU/InstructionsImpl/DIV.cpp
    Core/CPU/InstructionsImpl/CALLL.cpp
    Core/CPU/InstructionsImpl/MUL.cpp
    Core/CPU/InstructionsImpl/READ.cpp
    Core/CPU/InstructionsImpl/ADC.cpp
    Core/CPU/InstructionsImpl/ADD.cpp
    Core/CPU/InstructionsImpl/DEC.cpp
    Core/CPU/InstructionsImpl/SHFL.cpp
    Core/CPU/InstructionsImpl/CUDF.cpp
    Core/CPU/InstructionsImpl/PUSH.cpp
    Core/CPU/InstructionsImpl/OR.cpp
    Core/CPU/InstructionsImpl/POP.cpp
    Core/CPU/InstructionsImpl/CALLGR.cpp
    Core/CPU/InstructionsImpl/CCRF.cpp
    Core/CPU/InstructionsImpl/JMP.cpp
    Core/CPU/InstructionsImpl/AND.cpp
    Core/CPU/InstructionsImpl/HID.cpp
    Core/CPU/InstructionsImpl/CALL.cpp
    Core/CPU/InstructionsImpl/INC.cpp
    Core/CPU/InstructionsImpl/INTR.cpp
    Core/CPU/InstructionsImpl/SHFR.cpp
    Core/CPU/InstructionsImpl/CALLE.cpp
    Core/CPU/InstructionsImpl/JML.cpp
    Core/CPU/InstructionsImpl/SUB.cpp
    Core/CPU/InstructionsImpl/ANDN.cpp
    Core/CPU/InstructionsImpl/LOIVT.cpp
    Core/CPU/InstructionsImpl/HALT.cpp
    Core/CPU/InstructionsImpl/MOV.cpp
    Core/CPU/InstructionsImpl/CMP.cpp
    Core/CPU/InstructionsImpl/WRITE.cpp
    Core/CPU/InstructionsImpl/BSWAP.cpp
    Core/CPU/InstructionsImpl/JME.cpp
    Core/CPU/InstructionsImpl/COVF.cpp
    Core/CPU/InstructionsImpl/JMGR.cpp
    Core/CPU/Decoders/StdDecoder.cpp
    Core/CPU/Stack.cpp
    Core/CPU/OperandsEvaluation.cpp
    Core/CPU/IO/Simple.cpp
    Core/MemoryController/MemoryControllerST.hpp
    Core/MemoryController/IMemoryController.hpp
    Core/CPU/Instructions/AllowedFlags.hpp
    Core/CPU/Instructions/Opcodes.hpp
    Core/CPU/Instructions/Flags.hpp
    Core/CPU/Instructions/Registers.hpp
    Core/CPU/Interrupts/ReservedInterrupts.hpp
    Core/CPU/CPU.hpp
    Core/CPU/ALU.hpp
    Core/CPU/Decoders/StdDecoder.hpp
    Core/CPU/Decoders/IDecoder.hpp
    Core/CPU/Assert.hpp
    Core/CPU/Version.hpp
    Core/CPU/Util.hpp
    Core/CPU/IO/Simple.hpp
    Misc/byteswap.hpp
    Misc/overflow.hpp
    Misc/deref.hpp
    Misc/bit_cast.hpp
    Misc/unreachable.hpp
    Misc/underflow.hpp
    Misc/print.hpp
)

target_include_directories(
    assembler-core PUBLIC
    ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    assembler-core PUBLIC
    fmt::fmt argparse::argparse pog eternal::eternal pch
)

add_executable(
    hcemul 
    Main/Main.hpp
    Main/Main.cpp
    Main/ExceptionHandling.cpp
    Main/ExceptionHandling.hpp
)
target_link_libraries(hcemul PRIVATE assembler-core)