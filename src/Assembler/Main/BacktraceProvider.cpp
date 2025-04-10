#ifdef HCPU_ENABLE_LIBUNWIND

#include <cstdlib>
#include <cstdio>
#include <cxxabi.h>

#define UNW_LOCAL_ONLY
#include <libunwind.h>
#include <backtrace.h>

#include <fmt/printf.h>

#include <Main/BacktraceProvider.hpp>

extern "C" {
  void bt_create_error_callback(void*, const char* msg, int err) {
    printf("Error %d occurred when initializing the stack trace: %s", err, msg);
  }

  void bt_error_callback(void*, [[maybe_unused]] const char* msg, [[maybe_unused]] int err) {
    std::puts("Error while getting the stacktrace!");
  }

  int bt_callback(void*, uintptr_t, const char* filename, int lineno, const char* function) {
    const char* func_name = function;
    int status;
    char* demangled = abi::__cxa_demangle(function, nullptr, nullptr, &status);
    if (!status) {
      func_name = demangled;
    }

    fmt::println("{}:{} in function {}", filename, lineno, func_name);

    return 0;
  }
}

BacktraceController global_bt_controller;

void BacktraceController::Run() {
  backtrace_full((backtrace_state*)bt_state, 0, bt_callback, bt_error_callback, nullptr);
  /*
  if (unw_getcontext(&context) < 0) {
    std::puts("Unwinding stack failed: couldn't initialize context");
    std::exit(1);
  }

  if (unw_init_local(&cursor, &context) < 0) {
    std::puts("Unwinding stack failed: couldn't initialize context");
    std::exit(1);
  }

  unw_step(&cursor); // We should skip one more frame - RunBacktraceController

  while (unw_step(&cursor) > 0) {
    unw_word_t offset, pc, sp;
    char sym[512] = {"<unknown>"};
    char* name = sym;

    if (unw_get_reg(&cursor, UNW_REG_IP, &pc)) {
      std::puts("Unwinding stack failed: couldn't get PC");
      std::exit(1);
    }

    if (unw_get_reg(&cursor, UNW_REG_SP, &sp)) {
      std::puts("Unwinding stack failed: couldn't get SP");
      std::exit(1);
    }

    if (!unw_get_proc_name(&cursor, sym, sizeof(sym), &offset)) {
      int status;
      if ((name = abi::__cxa_demangle(sym, NULL, NULL, &status)) == 0) {
        name = sym;
      }
    }
  }
  */
}

#endif