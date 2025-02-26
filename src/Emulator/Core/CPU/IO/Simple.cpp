#include <cstdint>
#include <cstdio>
#include <iostream>

#include <termios.h>
#include <unistd.h>

#include <Core/CPU/IO/Simple.hpp>
#include <Misc/bit_cast.hpp>

HyperCPU::SimpleIOImpl::SimpleIOImpl() : state(CurrentState::Default), was_printing(true), printing(true), buffering(true) {
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  newt.c_cc[VMIN] = 1;
  newt.c_cc[VTIME] = 0;
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

HyperCPU::SimpleIOImpl::~SimpleIOImpl() {
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void HyperCPU::SimpleIOImpl::Putchar(std::uint8_t c) {
  if (state == CurrentState::WaitingForCommand) {
    switch(HyperCPU::bit_cast<Command>(c)) {
      case Command::DisableBuffering:
        DisableBuffering();
        printing = was_printing;
        buffering = false;
        break;
      case Command::EnableBuffering:
        EnableBuffering();
        printing = false;
        buffering = true;
        break;
      case Command::EnablePrinting:
        printing = true;
        was_printing = true;
        break;
      case Command::DisablePrinting:
        printing = false;
        was_printing = false;
        break;
      default:
        break;
    }
    state = CurrentState::Default;
    return;
  }

  switch (c) {
    case 0xFF:
      state = CurrentState::WaitingForCommand;
      return;
    default:
      std::putchar(c);
      break;
  }
}

std::uint8_t HyperCPU::SimpleIOImpl::Getchar() {
  char c;
  read(STDIN_FILENO, &c, 1);
  if (printing) {
    std::putchar(c);
  }
  return c;
}

std::function<void(std::uint8_t)> HyperCPU::SimpleIOImpl::GetPutchar() {
  return std::bind(&SimpleIOImpl::Putchar, this, std::placeholders::_1);
}

std::function<std::uint8_t()> HyperCPU::SimpleIOImpl::GetGetchar() {
  return std::bind(&SimpleIOImpl::Getchar, this);
}

void HyperCPU::SimpleIOImpl::EnableBuffering() {
  if (tcsetattr(STDIN_FILENO, TCSANOW, &oldt) == -1) {
    std::cerr << "Failed to enable buffering\n";
  }
}

void HyperCPU::SimpleIOImpl::DisableBuffering() {
  if (tcsetattr(STDIN_FILENO, TCSANOW, &newt)) {
    std::cerr << "Failed to disable buffering\n";
  }
}
