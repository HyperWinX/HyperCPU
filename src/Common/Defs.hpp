#pragma once


#if defined(__GNUC__) || defined(__clang__)
    #define HCPU_ALWAYS_INLINE inline __attribute__((always_inline))
#else
    #define HCPU_ALWAYS_INLINE inline
#endif
