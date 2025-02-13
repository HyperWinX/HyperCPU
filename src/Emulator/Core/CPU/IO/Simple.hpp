#include <functional>

#include <termios.h>
#include <unistd.h>


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
      EnableBuffering = 0x20,
      DisableBuffering = 0x21
    };
  
    void Putchar(std::uint8_t);
    std::uint8_t Getchar();

    void DisableBuffering();
    void EnableBuffering();

    CurrentState state;

    bool was_printing, printing, buffering;
    struct termios oldt, newt;
  };
}
