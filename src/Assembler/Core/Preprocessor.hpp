#pragma once

#include <string>

namespace HCAsm {
  enum class PreprocessorState {
    WaitingEOL,
    WaitingComment
  };

  std::string Preprocess(std::string& str);
}