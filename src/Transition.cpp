#include "../include/Transition.hpp"

Transition::Transition(size_t id, std::string initialState, std::string resultingState,
std::string readSymbol, std::string writeSymbol, movements_ movement) :
initialState_(std::move(initialState)), resultingState_(std::move(resultingState)),
readSymbol_(std::move(readSymbol)), writeSymbol_(std::move(writeSymbol)) {
  id_ = id;
  movement_ = movement;
}

std::string Transition::getOldState() const {
  return initialState_;
}

std::string Transition::getReadSymbol() const {
  return readSymbol_;
}

std::ostream& Transition::show(std::ostream& os) const {
  os << '\t' << id_ << ". { " << initialState_ << ", " << readSymbol_ << ", " << resultingState_ << ", " << writeSymbol_ << ", ";
  if (movement_ == movements_::R) {
    os << "R";
  } else {
    os << "L";
  }
  os << " }\n";
  return os;
}

////////////////////////////////////////////////////////////////////////////

void TransitionMap::insert(const Transition& transition) {
  transitionMap_.emplace(std::make_tuple(transition.getOldState(),
  transition.getReadSymbol()), transition);
}

std::queue<Transition> TransitionMap::find(const std::string& state,
const std::string& readSymbol) const {
  auto tuple = std::make_tuple(state, readSymbol);
  auto range = transitionMap_.equal_range(tuple);
  std::queue<Transition> posiblesTransitions;
  for (auto it = range.first; it != range.second; it++) {
    posiblesTransitions.push(it->second);
  }
  return posiblesTransitions;
}

std::ostream& TransitionMap::show(std::ostream& os) const {
  for (const auto& it : transitionMap_) {
    it.second.show(os);
  }
  return os;
}
