set(FAST_COMPILE_FLAGS "-Wall -Wextra -Wno-pointer-arith -O3 -Wno-unused-const-variable")
set(DEBUG_COMPILE_FLAGS "-Wall -Wextra -Werror -Wno-pointer-arith -O0 -ggdb3 -Wno-unused-const-variable -fno-sanitize-recover=all -fsanitize=address,undefined")

set(TESTING_COMPILE_FLAGS_NOOPT "-Wall -Wextra -Werror -Wno-pointer-arith -O0 -ggdb3 -Wno-unused-const-variable -fno-sanitize-recover=all -fsanitize=address,undefined")
set(TESTING_COMPILE_FLAGS_ALLOPT "-Wall -Wextra -Werror -Wno-pointer-arith -O0 -ggdb3 -Wno-unused-const-variable -fno-sanitize-recover=all -fsanitize=address,undefined -flto=thin")
