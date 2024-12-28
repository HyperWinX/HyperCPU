include(${ROOT_DIR}/cmake/Variables.cmake)

function(set_compile_flags debug_enabled)
  if (debug_enabled)
    set(HCPU_COMPILE_FLAGS ${DEBUG_COMPILE_FLAGS} PARENT_SCOPE)
  else()
    set(HCPU_COMPILE_FLAGS ${FAST_COMPILE_FLAGS} PARENT_SCOPE)
  endif()
endfunction()
