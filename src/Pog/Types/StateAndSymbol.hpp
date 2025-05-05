#pragma once

#include "Pog/State.hpp"
#include "Pog/Symbol.hpp"

namespace pog {

  template <typename ValueT>
  struct StateAndSymbol {
    const State<ValueT>* state;
    const Symbol<ValueT>* symbol;

    bool operator==(const StateAndSymbol& rhs) const {
      return state->get_index() == rhs.state->get_index() && symbol->get_index() == rhs.symbol->get_index();
    }

    bool operator!=(const StateAndSymbol& rhs) const {
      return !(*this == rhs);
    }
  };

} // namespace pog

namespace std {

  template <typename ValueT>
  struct hash<pog::StateAndSymbol<ValueT>> {
    std::size_t operator()(const pog::StateAndSymbol<ValueT>& ss) const {
      return pog::hash_combine(ss.state->get_index(), ss.symbol->get_index());
    }
  };

} // namespace std
