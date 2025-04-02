include_directories(${HyperCPU_SOURCE_DIR}/src)

add_subdirectory(${HyperCPU_SOURCE_DIR}/dist/benchmark dist/benchmark)

set(EXECUTABLE_OUTPUT_PATH .)

add_executable(memory_fetch_bench_no memory_fetch/memory_fetch.cpp instr/decode.cpp)
target_compile_options(memory_fetch_bench_no PUBLIC -pthread -O0)
target_link_libraries(memory_fetch_bench_no benchmark benchmark_main pthread emulator-core)
target_include_directories(memory_fetch_bench_no PUBLIC ${ROOT_DIR}/src/Emulator)
#add_custom_command(TARGET memory_fetch_bench_no POST_BUILD COMMAND ./memory_fetch_bench_no)

add_executable(memory_fetch_bench_o memory_fetch/memory_fetch.cpp instr/decode.cpp)
target_compile_options(memory_fetch_bench_o PUBLIC -pthread -O2)
target_link_libraries(memory_fetch_bench_o benchmark benchmark_main pthread emulator-core)
add_custom_command(TARGET memory_fetch_bench_o POST_BUILD COMMAND ./memory_fetch_bench_o)
