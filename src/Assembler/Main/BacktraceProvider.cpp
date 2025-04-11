#ifdef HCPU_ENABLE_LIBUNWIND

#include <cstdlib>
#include <cstdio>
#include <cxxabi.h>

#define UNW_LOCAL_ONLY
#include <libunwind.h>
#include <backtrace.h>

#include <fmt/printf.h>

#include <Main/BacktraceProvider.hpp>
#include <Logger/Colors.hpp>

extern "C" {
  void bt_create_error_callback(void*, const char* msg, int err) {
    printf("Error %d occurred when initializing the stack trace: %s", err, msg);
  }

  void bt_error_callback(void*, [[maybe_unused]] const char* msg, [[maybe_unused]] int err) {
    std::puts("Error while getting the stacktrace!");
  }

  int bt_callback(void*, uintptr_t, const char* filename, int lineno, const char* function) {
    if (global_bt_controller.HasFinished() || global_bt_controller.iteration++ != 2) {
      return 0;
    }

    const char* func_name = function;
    int status;
    char* demangled = abi::__cxa_demangle(function, nullptr, nullptr, &status);
    if (!status) {
      func_name = demangled;
    }

    if (!func_name) {
      func_name = "<unknown>";
    } else if (!std::strcmp(func_name, "main")) {
      global_bt_controller.SetFinished();
    }

    if (!filename) {
      filename = "<unknown>";
    }

    fmt::println("{}:{} in function {}", filename, lineno, func_name);

    std::free(demangled);

    return 0;
  }

  void RunBacktraceController() {
    global_bt_controller.Run();
  }
}

BacktraceController global_bt_controller;

void BacktraceController::Run() {
  fmt::println("\n{}[!] HyperCPU encountered a segmentation fault!{}", B_RED, RESET);
  if (unw_getcontext(&context) < 0) {
    std::puts("Unwinding stack failed: couldn't initialize context");
    std::exit(1);
  }

  if (unw_init_local(&cursor, &context) < 0) {
    std::puts("Unwinding stack failed: couldn't initialize context");
    std::exit(1);
  }
  fmt::println("{}[>] Libunwind context initialized successfully, generating stack trace...{}\n", B_GREEN, RESET);

  unw_step(&cursor);

  backtrace_full((backtrace_state*)bt_state, 0, bt_callback, bt_error_callback, nullptr);
  
  /*
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

    fmt::println("{}", sym);
  }
  */
}

void BacktraceController::SetFinished() {
  finished = true;
}

bool BacktraceController::HasFinished() {
  return finished;
}

#endif