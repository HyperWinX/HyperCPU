include_directories(${HyperCPU_SOURCE_DIR}/src ${HyperCPU_SOURCE_DIR}/dist/HBench/src)

set(EXECUTABLE_OUTPUT_PATH .)

add_executable(memory_fetch_bench_no memory_fetch/memory_fetch.cpp)
target_compile_options(memory_fetch_bench_no PUBLIC -pthread -O0)
add_custom_command(TARGET memory_fetch_bench_no POST_BUILD COMMAND ./memory_fetch_bench_no)

add_executable(memory_fetch_bench_o memory_fetch/memory_fetch.cpp)
target_compile_options(memory_fetch_bench_o PUBLIC -pthread -O2)
add_custom_command(TARGET memory_fetch_bench_o POST_BUILD COMMAND ./memory_fetch_bench_o)
