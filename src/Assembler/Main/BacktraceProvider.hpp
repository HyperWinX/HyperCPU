#ifdef HCPU_ENABLE_LIBUNWIND

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
private:
  // libunwind
  [[maybe_unused]] unw_cursor_t cursor;
  [[maybe_unused]] unw_context_t context;

  // libbacktrace
  void* bt_state;

  // internals
  bool finished;
};

extern BacktraceController global_bt_controller;

extern "C" void RunBacktraceController();

#endif