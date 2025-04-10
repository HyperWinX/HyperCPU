if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(LTO_FLAG "-flto=thin")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(LTO_FLAG "-flto")
endif()
set(DEBUG_COMPILE_FLAGS -Wall -Wextra -Werror -Wno-pointer-arith -O0 -ggdb3 -Wno-unused-const-variable -Wno-missing-field-initializers -Wno-stringop-overflow -Wno-unknown-warning-option)
set(FAST_COMPILE_FLAGS -Wall -Wextra -Werror -Wno-pointer-arith -O3 -Wno-unused-const-variable -Wno-missing-field-initializers -Wno-stringop-overflow -Wno-unknown-warning-option)
