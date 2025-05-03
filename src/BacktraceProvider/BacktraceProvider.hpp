#ifdef HCPU_ENABLE_LIBUNWIND
#include "pch.hpp"

#include <backtrace.h>
#include <libunwind.h>

extern "C" {
  void bt_create_error_callback(void*, const char* msg, int err);
}

class BacktraceController {
public:
  BacktraceController() = default;
  BacktraceController(char* name) : iteration(0), finished(false) {
    bt_state = backtrace_create_state(name, 0, bt_create_error_callback, nullptr);
  }

  void Run();
  void SetFinished();
  bool HasFinished();

  int iteration; // to slice entries that are not needed

  // libunwind
  unw_cursor_t cursor;
  unw_context_t context;
private:
  // libbacktrace
  void* bt_state;

  // internals
  bool finished;
};

extern BacktraceController global_bt_controller;
extern std::string_view catched_signal_type;

extern "C" void SignalHandler(int);

#endif
