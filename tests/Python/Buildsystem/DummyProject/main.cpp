#include <iostream>

// compilation will fail if plog is not available
#include <plog/Log.h>

#ifndef DUMMY_MESSAGE
#error "Expected macro DUMMY_MESSAGE in this compilation unit"
#endif

int main() {
  std::cout << DUMMY_MESSAGE;
  return 0;
}