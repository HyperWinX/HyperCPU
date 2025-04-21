cmake_minimum_required(VERSION 3.25)


add_custom_target(python_build_copy_tests ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/DummyProject"
        "${CMAKE_CURRENT_BINARY_DIR}/DummyProject"
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/test_build.py"
        "${CMAKE_CURRENT_BINARY_DIR}/test_build.py"
    COMMENT "Copy python tests and their artifacts to build directory"
)

add_test(
    NAME TestBuildsystem
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E env
        PYTHONPATH=${CMAKE_SOURCE_DIR}
        python3
        "${CMAKE_CURRENT_BINARY_DIR}/test_build.py"
)