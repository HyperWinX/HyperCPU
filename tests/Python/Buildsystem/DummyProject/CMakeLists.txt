cmake_minimum_required(VERSION 3.25)
project(dummy)

find_package(plog 1.0.0 REQUIRED)

if(NOT DEFINED DUMMY_MESSAGE OR DUMMY_MESSAGE STREQUAL "")
  message(FATAL_ERROR "Dummy: expected DUMMY_MESSAGE to be defined")
endif()

add_executable(dummy main.cpp)

target_compile_definitions(dummy
  PRIVATE
    # The backslashes escape the quote into the generated -D flag
    DUMMY_MESSAGE=\"${DUMMY_MESSAGE}\"
)

target_link_libraries(dummy
  PRIVATE
    plog::plog
)