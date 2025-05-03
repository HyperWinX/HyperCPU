#include "pch.hpp"

#include <termios.h>

namespace HyperCPU {
  class SimpleIOImpl {
  public:
    SimpleIOImpl();

    std::function<void(std::uint8_t)> GetPutchar();
    std::function<std::uint8_t()> GetGetchar();

    ~SimpleIOImpl();
  private:
    enum class CurrentState {
      Default,
      WaitingForCommand
    };

    enum class Command : std::uint8_t {
      EnablePrinting = 0x10,
      DisablePrinting = 0x11,
    };

    void Putchar(std::uint8_t);
    std::uint8_t Getchar();

    void DisablePrinting();
    void EnablePrinting();

    CurrentState state;

    bool was_printing, printing;
    struct termios oldt, newt;
  };
}
