include(ExternalProject)

set(GENERIC_INCLUDE_DIR 
  ${ROOT_DIR}/src
  ${ROOT_DIR}/dist/argparse/include
  ${ROOT_DIR}/dist/pog/include
  ${ROOT_DIR}/dist/eternal/include
  ${ROOT_DIR}/dist/HPool)

ExternalProject_Add(
  libbacktrace
  SOURCE_DIR
    ${ROOT_DIR}/dist/libbacktrace
  BUILD_IN_SOURCE
    0
  CONFIGURE_COMMAND
    cd ${ROOT_DIR}/dist/libbacktrace && ./configure
  BUILD_COMMAND
    cd ${ROOT_DIR}/dist/libbacktrace && make -j$(nproc)
  INSTALL_COMMAND
    ""
  BUILD_BYPRODUCTS 
    ${ROOT_DIR}/dist/libbacktrace/libbacktrace.la
)

add_library(emulator-core STATIC ${SOURCES_emulator-core})
target_include_directories(emulator-core PUBLIC ${GENERIC_INCLUDE_DIR} ${ROOT_DIR}/src/Emulator)
target_link_libraries(emulator-core ${LD_FLAGS} fmt)

add_library(assembler-core STATIC ${SOURCES_assembler-core})
target_include_directories(assembler-core PUBLIC ${GENERIC_INCLUDE_DIR} ${ROOT_DIR}/src/Assembler)
target_link_libraries(assembler-core pog)

add_library(backtrace-provider STATIC ${SOURCES_backtrace-provider})
target_include_directories(backtrace-provider PUBLIC ${GENERIC_INCLUDE_DIR})
add_dependencies(backtrace-provider libbacktrace)

add_executable(hcasm ${SOURCES_assembler-main})
target_include_directories(hcasm PUBLIC ${GENERIC_INCLUDE_DIR} ${ROOT_DIR}/src/Assembler)
target_link_libraries(hcasm assembler-core pog)

add_executable(hcemul ${SOURCES_emulator-main})
target_include_directories(hcemul PUBLIC ${GENERIC_INCLUDE_DIR} ${ROOT_DIR}/src/Emulator)
target_link_libraries(hcemul emulator-core assembler-core)

if (LIBUNWIND)
  target_link_libraries(hcasm backtrace-provider -L${ROOT_DIR}/dist/libbacktrace backtrace)
  target_link_libraries(hcemul backtrace-provider -L${ROOT_DIR}/dist/libbacktrace backtrace)
endif()

add_custom_target(default
  DEPENDS
    hcasm
    hcemul
)
