#include <utility>
#include <vector>
#include <stack>

#include <Core/Preprocessor.hpp>

std::string HCAsm::Preprocess(std::string& str) {
  PreprocessorState state = PreprocessorState::WaitingComment;
  std::stack<char> state_stack;
  std::vector<std::string::iterator> iterators;

  for (auto ch : str) {
    switch (state) {
      case HCAsm::PreprocessorState::WaitingComment:
        if (state_stack.empty() && ch == '#') {
          state = PreprocessorState::WaitingEOL;
        } else {
          continue;
        }
        break;
      case HCAsm::PreprocessorState::WaitingEOL:
        if (ch != '\n') continue;
        state = PreprocessorState::WaitingComment;
        break;
      default:
        std::unreachable();
    }
  }
}