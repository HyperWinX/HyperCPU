#pragma once

#ifdef __HCPU_DEBUG
# define UNREACHABLE() std::abort()
# define EXIT(code) std::abort()
#else
# define UNREACHABLE() __builtin_unreachable()
# define EXIT(code) std::exit(code)
#endif