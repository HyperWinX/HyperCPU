#ifdef HCPU_ENABLE_LIBUNWIND

#include <backtrace.h>
#include <libunwind.h>

extern "C" {
  void bt_create_error_callback(void*, const char* msg, int err);
}

class BacktraceController {
public:
  BacktraceController() = default;
  BacktraceController(char* name) {
    bt_state = backtrace_create_state(name, 0, bt_create_error_callback, nullptr);
  }

  void Run();
private:
  // libunwind
  [[maybe_unused]] unw_cursor_t cursor;
  [[maybe_unused]] unw_context_t context;

  // libbacktrace
  void* bt_state;
};

extern BacktraceController global_bt_controller;

void RunBacktraceController();

#endif