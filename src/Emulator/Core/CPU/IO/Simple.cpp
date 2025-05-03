#include "pch.hpp"

#include <termios.h>
#include <unistd.h>

#include <Core/CPU/IO/Simple.hpp>
#include <Misc/bit_cast.hpp>

HyperCPU::SimpleIOImpl::SimpleIOImpl() : state(CurrentState::Default), was_printing(true), printing(true) {
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
      case Command::EnablePrinting:
        EnablePrinting();
        printing = true;
        was_printing = true;
        break;
      case Command::DisablePrinting:
        DisablePrinting();
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
  [[maybe_unused]] auto t = read(STDIN_FILENO, &c, 1);
  return c;
}

std::function<void(std::uint8_t)> HyperCPU::SimpleIOImpl::GetPutchar() {
  return std::bind(&SimpleIOImpl::Putchar, this, std::placeholders::_1);
}

std::function<std::uint8_t()> HyperCPU::SimpleIOImpl::GetGetchar() {
  return std::bind(&SimpleIOImpl::Getchar, this);
}

void HyperCPU::SimpleIOImpl::DisablePrinting() {
  newt.c_lflag &= ~ECHO;
  newt.c_lflag |= ECHONL;
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void HyperCPU::SimpleIOImpl::EnablePrinting() {
  newt.c_lflag |= ECHO;
  newt.c_lflag |= ECHONL;
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}
