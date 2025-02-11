#include "Misc/bit_cast.hpp"
#include <termios.h>
#include <unistd.h>

#include <Core/CPU/IO/Simple.hpp>

HyperCPU::SimpleIOImpl::SimpleIOImpl() : state(CurrentState::Default), printing(true) {
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  newt.c_cc[VMIN] = 1;
  newt.c_cc[VTIME] = 0;
  DisableBuffering();
}

HyperCPU::SimpleIOImpl::~SimpleIOImpl() {
  EnableBuffering();
}

void HyperCPU::SimpleIOImpl::Putchar(std::uint8_t c) {
  if (state == CurrentState::WaitingForCommand) {
    switch(HyperCPU::bit_cast<Command>(c)) {
      case Command::DisableBuffering:
        DisableBuffering();
        break;
      case Command::EnableBuffering:
        EnableBuffering();
        break;
      case Command::EnablePrinting:
        printing = true;
        break;
      case Command::DisablePrinting:
        printing = false;
        break;
      default:
        state = CurrentState::Default;
    }
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
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void HyperCPU::SimpleIOImpl::DisableBuffering() {
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}