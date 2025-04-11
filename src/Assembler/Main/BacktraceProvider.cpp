#include <fmt/base.h>
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
    fmt::println("{}[!] Error while getting the stacktrace!{}", B_RED, RESET);
  }

  int bt_callback(void*, uintptr_t, const char* filename, int lineno, const char* function) {
    if (global_bt_controller.HasFinished() || global_bt_controller.iteration < 2) {
      ++global_bt_controller.iteration;
      return 0;
    }

    // Demangle function name
    const char* func_name = function;
    int status;
    unw_word_t pc, sp;
    char* demangled = abi::__cxa_demangle(function, nullptr, nullptr, &status);
    if (!status) {
      func_name = demangled;
    }

    // Null pointer protection
    if (!func_name) {
      func_name = "<unknown>";
    } else if (!std::strcmp(func_name, "main")) {
      global_bt_controller.SetFinished();
    }
    if (!filename) {
      filename = "<unknown>";
    }

    // Extract PC and SP
    if (unw_get_reg(&global_bt_controller.cursor, UNW_REG_IP, &pc)) {
      fmt::println("{}[!] Unwinding stack failed: couldn't get PC!{}", B_RED, RESET);
      std::exit(1);
    }

    if (unw_get_reg(&global_bt_controller.cursor, UNW_REG_SP, &sp)) {
      fmt::println("{}[!] Unwinding stack failed: couldn't get SP!{}", B_RED, RESET);
      std::exit(1); 
    }

    fmt::println("{}frame #{} (PC: {:#x}, SP: {:#x}){}", B_YELLOW, global_bt_controller.iteration, pc, sp, RESET);
    fmt::println("{}{}:{}, function: {}{}", B_YELLOW, filename, lineno, func_name, RESET);

    std::free(demangled);
    
    ++global_bt_controller.iteration;
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
    fmt::println("{}[!] Unwinding stack failed: couldn't initialize the context!{}", B_RED, RESET);
    std::exit(1);
  }

  if (unw_init_local(&cursor, &context) < 0) {
    fmt::println("{}[!] Unwinding stack failed: couldn't initialize the context!{}", B_RED, RESET);
    std::exit(1);
  }
  fmt::println("{}[>] Libunwind context initialized successfully, generating stack trace...{}\n", B_GREEN, RESET);

  unw_step(&cursor);

  backtrace_full((backtrace_state*)bt_state, 0, bt_callback, bt_error_callback, nullptr);
}

void BacktraceController::SetFinished() {
  finished = true;
}

bool BacktraceController::HasFinished() {
  return finished;
}

#endif