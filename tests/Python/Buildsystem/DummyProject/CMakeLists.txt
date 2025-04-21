cmake_minimum_required(VERSION 3.25)


project(dummy)

find_package(plog 1.0.0 REQUIRED)

if("${DUMMY_MESSAGE}" EQ "")
    message(ERROR "Dummy: expected DUMMY_MESSAGE to be defined")
endif()

add_executable(
    dummy 
        main.cpp
)

target_compile_definitions(
    dummy PRIVATE 
        DUMMY_MESSAGE=${DUMMY_MESSAGE}
)

target_link_libraries(dummy PRIVATE plog)
