set(GENERIC_INCLUDE_DIR 
  ${HyperCPU_SOURCE_DIR}/src)

add_library(core STATIC ${SOURCES_core})
target_include_directories(core PUBLIC ${GENERIC_INCLUDE_DIR})
set_target_properties(core PROPERTIES COMPILE_FLAGS ${HCPU_COMPILE_FLAGS})

add_library(core-fast STATIC ${SOURCES_core})
target_include_directories(core-fast PUBLIC ${GENERIC_INCLUDE_DIR})
set_target_properties(core-fast PROPERTIES COMPILE_FLAGS ${FAST_COMPILE_FLAGS})

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_link_libraries(core-fast -flto=thin)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GCC")
  target_link_libraries(core-fast -flto)
endif()

add_executable(emulator ${SOURCES_main})
target_include_directories(emulator PUBLIC ${GENERIC_INCLUDE_DIR})
set_target_properties(emulator PROPERTIES COMPILE_FLAGS ${HCPU_COMPILE_FLAGS})
